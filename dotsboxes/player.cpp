// Dana Kallunki
// April 9, 2015
// CS 333 Spring 2015
// player.cpp 
// dots and boxes assiognment

#include "player.h"

// Construct a Player with nameId and reset score to zero
Player::Player(char nameIDValue)
{
	nameId = nameIDValue;
	score = 0;
}

// Destruct a Player 
Player::~Player()
{
}

// This virtual method is implemented in the sub-class
//virtual void Player::takeTurn(char& fromRow, char& fromCol,char& toRow, char& toCol,
//									Grid* gridPtr);

// Get player name Id
char Player::getNameId() const
{
	return nameId;
}

// Get player score
int Player::getScore() const
{
	return score;
}

// Set player score
void Player::setScore(const int scoreNumber)
{
	score = scoreNumber;
}
  

