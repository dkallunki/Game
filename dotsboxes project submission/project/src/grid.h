/*
 * grid.h
 *
 *  Created on: Apr 24, 2015
 *      Author: kallunki j
 */

#ifndef GRID_H_
#define GRID_H_

#include <iostream>
//#include <array>
#include <iomanip>
#include <cmath>
#include <cstdlib>
using namespace std;



class Grid{


public:
	static const int MIN_ROWS = 2; ///< Min number of rows
	static const int MIN_COLS = 2; ///< Min number of column+s

	static const int MAX_ROWS = 8; ///< Max number of rows
	static const int MAX_COLS = 8; ///< Max number of columns
	int youScore;
	int meScore;



private:
	//variables here
	char horizontal_edges  [MAX_ROWS +1][MAX_ROWS +1]; 	// array to hold " " for empty or"-" for taken
	char vertical_edges	   [MAX_COLS+1][MAX_COLS+1];	// array to hold " " for empty or "|" for taken
	int n_rows; ///< number of rows
	int n_cols; ///< number of columns
	// move variables
	char letter1;
	int  num1;
	char letter2;
	int  num2;

public:

	void initEdges();//void initEdges();// initialize edges to " "

/**
* Create a 4 x 4 grid
 */
	 Grid();

/**
* Create a grid form USER
*/

	Grid( int size );


	// GETS & SETS for PRIVATE variables here
	int getNumRows() const;

	void setNumRows( int r );

	int getNumCols() const;

	void setNumCols( int c );
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		        //  move fx
	void makeMove( );// char ??







//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
		        /**
		         * Print the grid
		         */
		        void display( ) const;

	};// END of class GRID

		/**
		 * Allow printing of the grid with a *cout statement*
		 */
		std::ostream& operator<<( std::ostream &outs, const Grid &prt );


	inline int Grid::getNumRows() const{
		    return this->n_rows;
		}


	inline void Grid::setNumRows( int r ){
		    this->n_rows = r;
		}

	inline int Grid::getNumCols() const{
		    return this->n_cols;
		}

	inline void Grid::setNumCols( int c ){
		    this->n_cols = c;
		}

	inline std::ostream& operator<<( std::ostream &outs, const Grid &prt ){
		    prt.display( );

		    return outs;
		}








#endif /* GRID_H_ */
