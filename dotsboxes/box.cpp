// Dana Kallunki
// April 9, 2015
// CS 333 Spring 2015
// Box.cpp 
// dots and boxes assignment
#include <iostream>
using namespace std;
#include "box.h"

// Construct a Box at row, column "origin" location of Grid

Box::Box(const int rowNo, const int colNo)
{
	typedef struct {		// an edge is a line with the points at
		int fromRowOffset;	// each end addressed as a r/c
		int fromColOffset;	// this line has a from r/c and to r/c
		int toRowOffset;	// a "offset" table of offsets from the box origin r/c
		int toColOffset;	// is used to calc the actual from and to r/c addresses
	} OFFSET_T;				// of each point of the edge line

	static OFFSET_T offset[4] = {
			{0,0,1,0}, // edge 0 fromrow, fromcol, torow, tocol, offsets
			{0,0,0,1}, // edge 1 offsets
			{0,1,1,1}, // edge 2 offsets
			{1,0,1,1}  // edge 3 offsets
	};

	int i = 0;

	owner = ' ';
	edgeCount = 4;

	for(i=0; i < 4; i++)	// initialize the 4 edge line from & to addresses
	{						// used during box updates to apply move to boxes
		edge[i].fromRow = rowNo + offset[i].fromRowOffset;
		edge[i].fromCol = colNo + offset[i].fromColOffset;
		edge[i].toRow = rowNo + offset[i].toRowOffset;
		edge[i].toCol = colNo + offset[i].toColOffset;
		edge[i].nameId = ' ';
	}

	return;
}

// Destruct a Box 
Box::~Box()
{
}

// Get owner of the box.
char Box::getOwner() const
{
	return owner;
}

// Get open edges count of the box.
// as edges are selected the edge count
// of a box decreases from 4 to 3 to ... until 0

int Box::getEdgeCount() const
{
	return edgeCount;
}

// calc sum X for edge N of the box (edge line from row + to row)
int Box::calcSumX(const int edgeNo)
{
	return edge[edgeNo].fromRow + edge[edgeNo].toRow;
}

// calc sum Y for edge N of the box (edge line from col + to col)
int Box::calcSumY(const int edgeNo)
{
	return edge[edgeNo].fromCol + edge[edgeNo].toCol;
}

// get calculated degrees of freedom for edge of the box
int Box::getDof(const int edgeNo)
{
	return(edge[edgeNo].dof);
}

// Get an edge owner of the box.
void Box::getEdgeOwnerId(const int edgeNumber, char& ownerId) const
{
	ownerId = edge[edgeNumber].nameId;
	return;
}

// get edge data, the edge line from and to r/c
bool Box::getEdgeData(const int edgeNo, int& fromRow, int& fromCol,
						int& toRow, int& toCol) const
{
	fromRow = edge[edgeNo].fromRow;
	fromCol = edge[edgeNo].fromCol;
	toRow = edge[edgeNo].toRow;
	toCol = edge[edgeNo].toCol;
	return true;
}

// Get an edge number given edge line from-to r/c address.
bool Box::getEdgeNo(int& edgeNo, const int fromRow, const int fromCol,
					const int toRow, const int toCol) const
{
	int i = 0;
	for(i=0; i < 4; i++)
	{
		if(edge[i].fromRow == fromRow &&
			edge[i].fromCol == fromCol &&
			edge[i].toRow == toRow &&
			edge[i].toCol == toCol)
		{
			edgeNo = i;
			return true;
		}
	}
	return false;
}

// Set owner of the entire box (all 4 edges have been selected).
// player to select the 4th edge gets to be the owner
void Box::setOwner(const char ownerId)
{
	owner = ownerId;
}

// set degrees of freedom for edge of the box
void Box::setDof(const int edgeNo, const int dof)
{
	edge[edgeNo].dof = dof;
	return;
}

// Set an edge of the box. Makes an edge owned by a player.
// and decrements the open edge count of the box
// also returns the number of OPEN edges remaining
int Box::setEdgeOwnerId(const int edgeNumber, const char ownerId)
{
	edge[edgeNumber].nameId = ownerId;
	edgeCount--;
	return edgeCount;
}

// Set an edge status of a box.
bool Box::setEdge(const int fromRow, const int fromCol,
					const int toRow, const int toCol, const char nameId)
{
	int edgeNo = 0;
	getEdgeNo(edgeNo, fromRow, fromCol,toRow, toCol);
	setEdgeOwnerId(edgeNo, nameId);
	return true;
}

