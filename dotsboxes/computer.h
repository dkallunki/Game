// Dana Kallunki
// April 9, 2015
// CS 333 Spring 2015
// computer.h 
// dots and boxes assignment

#ifndef COMPUTER_H
#define COMPUTER_H

#include "player.h"
#include "grid.h"

class Computer: public Player {
	static const char COMPUTER_ID = 'C';
public:
	// Constructor - for a Computer player of ID 'C'
	Computer(): Player(COMPUTER_ID) {};

	// take a turn, returns the from r,c and to r,c edge data
	virtual bool takeTurn(char& fromRow, char& fromCol, char& toRow, char& toCol, Grid * gridPtr);

	// Destructor
	~Computer() {};

private:

};

#endif
