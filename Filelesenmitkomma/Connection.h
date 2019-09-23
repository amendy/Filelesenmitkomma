#pragma once
#include "Graph.h"
#include "Edge.h"
#include <iostream>
#include <string>

using namespace std; 

class Connection : public Edge
{
public:
	Connection( Node& rSrc, Node& rDst, double distance, string name): Edge(rSrc, rDst), m_distance(distance), m_name(name)
	{
		m_geschwindigkeit = 45;
	}

	/*virtual double getWeight()
	{

	}*/
	string getname() { return m_name;  }
	double getdistance() { return m_distance; }



private: 
	double m_distance; 
	string m_name; 
	double m_geschwindigkeit; 





};


