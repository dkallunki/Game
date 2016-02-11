// Dana Kallunki
// April 9, 2015
// CS 333 Spring 2015
// human.cpp 
// dots and boxes assiognment

#include <iostream>

using namespace std;

#include "human.h"

// This virtual method is implemented here in this sub-class
// of the parent base class called Player
// takes a human turn and returns the from r,c and to r,c data

bool Human::takeTurn(char& fromRow, char& fromCol, char& toRow, char& toCol, Grid* gridPtr)
{
	char fromRowIn = ' ';
	char fromColIn = ' ';
	char toRowIn = ' ';
	char toColIn = ' ';

	cout << "What two dots would you like to connect? (Q to quit) \n";
	cin.clear();
	cin >> fromRowIn;
	if(fromRowIn == 'Q')
		return false;
	cin.clear();
	cin >> fromColIn;
	cin.clear();
	cin >> toRowIn;
	cin.clear();
	cin >> toColIn;
	cin.clear();
	cout << " ok got em\n";
	fromRow = fromRowIn;
	fromCol = fromColIn;
	toRow   = toRowIn;
	toCol   = toColIn;
	return true;
}


