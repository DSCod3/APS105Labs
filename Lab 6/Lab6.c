/********************************************************
 **     Definition: This is my Lab 6 code in C         **
 **     Author: Dhruv Sharma                           **
 **     Student Number: 1006926631                     **
 **     Date of Submission: Monday, March 8th, 2021    ** 
 **     Purpose: Battleship Populate Func              **
 *******************************************************/ 

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#define BOARDROWS 9
#define BOARDCOLS 11
bool dumpComputer = false; //causes dump of computer board before game if true (for
//debugging)//

// boards. 0 means empty, non-zero means ship is there, number is size, -tive means
//hit on a ship//
int playerBoard[BOARDROWS+1][BOARDCOLS+1];
int computerBoard[BOARDROWS+1][BOARDCOLS+1];
int compShotBoard[BOARDROWS+1][BOARDCOLS+1];
void populateBoard(bool getUserInput, int board[BOARDROWS+1][BOARDCOLS+1]);


int getRand(int lowval,int highval){
    return (rand()%(highval+1-lowval) + lowval);
}

int getShot(bool fromUser, int board[BOARDROWS+1][BOARDCOLS+1]){
    int row,col;
    
    while(1){
        if(fromUser){
            printf("Give a shot (row, col):");
            scanf("%d%d",&row,&col);
            if(col<1 || col > BOARDCOLS || row < 1 || row > BOARDROWS)
                printf("Invalid input\n");
            else  //valid input
                break;
        }
        else { //computer generated
            row=getRand(1,BOARDROWS);
            col=getRand(1,BOARDCOLS);
            if(compShotBoard[row][col]==0) { //make sure haven't shot here before
                compShotBoard[row][col]=1; //valid shot
                break;
            }
        }
    } //will leave this loop with valid input
    if(board[row][col] != 0){
        if(board[row][col]>0)
            board[row][col]= -1*board[row][col]; //make sure is -tive
        return -1*board[row][col]; //a hit!
    }
    return 0; //miss
}
            
bool allShipsNotHit(int board[BOARDROWS+1][BOARDCOLS+1]){
    for(int i=1;i<=BOARDROWS;i++){
        for(int j=1;j<=BOARDCOLS;j++){
            if(board[i][j]>0) //ship and not hit
                return(true);
        }
    }
    return (false); //no ships found not all hit
}

bool noneLeft(int valueToFind,int board[BOARDROWS+1][BOARDCOLS+1]){
    for(int i=1;i<=BOARDROWS;i++){
        for(int j=1;j<=BOARDCOLS;j++){
            if(board[i][j]==valueToFind) //ship and not hit
                return(false);
        }
    }
    return (true); //no ships found, all hit
}
    
void showBoard(int board[BOARDROWS+1][BOARDCOLS+1]){
    printf("   Cols\n");
    printf("    1  2  3  4  5  6  7  8  9 10 11\n");
    printf("     ________________________________\n");
    for(int i=1;i<=BOARDROWS;i++){
        printf("R%d|",i);
        for(int j=1;j<=BOARDCOLS;j++){
            if(board[i][j]>=0)
                printf(" ");
            printf("%d ",board[i][j]);
        }
        printf("|\n");
    }
    printf("  __________________________________\n");
}

int main(int argc, char **argv)
{
    bool playerBoardOK,computerBoardOK;
    
    // initialize the seed randomly. 
      srand(time(NULL)); 
    //init the boards
    for(int i=0;i<BOARDROWS;i++){
        for(int j=0;j<BOARDCOLS;j++){
            playerBoard[i][j]=0;
            computerBoard[i][j]=0;
            compShotBoard[i][j]=0;
        }
    }
    populateBoard(true,playerBoard);
    populateBoard(false,computerBoard);
    printf("Your board is\n");
    showBoard(playerBoard);
    if(dumpComputer){
        printf("\n\nComputer board is\n");
        showBoard(computerBoard);
    }
    // play starts here
    playerBoardOK=true;
    computerBoardOK=true;
    while(playerBoardOK && computerBoardOK){
        int hit=getShot(true,computerBoard); //shot from user
        if(hit){
            printf("HIT on size %d\n",hit);
            if(noneLeft(hit,computerBoard))
                printf("Sunk computer's %d\n",hit);
        }
        else
            printf("MISS!!\n");
        hit=getShot(false,playerBoard);
        if(hit){
            printf("Computer hits! Size=%d\n", hit);
            if(noneLeft(hit,playerBoard))
                printf("Sunk your %d\n",hit);
        }
        else
            printf("Computer miss!\n");
        playerBoardOK = allShipsNotHit(playerBoard);
        computerBoardOK = allShipsNotHit(computerBoard);
//    showBoard(playerBoard); //debug
//    showBoard(computerBoard); //debug
   }
   if(playerBoardOK)
       printf("You win!\n");
    else
        printf("You lose.\n");
    showBoard(computerBoard);
return 0;
}

// check if move valid
int checkValid(int board[BOARDROWS+1][BOARDCOLS+1],int col, int row, int size, int orientation){
    for(int i=1;i<=size;i++){
        if(col<1 || col > BOARDCOLS || row < 1 || row > BOARDROWS || orientation < 0 || orientation > 1)
            return 1; //error code, can't fit into space
        if(board[row][col] != 0) return 2; //error code, place already occupied
        if(orientation==0) //horizontal
            col++;
        else
            row++;
    }
    return 0;
}

//insert. Assumes valid.
void insertShip(int board[BOARDROWS+1][BOARDCOLS+1], int col, int row, int size, int orientation) {
    for(int i=1;i<=size;i++){
        board[row][col]=size;
        if(orientation==0) //horizontal
            col++;
        else
            row++;
    }
}


void populateBoard(bool getUserInput, int board[BOARDROWS+1][BOARDCOLS+1]){
    int numberToDo=5; //number yet to be done
    int row,column,orientation,errortype;
    
    // instructions to user
    if(getUserInput){
        printf("Rows are 1 - %d, Columns are 1 - %d\n",BOARDROWS,BOARDCOLS);
        printf("Orientation is 0 for across, 1 for down\n");
    }
   while(numberToDo>0){
        if(getUserInput){
            printf("Give starting row, starting column and orientation (3 inputs) for ship of size=%d:",numberToDo);
            scanf("%d %d %d",&row,&column,&orientation);
        }
        else { //computer input
            row=getRand(1,BOARDROWS);
            column=getRand(1,BOARDCOLS);
            orientation=getRand(0,1);
        }
        errortype = checkValid(board,column, row, numberToDo, orientation);    
       if(errortype==0){ //if no error
            insertShip(board,column,row,numberToDo,orientation);
            numberToDo--;
        }
        else {
            if(getUserInput){
                if(errortype == 1)
                    printf("Invalid Input\n");
                else
                    printf("Conflicts with ship already placed\n");
            }
                
        }
    }
}