# SubgraphIsomorphism
(Artificial Intelligence Course Assignment)
The subgraph isomorphism problem has been formulated and solved as a SAT problem using miniSat. 

### Problem Statement
There are two directed graphs G and G’. The graphs do not have self-edges. Find a one-one mapping M from nodes in G to nodes in G’ such that there is an edge from v1 to v2 in G if and only if there is an edge from M(v1) to M(v2) in G'.

### Input Format
Nodes are represented by positive integers starting from 1. Each line represents an edge from the first node to the second. Both graphs are presented in the single file, the larger first. The line with "0 0" is the boundary between the two.

### Output Format
The mapping will map each node of G into a node id for G’. The first numbers on each line represent a node as numbered in the smaller graph G, and the second number represents the node of the larger graph G’ to which it is mapped. If the problem is unsatisfiable output a 0.

### Graphs Generation
1. To generate an instance (G,G') and store the output in a file, run
'''
python generate.py n1 e1 n2 e2 > filename
'''
where n1,e1 are the number of nodes and edges in the bigger graph (G'), n2,e2 are the number of nodes and edges in the smaller graph (G). You can toggle the boolean flag 'guarantee_subgraph' to True to generate (G,G') where G is definitely a subgraph of G'
2. To check whether a mapping (in the given output format) is valid , run
'''
python check.py test.input test.output
'''
where test.input is in the described input format, and test.output is in the described output format.

### Running the code
1. To compile
'''
./compile.sh
'''

2. To run
'''
./run.sh testgraph
'''
This takes testgraph.graphs as input and outputs testgraph.mapping. It creates an intermediate testgraph.satinput which is fed into the minisat solver which outputs testgraph.satoutput, that is further processed to give the output mapping.




