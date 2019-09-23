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

/*
//Netzeigen C++ und Sortieren

// Netzeigen zuerst und sortiert bleiben.
void GUI:: Netzeigen ()
{
list <Node*>sortedNode = this->getNodes();
list <Edge*> sortedEdges = this->getEdges();
// Liste ist erstmal erstellt aber leer.

// Liste alphabetisch sortieren

cout << "alphabetisch: " << endl;

sortedNode.sort([](const Node* a, const Node* b) {return a->getID() < b->getID(); });

  // Jetzt hier unten geht es um speichern und cout

  for (auto tmpIt = sortedNode.begin(); tmpIt != sortedNode.end(); tmpIt++)
  {
  NodeAufgabe* tmpNode = static_cast<NodeAufgabe*> (*tmpIt);
		sortedNodeAufgabe.push_back(tmpNodeAufgabe);

		cout << tmpNodeAufgabe->getID() << " ; Type: " << tmpNodeAufgabe->getTypNaame() << endl;
  }
  for (auto tmpEdge = sortedEdge.begin(); tmpEdge != sortedEdge.end(); tmpEdge++)
		{
			Connection* tmpConnection = dynamic_cast<Connection*> (*tmpEdge);
			if (tmpConnection->getSrcNode().getID() == tmpHaffen->getID())
			{
				cout << "	" << tmpConnection->toString() << " ; Distance: "
					<< tmpConnection->getDistance() << endl;
			}

		}

 }
 // Sort by Type
 sortedNode.sort([](Node* a, Node* b)
 {
 return	static_cast<NodeAufgabe*>(a)->getTyp() < static_cast<NodeAufgabe*>(b)->getTyp();
 });

 //Oder  Netz einfach sortieren und gezeigt werden

 void GUI::Alphabetischsortieren()
{
	list<Node*> sorted = this->getNodes();
	list<Edge*> edgeList = this->getEdges();

	// Node zu sortieren und eingeben...
	sorted.sort([](const Node* a, const Node* b) { return a->getID() < b->getID(); });

	for (auto nodeIt = sorted.begin(); nodeIt != sorted.end(); nodeIt++)
	{
		cout << " " << (*nodeIt)->getID() << endl;
		for (auto edgeIt = this->getEdges().begin(); edgeIt != this->getEdges().end(); edgeIt++)
		{
			if ((*edgeIt)->getSrcNode().getID() == (*nodeIt)->getID())
			{
				std::cout << "\t" << (*edgeIt)->toString() << " " << (*edgeIt)->getWeight() << "Km" << std::endl;
			}

		}
	}
}


NetzZeigen komplett


void GUI::NetzZeigen()
{
	// Die IDs von den Nodes durchgehen

	for (auto i: this ->getNodes())
	{
		cout << i->getID() << endl;
	}
	for (auto i: this->getEdges())
	{
		Connection* temp = dynamic_cast <Connection*>(i);
		cout << temp->getSrcNode().getID() << " is connected to " << temp->getDstNode().getID() << " Distance is " << temp->getdistance() << " U-Bahn " << temp->getname() << endl;

		cout << i->getSrcNode().getID() << " is connected to " << i->getDstNode().getID() << endl;

	}

}

Files Open Input and Output.



void GUI::Dateieinlesen()
{
	string FileName;
	cout << " Geben Sie den Dateiname an" << endl;
	cin >> FileName;
	fstream file;
	file.open(FileName);
	if (file.good())
	{
		string zeile;
		cout << " File is geoffnet" << endl;
		getline(file, FileName); // Gib die erste Zeile des Files zurueck
		while (getline(file, zeile))
		{
			istringstream iss(zeile);
			vector<string> tokens{ istream_iterator<string>{iss},
				  istream_iterator<string>{} };
			if (this->findNode(tokens[0]) == NULL)
				this->addNode(new Node(tokens[0]));
			if (this->findNode(tokens[2]) == NULL)
				this->addNode(new Node(tokens[2]));


			this->addEdge(new Connection(*(this->findNode(tokens[0])), *(this->findNode(tokens[2])), stod(tokens[3]), tokens[1]));
			this->addEdge(new Connection(*(this->findNode(tokens[2])), *(this->findNode(tokens[0])), stod(tokens[3]), tokens[1]));


		}
	}
	else
		cerr << "File ist nicht geoffnet" << endl;




	}

	Files Open Input and Output not Space between but with comma.

	void GUI::Dateieinlesen()
{
	string FileName;
	cout << " Geben Sie den Dateiname an" << endl;
	cin >> FileName;
	fstream file;
	file.open(FileName);
	if (file.good())
	{
		string zeile;
		cout << " File is geoffnet" << endl;
		getline(file, FileName); // Gib die erste Zeile des Files zurueck
		while (getline(file, zeile))
		{
			istringstream iss(zeile);
			vector<string> tokens{ istream_iterator<string>{iss},
				  istream_iterator<string>{}, istream_iterator<string>( std::cout, ",") };
			if (this->findNode(tokens[0]) == NULL)
				this->addNode(new Node(tokens[0]));
			if (this->findNode(tokens[2]) == NULL)
				this->addNode(new Node(tokens[2]));


			this->addEdge(new Connection(*(this->findNode(tokens[0])), *(this->findNode(tokens[2])), stod(tokens[3]), tokens[1]));
			this->addEdge(new Connection(*(this->findNode(tokens[2])), *(this->findNode(tokens[0])), stod(tokens[3]), tokens[1]));


		}
	}
	else
		cerr << "File ist nicht geoffnet" << endl;




	}

	//Files Open Open and write inside the files and save it.


	// basic file operations
#include <iostream>
#include <fstream>
using namespace std;

int main () {
  ofstream myfile;
  myfile.open ("example.txt");
  myfile << "Writing this to a file.\n";
  myfile.close();
  return 0;

}

// File read and put at the last line

#include <fstream>
 using namespace std;
int main()
{
 ofstream outfile;

  outfile.open("test.txt", std::ios_base::app);
  outfile << "Data"; // What i put inside the file
  return 0;
}


// Dijstra Algorithmus

void GUI::optimaleVerbindung()
{
void GUI::Reisebuchen() {
	double preis = 0.0;
	double Minutes = 0.0; // Minute ist nicht benutzt
	// Funktionen der GUI
	// Zuerst Eingabe fördern laut Aufgabe
	std::cout << " Bitte geben Sie Ihre Startcity ein" << std::endl;
	Node* rSrc = readCity();
	std::cout << " Bitte geben Sie Ihre Zielcity ein" << std::endl;
	Node* rDst = readCity();

	/* Dann kommst deque von Edge, die den ganzen Weg mit Dijkstra optimiert*/
/*
std::deque<Edge*>path;
findShortestPathDijkstra(path, *rSrc, *rDst);
// For Schleife in einer Liste Edge 
for (std::deque<Edge*>::iterator it = path.begin(); it != path.end(); it++)
{
	if (FlugRoute* pFlight = dynamic_cast<FlugRoute*>(*it))
	{
		preis += pFlight->getPreis();
		std::cout << "Flug: " << pFlight->toString() << "; Dauer: " << pFlight->getMinutes() << "min" << std::endl;
	}
	// ist es eine Busverbindung?
	else if (BusRoute* pBus = dynamic_cast<BusRoute*>(*it))
	{
		preis += pBus->getPreis();
		std::cout << "Bus: " << pBus->toString() << "; Dauer: " << pBus->getMinutes() << "min" << std::endl;
	}
}
cout << "preis is " << preis << endl;
}
}
// Second Dijkstra IT-Spezialist 
{
cout << "Bitte Ziel Ort auswaehlen" << endl << "Ziel Ort: ";

while (!(cin >> zielOrt)) // Falls Buschstabe statt Zahl eingetragen
{
	cout << "Bitte Digit eingeben..." << endl;
	cin.clear();
	cin.ignore(132, '\n');
}
cout << endl;
		}
rZielOrt = NodeList[zielOrt - 1];
deque<Edge*> path;
globalFaktor = 2;

g.findShortestPathDijkstra(path, *rStartOrt, *rZielOrt);
rStartOrt = rZielOrt;

for (std::deque<Edge*>::iterator it = path.begin(); it != path.end(); it++)
{
	Connection* pTeilConnection = dynamic_cast<Connection*>(*it);

	std::cout << "Teilroute: " << pTeilConnection->toString() <<
		";  Teilzeit: " << pTeilConnection->getWeight() <<
		" Kost: " << ((pTeilConnection->getDistance() * 30)) << " Cent" << endl;

	gesamtKost += (pTeilConnection->getDistance()) * 30;
	gesamtZeit += pTeilConnection->getWeight();
}
cout << " Gesamt Einnahme: " << (gesamtKost / 100) + 50 << " Euro" << endl;
cout << "Gesamt Zeit: " << gesamtZeit << endl;

string nameDerKunde;

cout << " Bitte Name der Kunde eintragen: " << endl;
cin >> nameDerKunde;

fahrListe.m_nameDerKunde = nameDerKunde;
fahrListe.m_fahrKost = gesamtKost / 100;
fahrListe.m_Einnahme = (gesamtKost / 100) + 50;
fahrListe.m_ZielOrt = rZielOrt;

tagFahrt.push_back(fahrListe);
	}
}

// Kimoran Spiel

void GUI::optimaleVerbindung(Node ziel, int spielerType)
{
	std::deque<Edge*>*rPath = new std::deque<Edge*>();
	Node spielerPosition; // for the case Default Constructor should be created on Inseln
	Spieler* mensch = new Spieler();
	for (Spieler *temp : m_spieler) {
		if (temp->getType() == spielerType) {
			//temp->getPosition(); 
			spielerPosition = temp->getPosition();
			mensch = temp;
		}
	}

	double summe = 0;
	this->findShortestPathDijkstra(*rPath, spielerPosition, ziel);
	for (auto edge : *rPath) {
		summe = edge->getWeight();
		cout << "Source Inseln :" << edge->getSrcNode().getID() << " Zur Inseln : " << edge->getDstNode().getID() << endl;
		Inseln* weg = static_cast<Inseln*>(&(edge->getDstNode()));
		if (weg->get_schatz() == true)
		{
			cout << "you are winner" << endl;
			mensch->setPosition(static_cast<Inseln&>(ziel));
			system("pause");
			std::exit(0);
			// End the programm
		}
		if (weg->get_taler() > 0) {
			mensch->setTaler(weg->get_taler() + mensch->getTaler());
		}
		if (typeid(*edge).name() == "Bruecke")
		{
			Connection* temp = dynamic_cast<Connection*>(edge);
		}
		if (typeid(*edge).name() == "Faehre")
		{
			Connection* temp = dynamic_cast<Connection*>(edge);

		}
		if (typeid(*edge).name() == "Tunnel")
		{
			Connection* temp = dynamic_cast<Connection*>(edge);
		}
	}
	if (summe > mensch->getTaler())
	{
		cout << "you loosed the game" << endl;

	}
	else
	{
		mensch->setTaler(mensch->getTaler() - summe);

		mensch->setPosition(static_cast<Inseln&>(ziel));
	}
	this->computerRandomSpiel();

}

// Dijkstra Klausur Sommer 


void GUI::optimaleVerbindung()
{
	globalFaktor = 2;

	for (auto i : this->getNodes())
	{
		for (auto o : this->getNodes())
		{
			std::deque<Edge*>path;
			this->findShortestPathDijkstra(path, *i, *o);
			double summeDistance = 0;
			for (std::deque<Edge*>::iterator it = path.begin(); it != path.end(); it++)
			{
				if (Connection* pConnection = dynamic_cast<Connection*>(*it))
				{

					summeDistance += pConnection->getdistance();
				}

			}
			datei.push_back({ i->getID(), o->getID(), summeDistance });

		}
	}
}


Main C++ Code

#include "GUI.h"
#include "Node.h"
#include "Edge.h"
#include "Graph.h"
#include <iostream>



using namespace std;


int main ()

{
 GUI gui;
 // Nodes and Edges hier bauen.

 bool bRunnning = true;


 while (bRunnning)
{

int menuEntry= gui.showMenu();

switch(menuEntry)
{
 case 1:
	gui.function1();
 break;

 case n:
	bRunnning = false;
	break;

	default:
	break;
}
}


}

ShowMenu Methode in GUI


int GUI::showMenu()
{
	cout << " Bitte waehlen Sie eine Aktion aus" << endl
		<< "1- : " << endl
		<< "2- : " << endl
		<< "3- : " << endl
		<< "4- : " << endl
		<< "5- : " << endl
		<< "6- Programm beenden" << endl;


	cout << "Eingabe: ";
	int eingabe;
	cin >> eingabe;
	return eingabe;
}

*/
