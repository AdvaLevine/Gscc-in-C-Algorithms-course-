#include "vertex.h"
//this function is for adding edge
void vertex::addEdge(vertex* u) {
	edge e;  
	e.setVaule(u->getValOfVertex());
	e.setNeighbour(u);
	edges.push_back(e); 
	numOfEdges++;
}
//this function is for removing edge
void vertex:: removeEdge(int u) {
	for (int i = 0; i < edges.size(); i++) {
		if (u == edges[i].getVaule()) {
			for (int j = i; j < numOfEdges - 1; j++) {
				edges[j] = edges[j + 1];
			}
			numOfEdges--;
		}
	}
}
//this function returns if the edge exists 
bool vertex::hasEdge(int v) {
	for (int i = 0; i < edges.size(); i++) {
		if (edges[i].getVaule() == v) {
			return true;
		}
	}
	return false; 
}
