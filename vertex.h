#pragma once
#include <vector>
#include <iostream>
using namespace std;
#include "edge.h"

class edge;
class vertex
{
	int v;
	vector<edge>edges;
	int numOfEdges;
	bool visited;
	vertex* parent;

public:
	vertex* getParent() {
		return parent;
	}
	void setParent(vertex* p) {
		parent = p;
	}
	int getValOfVertex() {
		return v;
	}
	int getNumOfEdges() {
		return numOfEdges;
	}
	void setVertex(int number) {
		v = number;
	}
	void setVisited(bool value) {
		visited = value;
	}
	bool getVisited() {
		return visited;
	}
	vector<edge> getListOfEdges() {
		return edges;
	}
	void addEdge(vertex* u);
	void removeAllEdges() {
		edges.clear(); 
		numOfEdges = 0;
	}
	void removeEdge(int u);
	bool hasEdge(int v);

};

