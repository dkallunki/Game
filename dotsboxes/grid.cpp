// Dana Kallunki
// April 9, 2015
// CS 333 Spring 2015
// grid.cpp 
// dots and Grides assiognment

#include <iostream>

using namespace std;

#include "grid.h"
#include "box.h"





// baseRowCol - helper to make from/to row/col 0/0 based
// if the edge from/to row/col are invalid per
// the grid size NxN, return false
static bool baseRowCol(char rowFrom, char colFrom, char rowTo, char colTo,
				int& rowFromBase,int& colFromBase,int& rowToBase,int& colToBase, int size)
{
	rowFromBase = rowFrom - 'a';
	colFromBase = colFrom - '1';
	rowToBase = rowTo - 'a';
	colToBase = colTo - '1';
	if(rowFromBase < 0 || rowFromBase > size)
		return false;
	if(colFromBase < 0 || colFromBase > size)
		return false;
	if(rowToBase < 0 || rowToBase > size)
		return false;
	if(colToBase < 0 || colToBase > size)
		return false;
	return true;
}

// normalizeEdge - helper to make edge addressing left to right and top to bottom
// also if the edge from/to dots are NOT adjacent return false
static bool normalizeEdge(int& rowFrom, int& colFrom, int& rowTo, int& colTo, int size)
{
	int temp = 0;
	if (rowFrom == rowTo)
	{
		// horizontal edge
		if(colFrom == colTo)
			return false;
		if (colFrom > colTo)
		{
			temp = colFrom;
			colFrom = colTo;
			colTo = temp;
		}
		if((colFrom+1) != colTo)
			return false;
	}
	else
	{
		// vertical edge
		if(rowFrom == rowTo)
			return false;
		if (rowFrom > rowTo)
		{
			temp = rowFrom;
			rowFrom = rowTo;
			rowTo = temp;
		}
		if((rowFrom+1) != rowTo)
			return false;
	}
	if((rowFrom < 0 || rowFrom > size) ||
	  (colFrom < 0 || colFrom > size) ||
	  (rowTo < 0 || rowTo > size) ||
	  (colTo < 0 || colTo > size))
		return false;
	return true;
}

// Grid - Construct a Grid of size N x N
Grid::Grid(const int nSize)
{
	int row=0;
	int col=0;
	size = nSize;
	edgeCount = size * (size+1) * 2;

	// construct a grid with N x N new boxes
	for(row=0; row < size; row++)
		for(col=0; col < size; col++)
			gridBoxPtr[row][col] = new Box(row,col);
	// initialize Grid with N+1 x N horizontal edges
	for(row=0; row < (size+1); row++)
		for(col=0; col < size; col++)
			gridHorEdge[row][col] = ' ';
	// initialize Grid with N x N+1 vertical edges
	for(row=0; row < size; row++)
		for(col=0; col < (size+1); col++)
			gridVertEdge[row][col] = ' ';

	headPtr = NULL;      // Linked list head
	tailPtr = NULL;      // Linked list tail

}

// Destruct a Grid 
Grid::~Grid()
{
	// delete the acquired memory resources
	// the N x N newed boxes
	for(int row=0; row < size; row++)
		for(int col=0; col < size; col++)
			delete gridBoxPtr[row][col];
	// delete any left over linked list nodes
	delAllNodes();
}

// getSize - size N.
int Grid::getSize() const
{
	return size;
}

// getEdgeCount.
int Grid::getEdgeCount() const
{
	return edgeCount;
}

// getEdge - status.
bool Grid::getEdge(const char rowFrom, const char colFrom,
					const char rowTo, const char colTo, char& nameId) const
{
	int rowFromBase = 0;
	int colFromBase = 0;
	int rowToBase = 0;
	int colToBase = 0;
	bool result = false;

	// make dot addresses 0 based
	result =  baseRowCol(rowFrom, colFrom, rowTo, colTo,
				rowFromBase, colFromBase, rowToBase, colToBase, size);
	// if invalid row/col exit
	if(result == false)
		return false;
	// and normal left to right and top to bottom ascending order
	result = normalizeEdge(rowFromBase,colFromBase,rowToBase,colToBase,size);
	// if invalid edge exit
	if(result == false)
		return false;
	if (rowFrom == rowTo)
		// horizontal edge
		nameId = gridHorEdge[rowFromBase][colFromBase];
	else
		// vertical edge
		nameId = gridVertEdge[rowFromBase][colFromBase];
	return true;
}

// getEdge - status (overloaded).
bool Grid::getEdge(const int rowFrom, const int colFrom,
					const int rowTo, const int colTo, char& nameId) const
{
	int rowFromBase = rowFrom;
	int colFromBase = colFrom;
	int rowToBase = rowTo;
	int colToBase = colTo;
	bool result = false;

	// normalize left to right and top to bottom ascending order
	result = normalizeEdge(rowFromBase,colFromBase,rowToBase,colToBase, size);
	if(result == false)
		return false;
	if (rowFrom == rowTo)
		// horizontal edge
		nameId = gridHorEdge[rowFromBase][colFromBase];
	else
		// vertical edge
		nameId = gridVertEdge[rowFromBase][colFromBase];
	return true;
}

// setEdge - status (from OPEN to SELECTED by ownerId).
// row/col/nameId values all assumed to be valid here
// returns the number of filled boxes resulting from edge selection
int Grid::setEdge(const char rowFrom, const char colFrom,
					const char rowTo, const char colTo, const char nameId)
{
	bool result = false;
	int rowFromBase = 0;
	int colFromBase = 0;
	int rowToBase = 0;
	int colToBase = 0;
	int temp = 0;
	int row = 0;
	int col = 0;
	int edgeNo = 0;

	// make dot addresses 0 based and normal left to right top to bottom
	baseRowCol(rowFrom, colFrom, rowTo, colTo,
				rowFromBase, colFromBase, rowToBase, colToBase, size);
	normalizeEdge(rowFromBase,colFromBase,rowToBase,colToBase,size);
	if (rowFrom == rowTo)
		// horizontal edge
		gridHorEdge[rowFromBase][colFromBase] = nameId;
	else
		// vertical edge
		gridVertEdge[rowFromBase][colFromBase] = nameId;
	edgeCount--;
	return (updateBoxEdges(rowFromBase, colFromBase, rowToBase, colToBase, nameId));
}



// updateBoxEdges - Update box edge status.
// returns no. of boxes changed to "filled" state
int Grid::updateBoxEdges(const int rowFrom, const int colFrom,
					const int rowTo, const int colTo, const char nameId)
{
	bool result = false;
	int row = 0;
	int col = 0;
	int edgeNo = 0;
	int filledBoxesCount = 0;
	int openCount = 0;

	// update edge data of affected boxes in the grid
	for(row=0; row < size; row++)
	{
		for(col=0; col < size; col++)
		{
			result = gridBoxPtr[row][col]->getEdgeNo(edgeNo, rowFrom, colFrom, rowTo, colTo);
			if(result == true)
			{
				openCount = gridBoxPtr[row][col]->setEdgeOwnerId(edgeNo, nameId);
				if(openCount == 0)
				{
					gridBoxPtr[row][col]->setOwner(nameId);
					filledBoxesCount++;
				}
			}
		}
	}
	return filledBoxesCount;
}

// findBoxes - with N (0,1,2,or 3) edges of 4 filled in.
// Used to get those boxes from within the grid
// edges can be 0 or 1 or 2 or 3 depending on type of box
// being searched for (e.g., search for boxes with 3 edges filled)
// to find all boxes with 3 of the 4 edges filled in
// do: boxPtrPtr = findBoxes(3);
Box** Grid::findBoxes(const int edges, int& count)
{
	int index = 0;
	int row = 0;
	int col = 0;

	// find boxes with N edges filled in (connected)
	for(row=0; row < size; row++)
	{
		for(col=0; col < size; col++)
		{
			if((4-edges) == gridBoxPtr[row][col]->getEdgeCount())
				boxArray[index++] = gridBoxPtr[row][col];
		}
	}

	// return number of items in array list
	count = index;
	// return a ptr to "an array of box ptrs"
	return boxArray;
}


// calcDof - calc degrees of freedom for edge of the box
int Grid::calcDof(const int edgeNo, Box* boxPtr)
{
	typedef struct { 	// a DOF offset from current r/c point
		int rowOffset;	// to an adjacent point in the
		int colOffset;	// east, west, north or south direction
	} DOFOFFSET_T;

	static DOFOFFSET_T dofOffset[4] = {
			{ 0,-1},	// left/east direction offset
			{ 0, 1},	// right/west direction offset
			{-1, 0},	// top/north direction offset
			{ 1, 0}		// bottom/south direction offset
	};

	char nameId = ' ';
	int fromRow;
	int fromCol;
	int toRow;
	int toCol;
	int dof = 0;
	bool result = false;

	boxPtr->getEdgeData(edgeNo,fromRow,fromCol,toRow,toCol);
	for(int i=0; i < 4; i++)
	{
		result = getEdge(fromRow, fromCol, (fromRow + dofOffset[i].rowOffset),
							(fromCol + dofOffset[i].colOffset), nameId);
		if(result == true && nameId == ' ')
			dof++;
	}
	for(int i=0; i < 4; i++)
	{
		result = getEdge(toRow, toCol, (toRow + dofOffset[i].rowOffset),
							(toCol + dofOffset[i].colOffset), nameId);
		if(result == true && nameId == ' ')
			dof++;
	}
	boxPtr->setDof(edgeNo,dof);
	return(dof);
}

// displayGrid - Display the current Grid data
void Grid::displayGrid() const
{
	char row = 'a';
	char col = '1';
	int i = 0;
	int colBase = 0;
	int rowBase = 0;

	for(rowBase=0; rowBase < (size+1); rowBase++)
	{	// display a row of horizontal edges
		cout << row << ' ';
		for(colBase=0; colBase < size; colBase++)
		{
			cout << '+';
			if(gridHorEdge[row-'a'][colBase] != ' ')
				cout << '-';
			else
				cout << ' ';
		}
		cout << "+\n";
		// display a row of vertical edges
		if(rowBase != (size))
		{
			cout << "  ";
			for(colBase=0; colBase < (size+1); colBase++)
			{
				if(gridVertEdge[row-'a'][colBase] != ' ')
					cout << '|';
				else
					cout << ' ';
				// also put box owner ' ', C or H if interior of grid
				if (colBase != size)
					cout << gridBoxPtr[rowBase][colBase]->getOwner();
			}
			cout << '\n';
		}
		row++;
	}
	// display a row of column numbers '1' to N+1
	cout << "  ";
	for(rowBase=0; rowBase < (size+1); rowBase++)
	{
		cout << col << " ";
		col++;
	}
	cout << "\n";
	return;
}


///////////////////////////////////////////////////////////////////////
//// example of using a linked list vs array for passing back found
//// boxes
/////////////////////////////////////////////////////////////////////
void Grid::findBoxesLL(const int edges, int& count)
{
	int index = 0;
	int row = 0;
	int col = 0;

	delAllNodes();
	// find boxes with N edges filled in (connected)
	for(row=0; row < size; row++)
	{
		for(col=0; col < size; col++)
		{
			if((4-edges) == gridBoxPtr[row][col]->getEdgeCount())
			{
				addNode(gridBoxPtr[row][col]);
				index++;
			}
		}
	}

	// return number of items in linked list
	count = index;
}



void Grid::addNode(Box *box )
{
	NODE_S *newNodePtr = new NODE_S();
	newNodePtr->boxPtr = box;
	newNodePtr->nextPtr = NULL;

	if(headPtr == NULL ){	// Add first item as initial head/tail Ptrs
		headPtr = newNodePtr;
		tailPtr = newNodePtr;
	}
	else                    // Add subsequent items at tail of list
	{
		tailPtr->nextPtr =  newNodePtr;
		tailPtr = newNodePtr;
	}
}

Box* Grid::getNodeN(int N)  // first node == N == 1
{
	Box *b = NULL;
	NODE_S *i = headPtr;
	while (N-- && i != NULL)
	{
		b = i->boxPtr;
		i = i->nextPtr;
	}
	return b;
}

void Grid::delAllNodes()
{
	NODE_S *i = headPtr;
	NODE_S *c = NULL;
	while (i != NULL)
	{
		c = i;
		i = i->nextPtr;
		delete c;
	}
	headPtr = NULL;
	tailPtr = NULL;
}



