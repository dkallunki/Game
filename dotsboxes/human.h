// Dana Kallunki
// April 9, 2015
// CS 333 Spring 2015
// human.h 
// dots and boxes assignment

#ifndef HUMAN_H
#define HUMAN_H

#include "player.h"


class Human : public Player {
	static const char HUMAN_ID = 'H';
public:
   // Constructor - for a Human
   Human() : Player(HUMAN_ID) {};

   // take a turn, returns from r,c and to r,c of edge
	virtual bool takeTurn(char& fromRow, char& fromCol, char& toRow, char& toCol,
							Grid* gridPtr);

   // Destructor
   ~Human() {};

private:

};

#endif
