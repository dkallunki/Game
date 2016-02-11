// Dana Kallunki
// April 9, 2015
// CS 333 Spring 2015
// computer.cpp 
// dots and boxes assiognment

#include <iostream>
using namespace std;
#include "computer.h"

#if 1
// takeTurn - this virtual method is implemented here in this sub-class
// of the parent base class called Player
// takes a computer turn and returns the from r,c and to r,c data

bool Computer::takeTurn(char& fromRow, char& fromCol, char& toRow, char& toCol, Grid* gridPtr)
{
	int  fromRowOut = 0;
	int  fromColOut = 0;
	int  toRowOut = 0;
	int  toColOut = 0;

	Box** boxPtrPtr = 0;
	Box** boxPtrPtrTemp = 0;
	Box** boxPtr = 0;

	int count = 0;
	int edgesFilled = 0;

	int edgeNo = 0;
	int edgecount = 0;

	int i = 0;
	int j = 0;

	char ownerId = ' ';
	int calcTemp = 0;
	int calcHits = 0;

	int dofMax = 0;
	int dofMaxBoxIndex = 0;
	int dofMaxEdge = 0;

	int sumXMin = 5000;
	int sumXMinBoxIndex = 0;
	int sumXMinEdge = 0;

	int sumYMin = 5000;

	int selectedBoxIndex = 0;
	int selectedEdge = 0;

	// NOTE: there is at least 1 edge left at this point

	// rule 1 -----------------------------------------------------------

	// find boxes with 3 edges already filled in
	edgesFilled = 3;
	boxPtrPtr = gridPtr->findBoxes(edgesFilled, count);   // find 3 edge boxes?
	if(count == 0)
	{
		// find boxes with 0 edges already filled in, that will not add a 3rd edge
		edgesFilled = 0;
		boxPtrPtr = gridPtr->findBoxes(edgesFilled, count); // find 0 edge boxes?
		if(count == 0)
		{
			// find boxes with 1 edge already filled in, that will not add a 3rd edge
			edgesFilled = 1;
			boxPtrPtr = gridPtr->findBoxes(edgesFilled, count); // find 1 edge boxes?
			if(count== 0)
			{
				// FINALLY, we have no other choice now
				// find boxes with 2 edges already filled in,
				// that WILL (unfortunately) mean we add a 3rd edge
				edgesFilled = 2;
				boxPtrPtr = gridPtr->findBoxes(edgesFilled, count);
			}
		}

	}

	cout << "found " << count << " boxes with edgesFilled = " << edgesFilled << "\n";

	// boxPtrPtr = is a list of 1 or more boxes (NULL terminated)
	// and "edgesFilled" is the no. edges filled in on those boxes
	// and "count" = the no of box ptrs in the list

	// if multiple choices go to Rule 2

	// rule 2 ---------------------------------------------------------
	// ( check degrees of freedom )
	// for each from/to point of OPEN edge E
	// count how many OPEN edges touch the from and to points (0-4 open EDGES)
	for(i=0; i < count; i++)// i= box number
	{
		for(j=0; j < Grid::GRID_BOXEDGEMAX; j++)//for edges of the box
		{
			boxPtrPtr[i]->getEdgeOwnerId(j, ownerId);
			if(ownerId == ' ')
			{
				calcTemp = gridPtr->calcDof(j, boxPtrPtr[i]);
				cout << "Box/Edge " << i << "/" << j <<  "  dof = " << calcTemp << "\n";
				if(calcTemp > dofMax)
				{
					dofMax = calcTemp;   // new DOF max
					calcHits = 1;
					dofMaxBoxIndex = i;
					dofMaxEdge = j;
				}
				else if(calcTemp == dofMax)
					calcHits++;      // additional DOF max
			}
		}
	}

	// select the max OPEN count if UNIQUE
	if(calcHits == 1)
	{
		selectedBoxIndex = dofMaxBoxIndex;
		selectedEdge = dofMaxEdge;
	}
	// if multiple choices with max dof go to Rule 3
	else
	{
		// rule 3 -----------------------------------------------------
		// Select the edge E between dots D1 and D2 from
		// the list that minimizes the sum of the
		// x-coordinates (row) of D1 and D2 for each from/to
		// point of edge E.
		calcHits = 0;
		for(i=0; i < count; i++)
		{
			for(j=0; j < Grid::GRID_BOXEDGEMAX; j++)
			{
				boxPtrPtr[i]->getEdgeOwnerId(j, ownerId);
				if(ownerId == ' ')
				{
					calcTemp = boxPtrPtr[i]->getDof(j);
					if(calcTemp == dofMax)
					{
						calcTemp = boxPtrPtr[i]->calcSumX(j);
						cout << "Box/Edge " << i << "/" << j <<  "  suX = " << calcTemp << "\n";
						if(calcTemp < sumXMin)
						{
							sumXMin = calcTemp;   // new DOF max
							calcHits = 1;
							sumXMinBoxIndex = i;
							sumXMinEdge = j;
						}
						else if(calcTemp == sumXMin)
						{
							calcHits++;      // additional SumX Min
						}
					}
				}
			}
		}

		cout << "found " << calcHits << " box edges with sumxmin = " << sumXMin << " edge " << sumXMinEdge << "\n";
		// select the min SumX EDGE if UNIQUE
		if(calcHits == 1)
		{
			selectedBoxIndex = sumXMinBoxIndex;
			selectedEdge = sumXMinEdge;
			// use this edge
		}
		// if multiple choices with min SumX go to Rule 4
		else
		{
			// rule 4 ----------------------------------------------
			// Select the edge E between dots D1 and D2 from the
			// list that minimizes the sum of the y-coordinates (col)
			// of D1 and D2 for each from/to point of edge E.
			// I guess the 1st min is ok to select, rules don't say what to do
			// Note: if more than one dupe min, seems not likely actually
			for(i=0; i < count; i++)
			{
				for(j=0; j < Grid::GRID_BOXEDGEMAX; j++)
				{
					boxPtrPtr[i]->getEdgeOwnerId(j, ownerId);
					if(ownerId == ' ')
					{
						calcTemp = boxPtrPtr[i]->calcSumX(j);
						if(calcTemp == sumXMin)
						{
							calcTemp = boxPtrPtr[i]->calcSumY(j);
							cout << "Box/Edge " << i << "/" << j <<  "  suY = " << calcTemp << "\n";
							if(calcTemp < sumYMin)
							{
								sumYMin = calcTemp;   // new sumY min
								selectedBoxIndex = i;
								selectedEdge = j;
							}
						}

					}
				}
			}
			cout << "found " << "1" << " box edges with sumymin = " << sumYMin << " edge " << selectedEdge << "\n";
		}
	}

	// done with selecting an EDGE, get the edge r/c info
	boxPtrPtr[selectedBoxIndex]->getEdgeData(selectedEdge, fromRowOut,
												fromColOut, toRowOut, toColOut);

	// then we return our move data D1 D2 as char's
	fromRow = (char) 'a' + (char) fromRowOut;  	// D1
	fromCol = (char) '1' + (char) fromColOut;  	// D1
	toRow   = (char) 'a' + (char) toRowOut;   	// D2
	toCol   = (char) '1' + (char) toColOut;   	// D2

	cout << "I choose to connect dots " << fromRow << fromCol;
	cout << " and " << toRow << toCol << "\n";
	return true;
}
#endif

#if 0
	///////////////////////////////////////////////////////////
	//// using a linked list
	////////////////////////////////////////////////////////////
	bool Computer::takeTurn(char& fromRow, char& fromCol, char& toRow, char& toCol, Grid* gridPtr)
	{
		int  fromRowOut = 0;
		int  fromColOut = 0;
		int  toRowOut = 0;
		int  toColOut = 0;

		//Box** boxPtrPtr = 0;
		Box** boxPtrPtrTemp = 0;
		Box** boxPtr = 0;
		Box* boxP = 0;

		int count = 0;
		int edgesFilled = 0;

		int edgeNo = 0;
		int edgecount = 0;

		int i = 0;
		int j = 0;

		char ownerId = ' ';
		int calcTemp = 0;
		int calcHits = 0;

		int dofMax = 0;
		int dofMaxBoxIndex = 0;
		int dofMaxEdge = 0;

		int sumXMin = 5000;
		int sumXMinBoxIndex = 0;
		int sumXMinEdge = 0;

		int sumYMin = 5000;

		int selectedBoxIndex = 0;
		int selectedEdge = 0;

		// NOTE: there is at least 1 edge left at this point

		// rule 1 -----------------------------------------------------------

		// find boxes with 3 edges already filled in
		edgesFilled = 3;
		gridPtr->findBoxesLL(edgesFilled, count);   // find 3 edge boxes?
		if(count == 0)
		{
			// find boxes with 0 edges already filled in, that will not add a 3rd edge
			edgesFilled = 0;
			gridPtr->findBoxesLL(edgesFilled, count); // find 0 edge boxes?
			if(count == 0)
			{
				// find boxes with 1 edge already filled in, that will not add a 3rd edge
				edgesFilled = 1;
				gridPtr->findBoxesLL(edgesFilled, count); // find 1 edge boxes?
				if(count== 0)
				{
					// FINALLY, we have no other choice now
					// find boxes with 2 edges already filled in,
					// that WILL (unfortunately) mean we add a 3rd edge
					edgesFilled = 2;
					gridPtr->findBoxesLL(edgesFilled, count);
				}
			}

		}

		cout << "found " << count << " boxes with edgesFilled = " << edgesFilled << "\n";

		// and "edgesFilled" is the no. edges filled in on those boxes
		// and "count" = the no of box ptrs in the list

		// if multiple choices go to Rule 2

		// rule 2 ---------------------------------------------------------
		// ( check degrees of freedom )
		// for each from/to point of OPEN edge E
		// count how many OPEN edges touch the from and to points (0-4 open EDGES)
		for(i=0; i < count; i++)
		{
			for(j=0; j < Grid::GRID_BOXEDGEMAX; j++)
			{
				boxP = gridPtr->getNodeN(i+1);
				boxP->getEdgeOwnerId(j, ownerId);
				if(ownerId == ' ')
				{
					calcTemp = gridPtr->calcDof(j, boxP);
					cout << "Box/Edge " << i << "/" << j <<  "  dof = " << calcTemp << "\n";
					if(calcTemp > dofMax)
					{
						dofMax = calcTemp;   // new DOF max
						calcHits = 1;
						dofMaxBoxIndex = i;
						dofMaxEdge = j;
					}
					else if(calcTemp == dofMax)
						calcHits++;      // additional DOF max
				}
			}
		}

		cout << "found " << calcHits << " box edges with dofMax = " << dofMax << "\n";
		// select the max OPEN count if UNIQUE
		if(calcHits == 1)
		{
			selectedBoxIndex = dofMaxBoxIndex;
			selectedEdge = dofMaxEdge;
		}
		// if multiple choices with max dof go to Rule 3
		else
		{
			// rule 3 -----------------------------------------------------
			// Select the edge E between dots D1 and D2 from
			// the list that minimizes the sum of the
			// x-coordinates (row) of D1 and D2 for each from/to
			// point of edge E.
			calcHits = 0;
			for(i=0; i < count; i++)
			{
				for(j=0; j < Grid::GRID_BOXEDGEMAX; j++)
				{
					boxP = gridPtr->getNodeN(i+1);
					boxP->getEdgeOwnerId(j, ownerId);
					if(ownerId == ' ')
					{
						calcTemp = boxP->getDof(j);
						if(calcTemp == dofMax)
						{
							calcTemp = boxP->calcSumX(j);
							cout << "Box/Edge " << i << "/" << j <<  "  suX = " << calcTemp << "\n";
							if(calcTemp < sumXMin)
							{
								sumXMin = calcTemp;   // new DOF max
								calcHits = 1;
								sumXMinBoxIndex = i;
								sumXMinEdge = j;
							}
							else if(calcTemp == sumXMin)
							{
								calcHits++;      // additional SumX Min
							}
						}
					}
				}
			}

			cout << "found " << calcHits << " box edges with sumxmin = " << sumXMin << " edge " << sumXMinEdge << "\n";
			// select the min SumX EDGE if UNIQUE
			if(calcHits == 1)
			{
				selectedBoxIndex = sumXMinBoxIndex;
				selectedEdge = sumXMinEdge;
				// use this edge
			}
			// if multiple choices with min SumX go to Rule 4
			else
			{
				// rule 4 ----------------------------------------------
				// Select the edge E between dots D1 and D2 from the
				// list that minimizes the sum of the y-coordinates (col)
				// of D1 and D2 for each from/to point of edge E.
				// I guess the 1st min is ok to select, rules don't say what to do
				// Note: if more than one dupe min, seems not likely actually
				for(i=0; i < count; i++)
				{
					for(j=0; j < Grid::GRID_BOXEDGEMAX; j++)
					{
						boxP = gridPtr->getNodeN(i+1);
						boxP->getEdgeOwnerId(j, ownerId);
						if(ownerId == ' ')
						{
							calcTemp = boxP->calcSumX(j);
							if(calcTemp == sumXMin)
							{
								calcTemp = boxP->calcSumY(j);
								cout << "Box/Edge " << i << "/" << j <<  "  suY = " << calcTemp << "\n";
								if(calcTemp < sumYMin)
								{
									sumYMin = calcTemp;   // new sumY min
									selectedBoxIndex = i;
									selectedEdge = j;
								}
							}

						}
					}
				}
				cout << "found " << "1" << " box edges with sumymin = " << sumYMin << " edge " << selectedEdge << "\n";
			}
		}

		// done with selecting an EDGE, get the edge r/c info
		boxP = gridPtr->getNodeN(selectedBoxIndex+1);
		boxP->getEdgeData(selectedEdge, fromRowOut,
							fromColOut, toRowOut, toColOut);

		// then we return our move data D1 D2 as char's
		fromRow = (char) 'a' + (char) fromRowOut;  	// D1
		fromCol = (char) '1' + (char) fromColOut;  	// D1
		toRow   = (char) 'a' + (char) toRowOut;   	// D2
		toCol   = (char) '1' + (char) toColOut;   	// D2

		cout << "I choose to connect dots " << fromRow << fromCol;
		cout << " and " << toRow << toCol << "\n";
		return true;

}
#endif

