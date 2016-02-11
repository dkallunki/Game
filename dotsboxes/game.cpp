// Dana Kallunki
// April 9, 2015
// CS 333 Spring 2015
// Game.cpp
// dots and boxes assignment

#include <iostream>
using namespace std;
#include "game.h"

// Construct a Game
Game::Game()
{
	currentPlayer = GAME_PLAYER_HUMAN;  // init start with human turn
	size = GAME_SIZE_MIN;				// init to min until size is available
	gridPtr = 0;						// init to NULL PTR until size is available
}

// Destruct a Game
Game::~Game()
{
	if(gridPtr)				// if we new'd a Grid object
		delete gridPtr;		// then delete it, so no mem leak
}

// Run the Game sequence.
void Game::run()
{
	bool result = false;

	// Pre Game processing is first
	result = preGame();

	// if preGame cin eof exit immediately
	if (result == false)
		return;
	
	// Game: Turn By Turn Processing is next
	turnByTurn();
	
	// Post Game Processing is last
	postGame();
	
	return;
}

// Pre Game Processing.
bool Game::preGame()
{
	bool done = false;
	while(done == false)
	{
		cout << "What size grid would you like? (2..8) ";
		cin >> size;
		// if eof exit immediately
		if(cin.eof())
			return false;
		if(size >= GAME_SIZE_MIN && size <= GAME_SIZE_MAX)
			done = true;
		else
			cout << "Sorry, try again.\n";
	}
	gridPtr = new Grid(size);
	return true;
}

// Turn By Turn Processing.
void Game::turnByTurn()
{
	int filledBoxes = 0;
	bool done = false;
	bool result = false;
	bool playerDone = false;
	char fromRow = 'a';
	char fromCol = '1';
	char toRow = 'a';
	char toCol = '1';
	char nameId = ' ';
	char edgeNameId = ' ';
	Player * playerPtr = 0;

	while(done == false)
	{
		printGrid();
		printScores();
		if (gridPtr->getEdgeCount() > 0)  				// if edges left to select
		{
			if(currentPlayer == GAME_PLAYER_HUMAN)  	// if human player set player object
				playerPtr = &human;
			else   									   	// if computer player set computer object
				playerPtr = &computer; 					// player turns alternate if no box captured
			nameId = playerPtr->getNameId();  			// ids: are human = C computer = C
			playerDone = false;
			while(playerDone == false)
			{
				result = playerPtr->takeTurn(fromRow, fromCol, toRow, toCol, gridPtr);
				if(result == false)  					// if false, human did "Q" and game is over
					playerDone = true;
				else // if result is true, see if a valid row/col from/to edge
				{
					result = gridPtr->getEdge(fromRow, fromCol, toRow, toCol, edgeNameId);
					if(result == false || edgeNameId != ' ')
						cout << "Sorry, try again.\n";	// bad row/col ids or edge already filled
					else  // else proceed with good player row/col edge
						playerDone = true;
				}
			}
			// note: the computer NEVER makes an invalid move, we hope?
			if(result == false)
				done = true;     // if false, human did "Q" and game is over
			else
			{	// apply the edge and if box(es) filled place nameID into box(es)
				filledBoxes = gridPtr->setEdge(fromRow, fromCol, toRow, toCol, nameId);
				if(filledBoxes == 0)
				{	// no filled box means next player's turn
					currentPlayer++;
					if(currentPlayer == GAME_PLAYER_MAX)
						currentPlayer = GAME_PLAYER_HUMAN;
				}
				else
				{	// filled boxes means update player score and player goes again
					playerPtr->setScore(playerPtr->getScore()+filledBoxes);
				}
			}
		}
		else
			done = true;
	}
	return;
}

// Print Grid. (have Grid object print itself)
void Game::printGrid()
{
	gridPtr->displayGrid();
	return;
}

// Print Scores.
void Game::printScores()
{
	cout << "You: " << human.getScore();
	cout << "    Me: " << computer.getScore() << "\n\n";
	return;
}

// Post Game.
void Game::postGame()
{
	cout << "\nFinal Score:\n";
	cout << "  You:" << human.getScore() << "\n";
	cout << "   Me:" << computer.getScore() << "\n";

	if(computer.getScore() > human.getScore())
		cout << "Better luck next time.\n";
	else if(computer.getScore() < human.getScore())
		cout << "Congratulations\n";
	else
		cout << "I think we need a rematch.\n";

	return;
}



