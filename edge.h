#pragma once
#include <iostream>
using namespace std;
class vertex;
class edge
{
	int u;
	vertex* neighbour;

public:
	
	void setVaule(int val) {
		u = val;
	}
	int getVaule() {
		return u;
	}
	void setNeighbour(vertex* v) {
		neighbour = v;
	}
	vertex* getNeighbour() {
		return neighbour;
	}
};

