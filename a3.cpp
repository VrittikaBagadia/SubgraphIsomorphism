#include <fstream>
#include <iostream>  
#include <vector> 
#include <algorithm>
#include <string.h>
#include <unordered_map> 
#include <sstream>
using namespace std;

struct Node
{
	vector<int> adjList, outOFneighbour, inOFneighbour, addOFneighbour;
	int inDegree=0;
	int outDegree=0;
};

unordered_map<int,Node> g;	// smaller graph
unordered_map<int,Node> G;	// larger graph
int num_nodes_g=0, num_nodes_G=0;		// number of nodes in smaller and larger graphs resp

int variable(int x, int y)
{
	return (x*num_nodes_G+ y + 1);
}

void takeInput(string filename)
{
	ifstream infile(filename);
	int n1,n2;
	unordered_map<int,Node>::iterator it;
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
	int temp;
	for (int i=0; i<num_nodes_G; i++)
	{
		if(G[i].outDegree<=40 && G[i].inDegree<=40)
		{
			temp=G[i].adjList.size();
			if(temp!=0)
			{
				for (int j = 0; j < temp; ++j)
				{
					G[i].outOFneighbour.push_back(G[G[i].adjList[j]].outDegree);
					G[i].inOFneighbour.push_back(G[G[i].adjList[j]].inDegree);
					G[i].addOFneighbour.push_back(G[G[i].adjList[j]].outDegree+G[G[i].adjList[j]].inDegree);
				}
				sort(G[i].outOFneighbour.begin(),G[i].outOFneighbour.end(),greater<int>());
				sort(G[i].inOFneighbour.begin(),G[i].inOFneighbour.end(),greater<int>());
				sort(G[i].addOFneighbour.begin(),G[i].addOFneighbour.end(),greater<int>());
			}
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
	for (int i=0; i<num_nodes_g; i++)
	{
		if(g[i].inDegree<=20 && g[i].outDegree<=20)
		{
			temp=g[i].adjList.size();
			if(temp!=0)
			{
				for (int j = 0; j < temp; ++j)
				{
					g[i].outOFneighbour.push_back(g[g[i].adjList[j]].outDegree);
					g[i].inOFneighbour.push_back(g[g[i].adjList[j]].inDegree);
					g[i].addOFneighbour.push_back(g[g[i].adjList[j]].outDegree+g[g[i].adjList[j]].inDegree);
				}
				sort(g[i].outOFneighbour.begin(),g[i].outOFneighbour.end(),greater<int>());
				sort(g[i].inOFneighbour.begin(),g[i].inOFneighbour.end(),greater<int>());
				sort(g[i].addOFneighbour.begin(),g[i].addOFneighbour.end(),greater<int>());
			}
		}
	}

	infile.close();
}

bool vector_compare(vector<int> a, vector<int> b)
{
	int temp=a.size();
	for (int i = 0; i < temp; ++i)
	{
		if (a[i]>b[i])
		{
			return false;
		}
	}
	return true;
}

void formMinisatInput(string filename)
{
	int matrix[num_nodes_g][num_nodes_G];
	memset(matrix, 0, sizeof(int)*num_nodes_G*num_nodes_g);
	unordered_map<int,Node>::iterator it1;
	unordered_map<int,Node>::iterator it2;
	// int ctr=0;
	for (int i=0; i<num_nodes_g; i++)
	{
		it1 = g.find(i);
		// if (it1 == g.end())
		// {
		// 	cout<<"How ?????????????????  SHOULDN't HAPPEN "<<endl;
		// 	continue;
		// }
		for (int j=0; j<num_nodes_G; j++)
		{
			it2 = G.find(j);
			// if (it2 == G.end())
			// {
			// 	cout<<"........How ?????????????????  SHOULDN't HAPPEN "<<endl;
			// 	continue;
			// }
			// both i and j present in g and G resp.
			if ((g[i].inDegree <= G[j].inDegree) && (g[i].outDegree <= G[j].outDegree))
			{
				if(g[i].inDegree <=20 && G[j].inDegree<=40 && g[i].outDegree <= 20 && G[j].outDegree<=40 )
				{
					if( vector_compare(g[i].outOFneighbour,G[j].outOFneighbour)  && vector_compare(g[i].inOFneighbour,G[j].inOFneighbour) 
						&& vector_compare(g[i].addOFneighbour,G[j].addOFneighbour))
					{
						matrix[i][j] = 1;
					}
					// else
					// {
					// 	ctr++;
					// }
				}
				else
					matrix[i][j] = 1;
			}
		}
	}
	// cout<<ctr<<"!!!!!!!!!!!!!!!!!!!!";
	int ig=0,iG=0;
	vector<int> isolated_g,isolated_G;
	for (int i = 0; i < num_nodes_g; ++i)
	{
		if (g[i].inDegree==0 && g[i].outDegree ==0 )
		{
			isolated_g.push_back(i);
			// ig++;
		}
	}
	for (int i = 0; i < num_nodes_G; ++i)
	{
		if (G[i].inDegree==0 && G[i].outDegree ==0 )
		{
			isolated_G.push_back(i);
			// iG++;
		}
	}
	ig=isolated_g.size();
	iG=isolated_G.size();
	// cout<<ig<<" "<<iG;
	ofstream outfile(filename);
	if(ig>iG)
	{
		// for (int ii = 0; ii < iG; ++ii)
		// {
		// 	for (int i = 0; i < num_nodes_g ; ++i)
		// 	{
		// 		matrix[i][isolated_G[ii]]=0;
		// 	}
		// 	for (int i = 0; i < num_nodes_G ; ++i)
		// 	{
		// 		matrix[isolated_g[ii]][i]=0;
		// 	}
		// 	matrix[isolated_g[ii]][isolated_G[ii]]=1;
		// }
		outfile<<"p cnf 1 2\n1 0\n-1 0\n";
		outfile.close();

		ofstream filetmp("temp.txt");
		filetmp<<num_nodes_G;
		filetmp.close();
		return;
	}
	else
	{
		for (int ii = 0; ii < ig; ++ii)
		{
			for (int i = 0; i < num_nodes_g ; ++i)
			{
				matrix[i][isolated_G[ii]]=0;
			}
			for (int i = 0; i < num_nodes_G ; ++i)
			{
				matrix[isolated_g[ii]][i]=0;
			}
			matrix[isolated_g[ii]][isolated_G[ii]]=1;
		}

	}
	// cout<<"PRINT MATRIX\n";
	// for (int i=0; i<num_nodes_g; i++)
	// {
	// 	for (int j=0; j<num_nodes_G; j++)
	// 		cout<<matrix[i][j]<<" ";
	// 	cout<<endl;
	// }
	
	vector<int> onewalej;
	stringstream ss;
	unsigned long cno=0;
	for (int i=0; i<num_nodes_g; i++)
		for (int j=0; j<num_nodes_G; j++)
			if (matrix[i][j] == 0)
			{
				ss<<"-"<<to_string(variable(i,j))<<" 0\n";
				cno++;
			}
	for (int i=0; i<num_nodes_g; i++)
	{
		for (int j=0; j<num_nodes_G; j++)
			if (matrix[i][j] == 1)
			{
				ss<<to_string(variable(i,j))<< " ";
				onewalej.push_back(j);
			}
		ss<<"0\n";		// alteast one 1 in ith row
		cno++;

		// no two 1's in any row wale constraints:
		for (int j1=0; j1<onewalej.size(); j1++)
			for (int j2=j1+1; j2<onewalej.size(); j2++)
			{
				ss<<"-"<<to_string(variable(i,onewalej[j1]))<<" -"<<to_string(variable(i,onewalej[j2]))<<" 0\n";
				cno++;
			}
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
			{
				ss<<"-"<<to_string(variable(onewalei[i1],j))<<" -"<<to_string(variable(onewalei[i2],j))<<" 0\n";
				cno++;
			}
		onewalei.clear();
	}

	// edge constraints:
	int flag1=0, flag2 = 0;
	vector<int> V1,V2,v1,v2;
	for (int i1=0; i1<num_nodes_g; i1++)
		for (int i2=i1+1; i2<num_nodes_g; i2++)
		{
			v1 = g[i1].adjList;
			v2 = g[i2].adjList;
			flag1=0; 
			flag2 = 0;
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
					V1 = G[j1].adjList;
					V2 = G[j2].adjList;

					int flag3=0, flag4=0;
					if (find(V1.begin(), V1.end(), j2) != V1.end())
					 	flag3 = 1;
					if (find(V2.begin(), V2.end(), j1) != V2.end())
						flag4 = 1;

					if ((flag1 && !flag3) || (!flag1 && flag3) || (flag2 && !flag4) || (!flag2 && flag4))
					{
						ss<<"-"<<to_string(variable(i1,j1))<<" -"<<to_string(variable(i2,j2))<<" 0\n"; // both not one
						cno++;
					}

					// if ( flag1 && ( find(V1.begin(), V1.end(), j2) == V1.end()) ) 
					// 	outfile<<"-"<<to_string(variable(i1,j1))<<" -"<<to_string(variable(i2,j2))<<" 0\n"; // both not zero
					// else if ( flag2 && ( find(V2.begin(), V2.end(), j1) == V2.end()) ) 
					// 	outfile<<"-"<<to_string(variable(i1,j1))<<" -"<<to_string(variable(i2,j2))<<" 0\n"; // both not zero
				
				}
			}
		}
	outfile<<"p cnf "<<(num_nodes_G*num_nodes_g)<<" "<<cno<<endl;
	outfile<<ss.rdbuf();
	outfile.close();

	ofstream filetmp("temp.txt");
	filetmp<<num_nodes_G;
	filetmp.close();

}

int main(int argc, char const *argv[])
{
	string infilename = argv[1]; infilename += ".graphs";
	string outfilename = argv[1]; outfilename += ".satinput";
	takeInput(infilename);
	formMinisatInput(outfilename);
	// cout<<"LARGER GRAPH: \n";
	// unordered_map<int, Node>::iterator itr; 
	// for (itr = G.begin(); itr != G.end(); ++itr) 
	// { 
 //        cout << itr->first << '\t' << (itr->second).inDegree << " "<<(itr-> second).outDegree << '\n'; 
 //    }
 //    cout<<"-------\n";



	return 0;
}