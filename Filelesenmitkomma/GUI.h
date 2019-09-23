#pragma once
#include "Graph.h"
#include "Connection.h"
#include "Node.h"
#include "Edge.h"
#include <vector>
#include <iostream>

using namespace std; 
class GUI :
	public Graph
{
public:
	int showMenu();
	void Dateieinlesen();
	void NetzZeigen();
	GUI();
	~GUI();

private: 
};

