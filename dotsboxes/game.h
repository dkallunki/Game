// Dana Kallunki
// April 9, 2015
// CS 333 Spring 2015
// game.h
// dots and boxes assiognment

#ifndef GAME_H
#define GAME_H

#include "human.h"
#include "computer.h"
#include "grid.h"



class Game {

	static const int GAME_SIZE_MIN = 2;
	static const int GAME_SIZE_MAX = 8;
	static const int GAME_PLAYER_MAX = 2;
	static const int GAME_PLAYER_HUMAN = 0;
	static const int GAME_PLAYER_COMPUTER = 1;

public:
	// Constructor - a Game for the game
	Game();

	// Run the game sequence.
	void run();

	// Pre Game Processing.
	bool preGame();

	// Turn By Turn Processing.
	void turnByTurn();

	// Post Game Processing.
	void postGame();

	// Print the Grid.
	void printGrid();

	// Print The scores.
	void printScores();

	// Destructor
	~Game();

private:

	int size;			// grid N for N x N size
	int currentPlayer;	// 0=human's turn, 1=computer's turn
	Grid* gridPtr;		// Grid pointer
	Human human;		// Human Player
	Computer computer;	// Computer Player
};


#endif
