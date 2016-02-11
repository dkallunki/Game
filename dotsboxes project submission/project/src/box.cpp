/*
 * box.cpp
 *
 *  Created on: Apr 28, 2015
 *      Author: kallunki j
 */


#include "box.h"

using namespace std;




 Box::Box (){



 }




 // 1)if gameboard is full/ game over ( check here or grid.cpp ?)
 //   then do :display final score youScore meScore
 // 2)else if box exists add a point  to player
 	 	 // add point to score
 	 	 // change turn to same player
 	 	 // locate top, bottom, left and right sides
 void Box::ScoreBox(){
	 Grid grid;
 cout<< "Final Score:"<<endl;
 cout <<"  You:"<<grid.youScore<<endl;
 cout <<"  Me :"<<grid.meScore<<endl;
 	 // display end msg
 if( grid.youScore >grid.meScore){
	 cout<<"Congratulations!";

 }
 else if( grid.meScore >grid.youScore){

	 cout<<"Better luck next time!";
 }
 else
 {
	 cout<<"I think we need a rematch!";
 }
}//end of fx
