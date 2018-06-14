/*-----------------------------------------------------------------------------
 *				HTBLA-Leonding / Class: <your class name here>
 *-----------------------------------------------------------------------------
 * Exercise Number: #exercise_number#
 * File:			battleship.c
 * Author(s):		Peter Bauer
 * Due Date:		#due#
 *-----------------------------------------------------------------------------
 * Description:
 * <your description here>
 *-----------------------------------------------------------------------------
*/
#include <stdio.h>
#include "battleship.h"

static CellContent me[FIELDSIZE][FIELDSIZE];
static CellContent opponent[FIELDSIZE][FIELDSIZE];
static CellContent guess[FIELDSIZE][FIELDSIZE];





void load_game(){
  FILE * fd1 = fopen("battleship.my", "r");
  FILE * fd2 = fopen("battleship.op", "r");

  for (int y = 0; y < FIELDSIZE; y++) {
    for (int x = 0; x < FIELDSIZE; x++) {
      fread(&me[x][y],4,1,fd1);
      fread(&opponent[x][y],4,1, fd2);
      guess[x][y] = Unknown;
    }
  }
  fclose(fd1);
  fclose(fd2);
}


CellContent get_shot(int row, int col){
  if(row < 0 || row >= FIELDSIZE || col < 0 || col >= FIELDSIZE) return OutOfRange;
  return me[col][row];
}

bool shoot(int row, int col){
 CellContent check = get_my_guess(row,col);
 if(check == OutOfRange) return false;

 if(opponent[col][row] == Boat || opponent[col][row] == Water)
 {

   guess[col][row] = opponent[col][row];
   if(guess[col][row] == Boat)
   {
     for (int i = -1; i < 2; i++)
     {
       for (int j = -1; j < 2; j++)
        {
         check = get_my_guess(row+j,col+i);
         if (check == Unknown)
         {
           guess[col+i][row+j] = Water;
         }
       }
     }
   }
 }
  return true;
}

CellContent get_my_guess(int row, int col){
  if(row < 0 || row >= FIELDSIZE || col < 0 || col >= FIELDSIZE) return OutOfRange;
  return guess[col][row];
}
