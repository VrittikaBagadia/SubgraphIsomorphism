#include <fstream>
#include <iostream>  
#include <vector> 
#include <algorithm>
#include <string.h>
#include <unordered_map> 
#include <sstream>
using namespace std;
int main(int argc, char const *argv[])
{
	// string fname1 = argv[1]; fname1 += ".graphs";
	string fname1="temp.txt";
	string fname2 = argv[1]; fname2 += ".satoutput";
	string outfilename = argv[1]; outfilename+=".mapping";
	ifstream infile1(fname1);
	ifstream infile2(fname2);
	ofstream outfile(outfilename);
	
	int num_nodes_G;
	int n1, n2;
	infile1>>num_nodes_G;
	// while (true)
	// {
	// 	infile1>>n1>>n2;
	// 	if (n1==0)
	// 		break;
	// 	num_nodes_G = max(num_nodes_G,max(n1,n2));
	// }

	string s;
	int n;
	infile2>>s;
	if (s == "SAT")
	{
		while (true)
		{
			infile2>>n;
			if (n==0)
				break;
			if (n > 0)
				outfile<<((n-1)/num_nodes_G) + 1<<" "<<((n-1)%num_nodes_G)+1<<endl;
		}
	}
	else if (s == "UNSAT")
	{
		outfile<<0<<endl;
	}
	infile1.close();
	infile2.close();
	outfile.close();
	return 0;
}