#include <fstream>
#include <iostream>
#include <stdio.h>      
#include <time.h>   
#include <vector> 
#include <math.h>
#include <algorithm>
#include <random> 
#include <map>
#include <string.h>
#include <unordered_map> 
#include <iomanip>
#include <time.h>
using namespace std;

struct Node
{
	vector<int> adjList;
	int inDegree=0;
	int outDegree=0;
};

map<int,Node> g;	// smaller graph
map<int,Node> G;	// larger graph
int num_nodes_g=0, num_nodes_G=0;		// number of nodes in smaller and larger graphs resp

int variable(int x, int y)
{
	return (x*num_nodes_G+ y + 1);
}

void takeInput(string filename)
{
	ifstream infile(filename);
	int n1,n2;
	map<int,Node>::iterator it;
	while (true)
	{
		infile>>n1>>n2;
		if (n1==0)
			break;
		num_nodes_G = max(num_nodes_G,max(n1,n2));
		n1--;
		n2--;
		it = G.find(n1);
  		if (it == G.end())
  		{
  			Node newnode;
  			G[n1] = newnode;
  		}
		it = G.find(n2);
		if (it == G.end())
		{
			Node newnode;
			G[n2] = newnode;
		}
		G[n1].adjList.push_back(n2);
		G[n1].outDegree++;
		G[n2].inDegree++;
	}
	for (int i=0; i<num_nodes_G; i++)
	{
		it = G.find(i);
		if (it == G.end())
		{
			Node newnode;
			G[i] = newnode;
		}
	}
	while (infile>>n1)
	{
		infile>>n2;
		num_nodes_g = max(num_nodes_g, max(n1,n2));
		n1--;
		n2--;
		it = g.find(n1);
		if (it == g.end())
		{
			Node newnode;
			g[n1] = newnode;
		}
		it = g.find(n2);
		if (it == g.end())
		{
			Node newnode;
			g[n2] = newnode;
		}
		g[n1].adjList.push_back(n2);
		g[n1].outDegree++;
		g[n2].inDegree++;
	}
	for (int i=0; i<num_nodes_g; i++)
	{
		it = g.find(i);
		if (it == g.end())
		{
			Node newnode;
			g[i] = newnode;
		}
	}
	infile.close();
}

void formMinisatInput(string filename)
{
	int matrix[num_nodes_g][num_nodes_G];
	memset(matrix, 0, sizeof(int)*num_nodes_G*num_nodes_g);
	map<int,Node>::iterator it1;
	map<int,Node>::iterator it2;
	for (int i=0; i<num_nodes_g; i++)
	{
		it1 = g.find(i);
		if (it1 == g.end())
		{
			cout<<"How ?????????????????  SHOULDN't HAPPEN "<<endl;
			continue;
		}
		for (int j=0; j<num_nodes_G; j++)
		{
			it2 = G.find(j);
			if (it2 == G.end())
			{
				cout<<"........How ?????????????????  SHOULDN't HAPPEN "<<endl;
				continue;
			}
			// both i and j present in g and G resp.
			if ((g[i].inDegree <= G[j].inDegree) && (g[i].outDegree <= G[j].outDegree))
				matrix[i][j] = 1;
		}
	}
	// cout<<"PRINT MATRIX\n";
	// for (int i=0; i<num_nodes_g; i++)
	// {
	// 	for (int j=0; j<num_nodes_G; j++)
	// 		cout<<matrix[i][j]<<" ";
	// 	cout<<endl;
	// }
	ofstream outfile(filename);
	vector<int> onewalej;
	for (int i=0; i<num_nodes_g; i++)
	{
		for (int j=0; j<num_nodes_G; j++)
			if (matrix[i][j] == 1)
			{
				outfile<<to_string(variable(i,j))<< " ";
				onewalej.push_back(j);
			}
		if (onewalej.size() == 0)
			cout<<"HIiiiiiii-----------------------------------------"<<endl;
		outfile<<"0\n";		// alteast one 1 in ith row

		// no two 1's in any row wale constraints:
		for (int j1=0; j1<onewalej.size(); j1++)
			for (int j2=j1+1; j2<onewalej.size(); j2++)
				outfile<<"-"<<to_string(variable(i,onewalej[j1]))<<" -"<<to_string(variable(i,onewalej[j2]))<<" 0\n";
		onewalej.clear();
	}

	// no two 1's in any column:			// ISKO OPTIMISE KARO 
	vector<int> onewalei;
	for (int j=0; j<num_nodes_G; j++)
	{
		for (int i=0; i<num_nodes_g; i++)			// useful only if matrix is sparse
			if (matrix[i][j] == 1)
				onewalei.push_back(i);
		for (int i1=0; i1<onewalei.size(); i1++)
			for (int i2=i1+1; i2<onewalei.size(); i2++)
				outfile<<"-"<<to_string(variable(onewalei[i1],j))<<" -"<<to_string(variable(onewalei[i2],j))<<" 0\n";
		onewalei.clear();
	}

	// edge constraints:
	for (int i1=0; i1<num_nodes_g; i1++)
		for (int i2=i1+1; i2<num_nodes_g; i2++)
		{
			vector<int> v1 = g[i1].adjList;
			vector<int> v2 = g[i2].adjList;
			int flag1=0, flag2 = 0;
			if (find(v1.begin(), v1.end(), i2) != v1.end())
				flag1=1;
			if (find(v2.begin(), v2.end(), i1) != v2.end())
				flag2 = 1;
			// if (flag1==0 && flag2==0)
			// 	continue; 		

			for (int j1=0; j1<num_nodes_G; j1++)
			{
				if (matrix[i1][j1]==0)
					continue;
				for (int j2=0; j2<num_nodes_G; j2++)
				{
					if (j1==j2)
						continue; 		// will be handled by earlier constraints
					if (matrix[i2][j2]==0)
						continue;
					vector<int> V1 = G[j1].adjList;
					vector<int> V2 = G[j2].adjList;

					int flag3=0, flag4=0;
					if (find(V1.begin(), V1.end(), j2) != V1.end())
					 	flag3 = 1;
					if (find(V2.begin(), V2.end(), j1) != V2.end())
						flag4 = 1;

					if ((flag1 && !flag3) || (!flag1 && flag3) || (flag2 && !flag4) || (!flag2 && flag4))
						outfile<<"-"<<to_string(variable(i1,j1))<<" -"<<to_string(variable(i2,j2))<<" 0\n"; // both not one

					// if ( flag1 && ( find(V1.begin(), V1.end(), j2) == V1.end()) ) 
					// 	outfile<<"-"<<to_string(variable(i1,j1))<<" -"<<to_string(variable(i2,j2))<<" 0\n"; // both not zero
					// else if ( flag2 && ( find(V2.begin(), V2.end(), j1) == V2.end()) ) 
					// 	outfile<<"-"<<to_string(variable(i1,j1))<<" -"<<to_string(variable(i2,j2))<<" 0\n"; // both not zero
				
				}
			}
		}

	for (int i=0; i<num_nodes_g; i++)
		for (int j=0; j<num_nodes_G; j++)
			if (matrix[i][j] == 0)
				outfile<<"-"<<to_string(variable(i,j))<<" 0\n";
	outfile.close();
}

int main(int argc, char const *argv[])
{
	string infilename = argv[1]; infilename += ".graphs";
	string outfilename = argv[1]; outfilename += ".satinput";
	takeInput(infilename);
	formMinisatInput(outfilename);
	// cout<<"LARGER GRAPH: \n";
	// map<int, Node>::iterator itr; 
	// for (itr = G.begin(); itr != G.end(); ++itr) 
	// { 
 //        cout << itr->first << '\t' << (itr->second).inDegree << " "<<(itr-> second).outDegree << '\n'; 
 //    }
 //    cout<<"-------\n";



	return 0;
}