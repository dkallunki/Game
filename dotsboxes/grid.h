// Dana Kallunki
// April 9, 2015
// CS 333 Spring 2015
// grid.h 
// dots and boxes assignment

#ifndef GRID_H
#define GRID_H

// the Grid is N x N  boxes (N can be 2 to 8)
//  any N x N Grid has "N squared" boxes inside
//  for example a 3 x 3 Grid has
//   9 boxes inside
//   h edges [4][3] array    4 rows 3 columns
//   v edges [3][4] array    3 rows 4 columns

// row ids are a b c d e f g h i
// col ids are 1 2 3 4 5 6 7 8 9

//    0 1 2 3

//  a +-+ + + 0
//      |
//  b +-+ + + 1
//    |C|
//  c + + + + 2
//      |H|
//  d + + + + 3
//    1 2 3 4

//  each Edge has an edge owner, ' '(unselected), 'C'(computer) or 'H'(human)


// a Box within the grid has 4 edges numbered 0 1 2 3
//  each Box has a box owner, ' ', 'C' or 'H'
//      1
//	  + - +
//	0 | C | 2
//	  + - +
//      3

#include "box.h"

class Grid {
	static const int GRID_SIZE_MIN = 2;
	static const int GRID_SIZE_MAX = 2;

public:
	static const int GRID_BOXEDGEMAX = 4;

	struct NODE_S {      // a single node within the linked list
		Box    *boxPtr;  // ptr to a Box (the data)
		NODE_S *nextPtr; // ptr to next node in the linked list
	};

	// Constructor - a Grid of size N x N
	Grid(int nSize);

	// set an edge owner id = to " ", C or H or U
	// returns the number of filled boxes resulting from edge selection
	int setEdge(const char rowFrom, const char colFrom,
				const char rowTo, const char colTo, const char nameId);

	// get an edge owner id " ", C or H or U (char args)
	bool getEdge(const char rowFrom, const char colFrom,
				const char rowTo, const char colTo, char& nameId) const;
	// get an edge owner id " ", C or H or U (int args - overloaded function)
	bool getEdge(const int rowFrom, const int colFrom,
				const int rowTo, const int colTo, char& nameId) const;
	
	// Update box edge status.
	// returns the number of filled boxes resulting from box edge updates
	int updateBoxEdges(const int rowFrom, const int colFrom,
						const int rowTo, const int colTo, const char nameId);

	// calc degrees of freedom for edge of a box
	int calcDof(const int edgeNo, Box* boxPtr);

	// get count of all open edges
	// (not yet selected by a player)
	int getEdgeCount() const;

	// get size of Grid
	int getSize() const;

	// Display the grid current state
	void displayGrid() const;

	// Find boxes of a particular number of filled edges
	// returns a ptr to array of box ptrs
	// updates count to be no. of boxes in that list
	Box** findBoxes(const int edges, int& count);

	////////////////////////////////////////////////////////////////////
	void findBoxesLL(const int edges, int& count);
	// addNode and getNodeN here are just for comparison of
	// using a linked list vs using an array for the findBoxes function
	void addNode(Box *box);
	Box* getNodeN(int N);   // first node == N == 1
	void delAllNodes();
	////////////////////////////////////////////////////////////////////

	// Destructor
	~Grid();

private:


	NODE_S *headPtr;      // Linked list head
	NODE_S *tailPtr;      // Linked list tail

	int  size;											// Grid N value 2 to 8
	int  edgeCount;										// Grid total open edge count
	Box* gridBoxPtr[GRID_SIZE_MAX][GRID_SIZE_MAX];		// Grid array of ptrs to the boxes indexed by [row][col]
	char gridHorEdge[GRID_SIZE_MAX+1][GRID_SIZE_MAX];	// Grid array of horizontal edges e.g. 5r x 4c
	char gridVertEdge[GRID_SIZE_MAX][GRID_SIZE_MAX+1];	// Grid array of vertical edges   e.g. 4r x 5c
	Box* boxArray[((GRID_SIZE_MAX)*(GRID_SIZE_MAX))];	// Grid array of ptrs to boxes found during findBoxes
};


#endif
