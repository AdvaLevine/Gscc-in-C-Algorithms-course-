#include <iostream>
#include <stdlib.h>
#include "graph.h"
using namespace std;


/*This program get a number of vertices and edges to a simple direcional graph and returns the gscc graph
input is: n-number of vertices, m-number of edges, and then m edges (v,u)
the prohgram uses the algorithms we learn in class to create the gscc in the most efficient way possible- tetha (n+m)
if the input isnt correct- two of the same edges, not enough vertices, neative input etc, the program exits with a message*/
int main() {
	try {
		int n = 0, m = 0; //n is num of vertices in the graph and m is num of edges in the graph
		graph G, * GSCC;

		//cout << "Please enter how many vertices you want the graph to have: ";
		cin >> n;
		//cout << "Please enter how many edges you want the graph to have: ";
		cin >> m;
		//update the graph
		G.validationCheck(n, m);
		G.makeEmptyGraph(n);
		G.setNumOfVertices(n);
		G.setNumOfEdges(m);

		for (int i = 1; i <= n; i++) {
			G.addVertex(i);
		}
		//cout << "Please enter the edges now: " << endl;

		for (int i = 0; i < m; i++) {
			int u = 0, v = 0;
			cin >> u >> v;

			vertex* vertexU = G.getVertex(u);
			vertex* vertexV = G.getVertex(v);

			G.addEdge(vertexU, vertexV);//add edge if possible
		}
		if (G.getNumOfVertices() != G.getVertList().size()) {
			throw invalidInputException();
		}
		//create the gscc graph
		GSCC = G.findGscc();
		//cout << endl;
		cout << GSCC->getNumOfVertices() << " " << GSCC->getNumOfEdges() << endl;
		G.makeEmptyGraph(G.getNumOfVertices());
		GSCC->makeEmptyGraph(GSCC->getNumOfVertices());
		delete(GSCC);
	}
	catch (const graphException&) {
		cout << "invalid input " << endl;
		exit(1);
	}

	return 0;

}

