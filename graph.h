#pragma once


#include "vertex.h"
#include "edge.h"
#include <algorithm>
#include "exception.h"
class graph
{
	vector<vertex> AdjList;
	int numOfVertices;
	int numOfEdges;
	vector<vertex> finishList;
	vector<int>parents;

public:

	void validationCheck(int n, int m);
	void DFSForParentList(vertex& v, vertex& parent, graph* gscc, int count);
	void setFinishList(vector <vertex> list) { finishList = list; }
	void setNumOfVertices(int n) { numOfVertices = n; }
	void setNumOfEdges(int m) { numOfEdges = m; }
	int getNumOfVertices() { return numOfVertices; }
	int getNumOfEdges() { return numOfEdges; }
	void makeEmptyGraph(int n);
	bool isAdjacent(vertex u, vertex v);
	void addVertex(int v);
	vector<vertex>getVertList() { return AdjList; }
	void addEdge(vertex* u, vertex* v);
	vector<edge> getAdjList(int u);
	void removeEdge(vertex u, vertex v);
	graph* findGscc();
	vertex* getVertex(int val);
	void reverseFinishList() { reverse(finishList.begin(), finishList.end()); }
	vector<vertex> DFSForFinishList();
	void DFSForFinishListHelper(vertex& v);
	graph transpose();

};

