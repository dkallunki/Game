/*
 * dotsAndBoxes.cpp
 *
 *  Created on: Apr 26, 2015
 *      Author: kallunki j
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <ctype.h>
#include <cmath>
//#include <array>

#include "grid.h"
#include "utilities.h"
#include "box.h"


using namespace std;


int main( ){
Grid grid;
//Move playerMove;
int size;
char letter1 ='a';// initialize all values
char letter2 =' ';
int  num1    = -1;
int  num2    = -1;// needs d1, d2 int and char
	// ask user for  size of grid
	 cout<<"What Grid size would you like? (2..8) ";
	 cin>> size;

	 while(( size< 2) ||( size >8 ))//  && only a number
	 	 {
		 cout<< "Sorry, try again."<<endl;
		 cout<<"What Grid size would you like? (2..8) ";
		 	 cin>> size;
	 	 }

//print out grid
cout<<Grid(size);




grid.makeMove(); //in main and Grid:: in grid.cpp and fx name in .h
	cout<<endl;
cout<< "msg end of game"<<endl;







	return 0;
}


