// Dana Kallunki
// April 9, 2015
// CS 333 Spring 2015
// Box.h 
// dots and boxes assiognment

#ifndef BOX_H
#define BOX_H

//      1
//	  + - +
//	0 | C | 2      // edges are numbered 0 1 2 3
//	  + - +
//      3

typedef struct  {
	char nameId;  	// owner of edge = ' '(none), 'C', 'H'
	int  fromRow;
	int  fromCol;
	int  toRow;
	int  toCol;
	int  dof;		// calculated degrees of freedom
}BOXEDGE_T;


class Box {
public:
	// type EDGEADR defines the from and to dot addresses of an edge
	// an edge is a line that goes from a dot to another adjacent dot
	// on the grid

	// Constructor - a Box at grid  location
	Box(const int rowNo, const int colNo);

	// Get the box owner value (nameId if all  4 edges filled).
	char getOwner() const;

	// Get the open edge count value. (0-4)
	int getEdgeCount() const;

	// get edge data
	bool getEdgeData(const int edgeNo, int& fromRow, int& fromCol,
					int& toRow, int& toCol) const;

	// Get an edge status of a box.
	void getEdgeOwnerId(const int edgeNumber, char& ownerId) const;

	// Get an edge # (0 1 2 3) given its from/to row/col.
	bool getEdgeNo(int& edgeNo, const int fromRow, const int fromCol,
					const int toRow, const int toCol) const;

	// get the previously calculated degrees of freedom for edge of the box
	int getDof(const int edgeNo);

	// Set the box owner value.
	void setOwner(const char ownerId);

	// Set an edge status of a box.
	// returns the number of OPEN edges remaining
	int setEdgeOwnerId(const int edgeNumber, const char ownerId);

	// Set an edge status of a box.
	bool setEdge(const int fromRow, const int fromCol,
					const int toRow, const int toCol, const char nameId);
	// set calculated degrees of freedom for edge of the box
	void setDof(const int edgeNo, const int dof);

	// calc sumX for edge of the box
	int calcSumX(const int edgeNo);

	// calc sumY for edge of the box
	int calcSumY(const int edgeNo);

	// Destructor
	~Box();

private:

	char owner;		// box owner, " ", or an owner nameId  (e.g. C or H)

	int edgeCount;	// box count of open edges (0 to 4)

	// box edge data left,top,right,bottom indexed 0 1 2 3
	// even index edges selected printed  "|"
	// odd index edges selected  printed  "-"
	// box edges have from r,c and to r,c address
	// edge status value  " " (open), or  C or H (or U unavailable)
	BOXEDGE_T edge[4];
};


#endif
