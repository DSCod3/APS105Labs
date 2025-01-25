/********************************************************
 **     File: project_reversi_skeleton.c               **
 **     Author: APS105 Teaching Team                   **
 **     Modified By: Dhruv Sharma                      **
 **     Date of Submission: Monday, March 22nd, 2021   ** 
 **     Purpose: Reversi Game setup and do one move    **
 *******************************************************/ 
// #include "project_reversi_skeleton.h" //DO NOT modify this line
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


// Note: You may want to add more function declarations here
// =========   Function declaration  ==========
void printColumnLabels(int n);
void printBoardConfiguration(char board [26][26], int n);
void printLegalMovesAvailable(char board [26][26], int n, char colour);
bool checkMoveLegality(char board[26][26], int n, int row, int col, char colour);
void checkValidAndFlip(char board [26][26], int n);
void flipTilesInDirection(char board [26][26], int n, int row, int col, char colour, int deltaRow, int deltaCol);
bool positionInBounds(int n, int row, int col);
bool checkLegalInDirection(char board[26][26], int n, int row, int col, char colour, int deltaRow, int deltaCol);

// ========= Function implementation ==========
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
* Function:  printBoardConfiguration
* --------------------
* Purpose: Prints the board after taking in input for an initial configuration of the board. 
* Employed by: main function.
*/
void printBoardConfiguration(char board [26][26], int n){

    printf("Enter board configuration:");
    printf("\n");
    char colorConfig = ' ';
    char rowConfig, colConfig;
    
    for(int i = 0; (colorConfig != '!' && rowConfig != '!' && colConfig != '!'); i++){
        scanf(" %c%c%c", &colorConfig, &rowConfig, &colConfig);//input for initial configuration
        board[rowConfig - 'a'][colConfig - 'a'] = colorConfig;//converting characters to integers for each element and assigning new val.
    }
    
    printBoard(board, n);//new board is printed
}

/*
* Function:  printLegalMovesAvailable
* --------------------
* Purpose: Prints the legal moves for both black and white colours. 
* Employed by: main function.
*/
void printLegalMovesAvailable(char board [26][26], int n, char colour){
    printf("Available moves for %c:\n", colour);
    for(int row = 0; row < n; row++){
        for(int col = 0; col < n; col++){//nested for loops moving through each element
            if(board[row][col] == 'U'){ // first check to see if element is empty
                if(checkMoveLegality(board, n, row, col, colour)){ //all move legality is checked for empty element
                    printf("%c%c\n", ('a'+row), ('a'+col)); //if both checks are passed, then move is printed
                }
            }
        }
    }
}

/*
* Function:  checkMoveLegality
* --------------------
* Purpose: Checks all the legal moves that can be made for a particular element of the board. 
* Employed by: printLegalMovesAvailable and checkValidAndFlip functions .
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
        rowCounter = rowCounter + deltaRow, colCounter = colCounter + deltaCol){ 
        //position in the given direction must be opposite colour.
        if(board[row+deltaRow][col+deltaCol] == oppColour){
            
            //if there is an element of the same colour, then move is legal in that direction.
            if(board[rowCounter+deltaRow][colCounter+deltaCol] == colour){
                return true;
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
* Function:  checkValidAndFlip
* --------------------
* Purpose: Asks for a move input, checks its legality, and performs it by flipping tiles in same colour. 
* Employed by: main function.
*/
void checkValidAndFlip(char board[26][26], int n){
    char moveColour, moveRow, moveColumn; //declaring local variables
    
    //prompting user for input and converting user input character into integer
    printf("Enter a move:\n");
    scanf(" %c%c%c", &moveColour, &moveRow, &moveColumn);
    int moveRowInt = moveRow - 'a';
    int moveColumnInt = moveColumn - 'a';

    if(checkMoveLegality(board, n, moveRowInt, moveColumnInt, moveColour)){ //move legality is checked
        printf("Valid move.\n");
        
        //if move is valid, then neighbouring tile with opposite element is located and tiles flipped in that direction
        for(int deltaRow = -1; deltaRow <= 1; deltaRow ++){
            for(int deltaCol = -1; deltaCol <= 1; deltaCol ++){
                if(deltaRow == 0 && deltaCol == 0);
                else
                    flipTilesInDirection(board, n, moveRowInt, moveColumnInt, moveColour, deltaRow, deltaCol); //tiles flipped in given direction
            }
        }
        board[moveRowInt][moveColumnInt] = moveColour; //board element is changed to move colour
        printBoard(board, n); //final board after move is printed
    }
    else{
        printf("Invalid move.\n");
        printBoard(board, n); //if move is invalid, then same board is printed
    }
}

/*
* Function:  flipTilesInDirection
* --------------------
* Purpose: flips the tiles of a given colour to the same colour in a given direction. 
* Employed by: checkValidAndFlip function.
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
}

/*
 * Function:  makeMove 
 * --------------------
 * The player "turn" makes a move at (row, col).
 * Note: This function MUST NOT change board, only row and col can be changed to reflect the move.
 */
int makeMove(const char board[26][26], int n, char turn, int *row, int *col) {
    (void)board;
    (void)n;
    (void)turn;
    (void)row;
    (void)col;
    return 0;
}

#ifndef COMPETE_MODE // DO NOT DELETE THIS LINE

//main function
int main(void) {
    // Complete your main function here
    int boardDimension, rowCount, colCount;
    char board[26][26]; // initializing the board array
    
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
    
    printBoard(board, boardDimension); //prints the inital board configuration
    printBoardConfiguration(board, boardDimension);//prints the board configuration after asking for input to place additional tiles
    printLegalMovesAvailable(board, boardDimension, 'W'); //prints available moves for White
    printLegalMovesAvailable(board, boardDimension, 'B');//prints avaialbe moves for Black
    checkValidAndFlip(board, boardDimension);//Asks for an input for a move, checks its validity, and performs it.
}
#endif // DO NOT DELETE THIS LINE