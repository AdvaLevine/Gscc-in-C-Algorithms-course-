#include "graph.h"

//this function is cleanning the graph from data
void graph::makeEmptyGraph(int n) {
	if (numOfEdges != 0) {
		for (int i = 0; i < AdjList.size(); i++) {
			if (AdjList[i].getNumOfEdges() != 0) {
				AdjList[i].removeAllEdges();
				AdjList[i].setVisited(false);
			}
		}
	}
	AdjList.clear();
	numOfVertices = 0;
	numOfEdges = 0;
}
//this function is adding a vertex
void graph::addVertex(int v) {
	bool found = false;
	for (int i = 0; i < AdjList.size(); i++) {
		if (v == AdjList[i].getValOfVertex()) {
			found = true;
			break;
		}
	}
	if (!found) {
		vertex tmp;
		tmp.setVertex(v);
		AdjList.push_back(tmp);
	}
	else {
		throw invalidInputException();	
	}
}

//this function is for checking is edge exists
bool graph::isAdjacent(vertex u, vertex v) {
	bool found = false;
	for (int i = 0; i < numOfVertices; i++) {
		if (u.getValOfVertex() == AdjList[i].getValOfVertex())
		{
			for (int j = 0; j < AdjList[i].getNumOfEdges(); j++) {
				vector<edge> listOfEdges = AdjList[i].getListOfEdges();
				if (v.getValOfVertex() == listOfEdges[j].getVaule()) {
					found = true;
				}
			}
		}
	}
	return found;
}
//this function returns the adjlist
vector<edge> graph::getAdjList(int u) {
	bool found = false;
	for (int i = 0; i < AdjList.size(); i++) {
		if (u == AdjList[i].getValOfVertex()) {
			found = true;
			return AdjList[i].getListOfEdges();
		}
	}
	//if the loop completes without finding the vertex, print an error message and handle the situation
	throw invalidInputException();

}
//this function adds an edge to the graph
void graph::addEdge(vertex* u, vertex* v) {
	if (u != nullptr && v != nullptr) {//checking if vertex exists
		if (u != v) {//checking if not a self loop
			for (int i = 0; i < AdjList.size(); i++) {
				if (u->getValOfVertex() == AdjList[i].getValOfVertex())
				{
					if (!AdjList[i].hasEdge(v->getValOfVertex())) {
						AdjList[i].addEdge(v);//adding the edge
						return;
					}
					else {//already exists 
						throw invalidInputException();
					}
				}

			}
		}
	}
	throw invalidInputException();
}
//this function is for removing the edge
void graph::removeEdge(vertex u, vertex v) {
	bool found = false;
	for (int i = 0; i < AdjList.size(); i++) {
		if (u.getValOfVertex() == AdjList[i].getValOfVertex())
		{
			AdjList[i].removeEdge(v.getValOfVertex());//remove edge
			found = true;
		}
	}
	if (!found) {//didnt find edge
		throw invalidInputException();

	}
}
//this is a function that create the finish list using dfs on the graph 
vector<vertex> graph::DFSForFinishList() {
	finishList.clear(); 

	for (int i = 0; i < AdjList.size(); ++i) {
		if (!AdjList[i].getVisited()) {
			DFSForFinishListHelper(AdjList[i]);
		}
	}
	for (int i = 0; i < AdjList.size(); i++) {//after doing the first dfs we need to do another one so we reset the visited to false
		finishList[i].setVisited(false);
		AdjList[i].setVisited(false);
	}
	return finishList;
}
//this is a helper func for the finish list creation
void graph::DFSForFinishListHelper(vertex& v) {
	v.setVisited(true);
	vector<edge> listOfEdges = v.getListOfEdges();

	for (int i = 0;i< listOfEdges.size();i++) {
		if (!listOfEdges[i].getNeighbour()->getVisited())
		{
			DFSForFinishListHelper(*(listOfEdges[i].getNeighbour()));
		}
	}

	finishList.push_back(v);
}
//this is a function that returns the vertex
vertex* graph::getVertex(int val) {
	for (vertex& v : AdjList) {
		if (v.getValOfVertex() == val) {
			return &v; 
		}
	}
	return nullptr;
}
//this function creates a trasposed graph
graph graph::transpose(){
	graph GT;
	GT.makeEmptyGraph(numOfVertices);
	GT.setNumOfVertices(numOfVertices);
	GT.setNumOfEdges(numOfEdges);

	for (int i = 0; i < AdjList.size(); i++) {//copy adjlist only
		GT.addVertex(AdjList[i].getValOfVertex());
	}

	for (int i = 0; i < AdjList.size(); i++)//update the edges
	{
		vector<edge> listOfEdges = AdjList[i].getListOfEdges();
		for (int u = 0; u < listOfEdges.size(); u++)
		{
			GT.addEdge(listOfEdges[u].getNeighbour(), &GT.AdjList[i]);
		}
	}
	GT.setFinishList(finishList);//update finish list
	return GT;
}
//this function is creating the gscc graph for the graph
graph* graph::findGscc() {
	DFSForFinishList();  // First DFS to compute finish times
	reverseFinishList(); // Reverse the finish list to get the order for the second DFS

	graph GT = transpose(); // Get the transpose of the graph
	graph* gscc = new graph();
	gscc->makeEmptyGraph(numOfVertices);

	GT.parents.clear();

	int count = 0;
	//go through finish list
	for (auto& v : GT.finishList) {
		vertex* v_ptr = GT.getVertex(v.getValOfVertex());
		if (v_ptr && !v_ptr->getVisited()) {//if vertex not visited or null
			count++;
			v_ptr->setParent(v_ptr);//set parent for v
			gscc->addVertex(v_ptr->getValOfVertex());//we add vertex to gscc
			GT.DFSForParentList(*v_ptr, *v_ptr, gscc, count);
		}
	}

	gscc->setNumOfVertices(count);//set num of vertices

	return gscc;
}
//this function is a helper function that uses the serir Kosaraju's algorithm to help find the gscc 
void graph::DFSForParentList(vertex& v, vertex& parent, graph* gscc, int count) {
	v.setVisited(true);
	v.setParent(&parent);

	for (auto& edge : v.getListOfEdges()) {
		vertex* neighbor = edge.getNeighbour();
		if (neighbor->getParent() == nullptr) {
			neighbor->setParent(&parent);
		}

		if (count > 1 && neighbor->getParent()->getValOfVertex() != parent.getValOfVertex()) {
			bool edgeExists = false;
			for (auto& gsccVertex : gscc->AdjList) {
				if (gsccVertex.getValOfVertex() == neighbor->getParent()->getValOfVertex()) {
					for (auto& gsccEdge : gsccVertex.getListOfEdges()) {
						if (gsccEdge.getVaule() == parent.getValOfVertex()) {
							edgeExists = true;
							break;
						}
					}
					if (!edgeExists) {
						gsccVertex.addEdge(&parent);
						gscc->setNumOfEdges(gscc->getNumOfEdges() + 1);
					}
					break;
				}
			}
		}

		if (!neighbor->getVisited()) {
			DFSForParentList(*neighbor, parent, gscc, count);
		}
	}
}
//this function is for validation of the vertice num and edges num
void graph::validationCheck(int n, int m) {
	if (n < 0 || m < 0) {
		throw invalidInputException();
	}
}




