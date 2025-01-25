/********************************************************
 **     File: project_reversi_skeleton.c               **
 **     Author: APS105 Teaching Team                   **
 **     Modified By: Dhruv Sharma                      **
 **     Date of Submission: Monday, April 5th, 2021    ** 
 **     Purpose: Reversi Game Part 1 ( Simple AI)      **
 *******************************************************/ 

#ifndef SKELETON_H
#define SKELETON_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// Function Declrations for part 1 of the project
void printBoard(char board[26][26], int n);
bool positionInBounds(int n, int row, int col);
bool checkLegalInDirection(char board[26][26], int n, int row,
 		int col, char colour, int deltaRow, int deltaCol);

// Function Declration for part 2 of the project
int makeMove(const char board[26][26], int n, char turn, int *row, int *col);

#endif

// Note: You may want to add more function declarations here
// =========   Function declaration  ==========
void printColumnLabels(int n);
bool checkMoveLegality(char board[26][26], int n, int row, int col, char colour);
bool movesAvailable(char board[26][26], int n, char colour);
void flipTiles(char board [26][26], int n, char moveRow, char moveCol, char moveColour);
void flipTilesInDirection(char board [26][26], int n, int row, int col, char colour, int deltaRow, int deltaCol);
void compMoveMaker(char board[26][26], int n, char colour);
int addMoveScore(char board[26][26], int n, int row, int col, int colour);
int addMoveScoreInDirection(char board[26][26], int n, int row, int col, int colour, int deltaRow, int deltaCol);
void declareWinner(char board[26][26], int n, char playerColour);
// ========= Function implementation ==========

//main function
int main(void) {
    // Complete your main function here
    int boardDimension, rowCount, colCount;
    char board[26][26]; // initializing the board array
    char playerColour = ' ';
    char compColour, rowMove, colMove;
    
    //Asking for board dimensions from the user
    printf("Enter the board dimension: ");
    scanf("%d", &boardDimension);
    
    //Assigning each element an initial Unoccupied character
    for(rowCount = 0; rowCount < boardDimension; rowCount ++){
        for(colCount = 0; colCount < boardDimension; colCount ++){
            board[rowCount][colCount] = 'U';
        }
    }
    
    //Elements in the middle are assigned W and B diagonally.
    board[(boardDimension/2)-1][(boardDimension/2)-1] = 'W';
    board[(boardDimension)/2][(boardDimension)/2] = 'W';
    board[(boardDimension/2)][(boardDimension/2)-1] = 'B';
    board[(boardDimension/2)-1][(boardDimension/2)] = 'B';
    
    //prompting the player for which colour the computer is going to play
    printf("Computer plays (B/W) : ");
    scanf(" %c", &compColour);
    
    //Assigning player colour based on input, making move if compColour is black, or printining error message if input is invalid
    if(compColour == 'B'){
        playerColour = 'W';
        printBoard(board, boardDimension);
        compMoveMaker(board, boardDimension, compColour);
    }
    else if(compColour == 'W'){
        playerColour = 'B';
    }
    else{
        printf("Invalid colour.\nPlease restart the program and try again.");
    }
    
    //printing initial board configuration, or printing board after computer's first move
    printBoard(board, boardDimension); 

    while(movesAvailable(board, boardDimension, playerColour) || movesAvailable(board, boardDimension, compColour)){ //If moves are available for either player or computer, loop keeps going.
        
        //check if moves are available for the player and then prompt user for first move.
        if(movesAvailable(board, boardDimension, playerColour)){
            printf("Enter move for colour %c (RowCol): ", playerColour);
            scanf(" %c%c", &rowMove, &colMove);
           
            //check if move is legal and then perform move if it is legal.
            if(checkMoveLegality(board, boardDimension, (rowMove-'a'), (colMove-'a'), playerColour) && positionInBounds(boardDimension, rowMove, colMove)){
                flipTiles(board, boardDimension, rowMove, colMove, playerColour);
                board[rowMove-'a'][colMove-'a'] = playerColour;
                printBoard(board, boardDimension);
            }
            else{
                printf("Invalid move.\n%c player wins.", compColour); //print error message if move is invalid
                return 0;
            }
        }
        else if(movesAvailable(board, boardDimension, compColour)){ //if move is legal but cannot be performed, check if computer has moves remaining and print no legal moves message
            
            printf("%c player has no valid move.\n", playerColour);
        }
        
        //check to see if computer has any moves available and then perform the move if they are
        if(movesAvailable(board, boardDimension, compColour)){
            compMoveMaker(board, boardDimension, compColour);
            printBoard(board, boardDimension);
        } 
        //otherwise if no moves are available then check if player has moves and print error message.
        else if(movesAvailable(board, boardDimension, playerColour)){
            
            printf("%c player has no valid move.\n", compColour);
        }
        
    }
    
    //call function to go through board to see which player has won.
    declareWinner(board, boardDimension, playerColour);
    
    return 0;
}


/*
* Function:  printColLabels
* --------------------
* Purpose: Prints the column labels for the board
* Employed by: printBoard function.
*/
void printColumnLabels(int n){
    int counter;
    printf("  ");
    
    for(counter = 0; counter < n; counter ++){
        printf("%c", (char) (97+counter));//for loop iterating through alphabets till board dimension.
    }
    printf("\n");
}

/*
* Function:  printBoard
* --------------------
* Purpose: Prints the whole board to the terminal window. 
* Employed by: main, printBoardConfiguration, and checkValidAnd Flip functions.
*/
void printBoard(char board[26][26], int n) {
    
    int rowCount, colCount;
    
    printColumnLabels(n); //to print board array, first column labels are printed
    
    for(rowCount = 0; rowCount < n; rowCount++){
        printf("%c ", 97+rowCount);//first alphabets for each row are printed
        for(colCount = 0; colCount < n; colCount++){
            printf("%c", board[rowCount][colCount]);//for loop printing board
        }
        printf("\n");
    }
}


/*
* Function:  movesAvailable
* --------------------
* Purpose: Checks if any legal moves for the given colour are available at the moment it is employed by checking board.
* Employed by: main function.
*/
bool movesAvailable(char board [26][26], int n, char colour){
    int row, col;
    
    for(row = 0; row < n; row++){
        for(col = 0; col < n; col++){//nested for loops moving through each element
            if(board[row][col] == 'U'){ // first check to see if element is empty
                if(checkMoveLegality(board, n, row, col, colour)){ //all move legality is checked for empty element
                    return true;
                }
            }
        }
    }
    return false;
}

/*
* Function:  checkMoveLegality
* --------------------
* Purpose: Checks all the legal moves that can be made for a particular element of the board. 
* Employed by: movesAvailable and checkValidAndFlip functions .
*/
bool checkMoveLegality(char board[26][26], int n, int row, int col, char colour){
    char oppColour;
    
    //opposite colours assigned based on input.
    if(colour == 'W'){
        oppColour = 'B';
    }
    if(colour == 'B'){
        oppColour = 'W';
    }
    
    for(int deltaRow = -1; deltaRow <= 1; deltaRow ++){
        for(int deltaCol = -1; deltaCol <=1; deltaCol ++){ // nested for loops for each direction
            if(deltaRow == 0 && deltaCol == 0); // since (0,0) is the element itself, so no check is required and it is skipped
            else if(positionInBounds(n, ('a'+row+deltaRow), ('a'+col+deltaCol))){ // position of neighbouring elements within bounds are checked
                if(board[row+deltaRow][col+deltaCol] == oppColour){ // check to see if any neighbouring element is of the opposite colour
                    if(checkLegalInDirection(board, n, row, col, colour, deltaRow, deltaCol)) // Finally, if move legality checked for each direction
                        return true;
                }
            }
        }
    }
    return false;  //false returned if the element doesn't have a legal move.
}

/*
 * Function:  positionInBounds 
 * --------------------
 * Checks whether the specified (row, col) lies within the board dimensions.
 * Employed by: checkMoveLegality function.
 */
bool positionInBounds(int n, int row, int col) {
    int r = row - 'a';
    int c = col - 'a';
    if(r >= 0 && c >= 0 && r < n && c < n) //bounds of array checked using if statement.
        return true;
    else
        return false;
}

/*
 * Function:  checkLegalInDirection 
 * --------------------
 * Checks whether (row, col) is a legal position for a tile of colour by “looking” in the direction 
 * specified by deltaRow and deltaCol.
 * Employed by: checkMoveLegality and flipTilesInDirection functions.
 */
bool checkLegalInDirection(char board[26][26], int n, int row, int col, char colour, int deltaRow, int deltaCol) {
    char oppColour;
    
    //assigning opposite colour depending on input.
    if(colour == 'W'){
        oppColour = 'B';
    }
    else if(colour =='B'){
        oppColour = 'W';
    }
    
    //starting at the input element, moving through all tiles in given direction
    for(int rowCounter = row, colCounter = col; 0 <= rowCounter && rowCounter < n && 0 <= colCounter && colCounter < n; 
        rowCounter += deltaRow, colCounter += deltaCol){ 
        //neighbouring position in the given direction must be opposite colour.
        if(board[row+deltaRow][col+deltaCol] == oppColour){
            
            //if there is an element of the same colour, then move is legal in that direction.
            if(board[rowCounter+deltaRow][colCounter+deltaCol] == colour){
                if(positionInBounds(n, ('a'+rowCounter+deltaRow), ('a'+colCounter+deltaCol))){
                    return true;
                }
            }
            //otherwise, if an empty element is reached, then false is returned
            else if(board[rowCounter+deltaRow][colCounter+deltaCol] == 'U'){
                return false;
            }
        }
    }
    return false;
}

/*
* Function:  flipTiles
* --------------------
* Purpose: flips tiles for a given move made after checking move legality.
* Employed by: main function.
*/
void flipTiles(char board[26][26], int n, char moveRow, char moveCol, char moveColour){
    
    //converting user input character into integer
    int moveRowInt = moveRow - 'a';
    int moveColInt = moveCol - 'a';
    
    //if move is valid, then neighbouring tile with opposite element is located and tiles flipped in that direction
    for(int deltaRow = -1; deltaRow <= 1; deltaRow ++){
        for(int deltaCol = -1; deltaCol <= 1; deltaCol ++){
            if(deltaRow == 0 && deltaCol == 0);
            else
                flipTilesInDirection(board, n, moveRowInt, moveColInt, moveColour, deltaRow, deltaCol); //tiles flipped in given direction
        }
    }

}

/*
* Function:  flipTilesInDirection
* --------------------
* Purpose: flips the tiles of a given colour to the same colour in a given direction. 
* Employed by: flipTiles function.
*/
void flipTilesInDirection(char board [26][26], int n, int row, int col, char colour, int deltaRow, int deltaCol){
    char oppositeColour;
    
    //opposite colours are assigned
    if(colour == 'W'){
        oppositeColour = 'B';
    }
    if(colour == 'B'){
        oppositeColour = 'W';
    }
    
    if(board [row][col] == 'U'){
        
        // board element is checked for legal direction, then a for loop moving through each element and flipping opp colours is executed
        if(checkLegalInDirection(board, n, row, col, colour, deltaRow, deltaCol)){ 
            for(int i = 0; i < n; i++){
                if(board[row + (deltaRow*i)][col + (deltaCol*i)] == oppositeColour){
                    board[row + (deltaRow*i)][col + (deltaCol*i)] = colour;
                }
                else if(board[row + (deltaRow*i)][col + (deltaCol*i)] == colour)
                    return; // when the same colour is reached, then function exits
            }
        }
        else
            return; // if element is not empty, then function exits
    }
    return;
}

/*
 * Function:  compMoveMaker
 * --------------------
 * Purpose: the computer makes a move whenever it is called by analysing the board and employing an algorithm to determine the best move
 * Employed by: main function
 */
void compMoveMaker(char board[26][26], int n, char colour){
    
    //initialize pointers and local variables
    int *row, *col;
    int bestRow = 0, bestCol = 0;
    
    //assign row and col the address of bestRow and bestCol, which is passed into makeMove function
    row = &bestRow;
    col = &bestCol;
    
    //alter row and col pointers after determining best move and performing the move( in this case after determining the move for which max tiles are flipped)
    makeMove(board, n, colour, &bestRow, &bestCol);
    flipTiles(board, n, ('a'+*row), ('a'+*col), colour);
    printf("Computer places %c at %c%c.\n", colour, (*row+'a'), (*col+'a'));
    board[*row][*col] = colour; //board element is changed to move colour

}

/*
 * Function:  makeMove 
 * --------------------
 * The player "turn" makes a move at (row, col).
 * Employed by: compMoveMaker function.
 * Note: This function MUST NOT change board, only row and col can be changed to reflect the move.
 */
int makeMove(const char board[26][26], int n, char turn, int *row, int *col) {
    
    int rowCount, colCount, bestRow, bestCol;
    int score = 0;
    int scoreCounter = 0;
    
    //move through entire board array
    for(rowCount = 0; rowCount < n; rowCount++){
        for(colCount = 0; colCount < n; colCount++){
            if(board[rowCount][colCount] == 'U' && checkMoveLegality(board, n, rowCount, colCount, turn)){ //check if move is legal and then add a score to that spot
                score = addMoveScore(board, n, rowCount, colCount, turn);
            }
            if(score > scoreCounter){ // store that score in a temp variable only if it has a score of 1 or more
                scoreCounter = score;
                bestRow = rowCount;
                bestCol = colCount;
            }
        }
    }
    
    *row = bestRow; // assign value at row to be the best row and col that we have determined using the greedy method
    *col = bestCol;
    
    return 0;
}

/*
 * Function:  addMoveScore
 * --------------------
 * Purpose: Goes through each direction of the given computer move and makes a score for the given move
 * Employed by: makeMove function
 */
int addMoveScore(char board[26][26], int n, int row, int col, int colour){
    int moveScore = 0;
    int deltaRow, deltaCol;
    // for a given legal move, score each direction except for 0,0 since that will go no where as it is the element itself.
    for(deltaRow = -1; deltaRow <= 1; deltaRow++){
        for(deltaCol = -1; deltaCol <= 1; deltaCol++){
            if(deltaRow == 0 && deltaCol == 0);
            else
                moveScore += addMoveScoreInDirection(board, n, row, col, colour, deltaRow, deltaCol);
        }
    }
    
    return moveScore;
}

/*
 * Function:  addMoveScoreInDirection
 * --------------------
 * Purpose: Generates a score for a given move in a given direction 
 * Employed By: addMoveScore function.
 */
int addMoveScoreInDirection(char board[26][26], int n, int row, int col, int colour, int deltaRow, int deltaCol){
    int moveScore = 0;
    char oppColour;
    

    //assign opposite colours
    if(colour == 'W'){
        oppColour = 'B';
    }
    else if(colour == 'B'){
        oppColour = 'W';
    }
    
    //first check if move is legal and then keep adding 1 to the score if an opposite colour tile is reached.
    if(board[row][col] == 'U' && checkLegalInDirection(board, n, row, col, colour, deltaRow, deltaCol)){
        for(int i = 1; i <= n; i++){
            if(board[row+deltaRow*i][col+deltaCol*i] == oppColour){
                moveScore++;
            }
            else if(board[row+deltaRow*i][col+deltaCol*i] == colour){
                return moveScore;
            }
        }
    }
    else
        return 0;
    
}

/*
 * Function:  declareWinner
 * --------------------
 * Purpose: After all moves are made, it checks the entire board to see who has won.
 * Employed By: main function.
 */
 void declareWinner(char board[26][26], int n, char playerColour){
     
     int playerTiles = 0;
     int computerTiles = 0;
     char compColour;
     
     if(playerColour == 'B'){
          compColour = 'W';
     }
     else if(playerColour == 'W'){
         compColour = 'B';
     }
     
     //move through entire array to see which colour has more tiles and then declare winner or tie based on that number.
     for(int row = 0; row < n; row++){
         for(int col = 0; col < n; col++){
             if(board[row][col] == playerColour){
                 playerTiles += 1;
             }
             else if(board[row][col] == compColour){
                 computerTiles += 1;
             }
         }
     }
     
     if(playerTiles > computerTiles){
         printf("%c player wins.\n", playerColour);
         return;
     }
     else if(playerTiles == computerTiles){
         printf("The game has ended in a tie.");
        return;
     }
     else if(playerTiles < computerTiles){
         printf("%c player wins.\n", compColour);
         return;
     }
     return;
 }


#ifndef COMPETE_MODE // DO NOT DELETE THIS LINE

#endif // DO NOT DELETE THIS LINE