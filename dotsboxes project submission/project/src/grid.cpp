/*
 * grid.cpp
 *
 *  Created on: Apr 24, 2015
 *      Author: kallunki j
 */
#include "grid.h"
#include "box.h"

using namespace std;






// initialize array to blank spaces using 2 arrays
void Grid::initEdges(){
    // Initialize claimed vertical edges


    for( int a = 0; a < MAX_ROWS+1; a++ ){//outerloop
     //   vertical_edges[i] = 'X';

        for( int b = 0; b < MAX_COLS +1; b++ ){//innerloop
            vertical_edges[a][b] = ' ';
        }
    }

    // Initialize claimed horizontal edges


    for( int c = 0; c < MAX_ROWS +1; c++ ){//outerloop
   //     horizontal_edges[i] = 'O';

        for( int d = 0; d < MAX_COLS +1; d++ ){//innerloop
            horizontal_edges[c][d] = ' ';
        }
    }
}// end fx


//constructor
	Grid::Grid(){
		n_rows = 4+1;
		n_cols = 4+1;

		initEdges();
	}

//constructor
	Grid::Grid( int size ){
		n_rows = size +1;
		n_cols = size +1;

		initEdges();
	}




//**************************************************************************
void Grid::makeMove( ){// char
	Box box;
	char letter1 ='x';// initialize all values
	int  num1    = -1;
	char letter2 ='y';
	int  num2    = -1;// needs d1, d2 int and char
	char player = 'A';


	// set player choosen edge for horizontal call to function here

	bool illegal = false;

	while((player == 'A' || player =='B' )||(!illegal)){





		cout<< "What two dots would you like to connect?  (Q to quit)";
		cin>>letter1>>num1>>letter2>>num2;


			// contvert to elements in array here
		if( letter1 =='Q' || letter1 =='q'){
			exit (1);
		}
		// test for values outside of range here (ex a1 a5)repeat loop





		// if illegal move condition here c1 a1
		// ask again

		//else{
			if (letter1 ==letter2){
						// process the move as horizontal
						int row=10;
						int col=10;

						row= int(letter2- 'a');
						col = (num1 -1)+1;

						 if (horizontal_edges[row][col] == ' ')
							 	 horizontal_edges[row][col]= '-';
						 else
							 cout<< "Sorry, try again"<< endl<<endl;
						 // handle by reset players or by while loop above( error check fx)
						}//end of horizontal if condition

					else{
						int rowV=10;
						int colV=10;

						rowV=int(letter2 -'a')-1;
						colV = int(num1)-1;

						if(vertical_edges [rowV][colV]==' ')
								vertical_edges[rowV][colV]='|';

						else
								cout<<"Sorry, try again"<<endl<<endl;

					}//end of vertical if condition


			// update the grid move by move

				display();
				// update the player move by move
			switch (player){
			case 'A':
				player ='B';
						break;
			case 'B':
				player= 'A';
						break;
			default:
				cout<<"Error in choosing player!"<<endl;
						break;
				}// end of switch




	//} //end of BIG ELSE
	}//end of while
}// END of makemove fx

/**
 *
 */
void Grid::display(  ) const{

		for (int i=0; i< n_rows; i++){// prints number of rows (outerloop) for all 3 symbols
				char alpha='a' + i;
				cout<<alpha;
				for(int j =0; j< n_cols; j++){// prints number of columns

						cout<<horizontal_edges[i][j];// fix here if i-1 gets garbage & if left there are
									// extra o"s in the first column.
							cout<<"+";
					}//inner #1
	// check for array vertical, then check box value REPEAT

			cout <<endl;
			cout<<" "; // skip two spaces 1 x for each line , before each row is displayed

	// rows for this loop handled above with outerloop
				for (int k=0; k<n_cols; k++){
					cout<<" "<<vertical_edges[i][k];

					}// END columns for vertical lines

				cout<<endl;// advance one line to next row

	}//outerloop of grid
		//prints one line of  numbers vertically
			cout<<"  ";
		for (int v=0; v< n_rows; v++){
				cout<< v+1 <<" ";
			}
		int youScore=10;
		int meScore =0;


		cout<<endl;
		// display updated players score here
		cout<<"You:"<<setw(2)<<youScore; //humanplayer variable
		cout<<"    Me:"<<setw(2)<<meScore<<endl<<endl;//computer score
		// add check for total edges here and if total edges >0 keep going
		// else price final score condition




}//fx END

