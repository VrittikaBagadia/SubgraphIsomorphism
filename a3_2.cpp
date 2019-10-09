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
int main(int argc, char const *argv[])
{
	string fname1 = argv[1]; fname1 += ".graphs";
	string fname2 = argv[1]; fname2 += ".satoutput";
	string outfilename = argv[2];
	ifstream infile1(fname1);
	ifstream infile2(fname2);
	ofstream outfile(outfilename);
	
	int num_nodes_G = -1;
	int n1, n2;
	while (true)
	{
		infile1>>n1>>n2;
		if (n1==0)
			break;
		num_nodes_G = max(num_nodes_G,max(n1,n2));
	}
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
				outfile<<(n-1)/num_nodes_G + 1<<" "<<(n-1)%num_nodes_G+1<<endl;
		}
	}
	else if (s == "UNSAT")
	{
		outfile<<0;
	}
	infile1.close();
	infile2.close();
	outfile.close();
	return 0;
}