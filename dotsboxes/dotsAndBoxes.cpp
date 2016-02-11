// Dana Kallunki
// April 9, 2015
// CS 333 Spring 2015
// dotsboxes.cpp 
// dots and boxes assignment

#include <iostream>
using namespace std;

#include "game.h"
#include "calc.h"



// The main--i.e., driver--function

int main (int argc, char** argv)
{
	Game game;
	game.run();

	
	// Template example
	calc <double> calc_double_object;
	// or calc <float> calc_float_object;
	
	double a = 5;
	double b = 8;
	double c = 0;
	
	cout << " calc template using <double> \n";
	c = calc_double_object.multiply(a, b);
	cout << " 5 X 8 = " << c << "\n";

	c = calc_double_object.add(a, b);
	cout << " 5 + 8 = " << c << "\n";

	c = calc_double_object.sub(a, b);
	cout << " 5 - 8 = " << c << "\n";
	
	
    return 0;
}
