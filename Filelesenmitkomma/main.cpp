#include "Graph.h"
#include "GUI.h"
#include <iostream>



using namespace std; 


int main() 
{

	GUI gui; // GUI aufrufen

	bool bRunning = true;

	// Endlosschleife, bis bRunning auf 'false' gesetzt wird
	while (bRunning)
	{
		int menuEntry = gui.showMenu();

		// Hinweis: Die Fallunterscheidung geht auch mit Switch-Case (siehe C-Programmierung)



		switch (menuEntry)
		{
		case 1:
		
			gui.Dateieinlesen();
			break;

		case 2:
			gui.NetzZeigen(); 
			break;
		case 3:
			
			break;
		case 4:
			
			break;

		case 5:
			bRunning = false;
			break;

		default:
			break;
		}
	}

	system("pause"); 
	return 0; 

}