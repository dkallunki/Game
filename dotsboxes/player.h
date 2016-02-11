// Dana Kallunki
// April 9, 2015
// CS 333 Spring 2015
// player.h 
// dots and boxes assiognment

#ifndef PLAYER_H
#define PLAYER_H

#include "grid.h"

class Player {
public:
	// construct player with a ownerId (e.g., 'C' or 'H')
	Player(char nameIDValue);

	// Take a turn, returns from r,c and to r,c edge data.
	virtual bool takeTurn(char& fromRow, char& fromCol, char& toRow, char& toCol,
							Grid* gridPtr) {return true;};
 
	// Get the player namw Id.
	char getNameId() const;

	// Get the player score.
	int getScore() const;

	// Set the player score
	void setScore(const int scoreNumber);

	// Destructor
	virtual ~Player();

private:

	int score;		// player score
	char nameId;	// player name id ( e.g., " ", "C" , "H" )
};


#endif
