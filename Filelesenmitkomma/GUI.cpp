#include "Graph.h"
#include "GUI.h"
#include "Node.h"
#include "Edge.h"
#include "Connection.h"
#include <iostream>
#include <deque>
#include <fstream> // Um Files zu lesen.
#include <string>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <vector>
#include <ctime>



GUI::GUI()
{
}

int GUI::showMenu()
{
	cout << " Bitte waehlen Sie eine Aktion aus" << endl
		<< "1- Geben Sie den Dateinamen zum Auslesen" << endl
		<< "2- Ausgeben des Netzes von Plaetzen und Strassen" << endl
		<< "3- Plaetze und Strassen alphabetisch sortiert ausgeben" << endl
		<< "4- Ausgeben des optimalen Platzes fuer die neue Feuerwehrstation" << endl
		<< "5- Programm beenden" << endl;

	cout << "Eingabe: ";
	int eingabe;
	cin >> eingabe;
	return eingabe;
}

void GUI::Dateieinlesen()
{
	fstream file;
	string FileName;
	cout << " Geben Sie den Dateinamen an " << endl;
	cin >> FileName;

	file.open(FileName, ios::in);
	if (!file.good())
	{
		cerr << "Fehler beim Aufmachen" << endl;
		return;
	}
	else
	{
		cout << "Datei geoffnet" << endl;
		string zeile;
		string word;
		std::vector<string> tokens;
		while (getline(file, zeile))
		{
			//istringstream iss(zeile);
			//vector<string> tokens{ istream_iterator<string> {iss}, istream_iterator<string>{} };
			istringstream iss(zeile);
			while (getline(iss, word, ','))
			{

				tokens.push_back(word);
			}


			if (this->findNode(tokens[0]) == NULL)
				this->addNode(new Node(tokens[0]));
			if (this->findNode(tokens[2]) == NULL)
				this->addNode(new Node(tokens[2]));
			this->addEdge(new Connection(*(this->findNode(tokens[0])), *(this->findNode(tokens[2])), stod(tokens[3]), tokens[1]));
			this->addEdge(new Connection(*(this->findNode(tokens[2])), *(this->findNode(tokens[0])), stod(tokens[3]), tokens[1]));
			tokens.clear();
		}
	}
	file.close();

}
void GUI::NetzZeigen()
{
	// Die IDs von den Nodes durchgehen

	for (auto i : this->getNodes())
	{
		cout << i->getID() << endl;
	}
	for (auto i : this->getEdges())
	{
		Connection* temp = dynamic_cast <Connection*>(i);
		cout << temp->getSrcNode().getID() << "---> " << temp->getDstNode().getID() <<
			" \n Distance is " << temp->getdistance() << "Km " <<
			" \n U-Bahn " << temp->getname() << endl;

		//cout << i->getSrcNode().getID() << "---> " << i->getDstNode().getID() << endl; 
		//cout << temp->toString() << endl; um eine Zusammenfassung zu zeigen. 
		// die Methode toString() fasst alle SrcNode und DstNode zusammen

	}
	cout << this->getEdges().size() << endl;

}
GUI::~GUI()
{
}
