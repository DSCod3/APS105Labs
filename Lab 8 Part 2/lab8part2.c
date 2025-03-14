/********************************************************
 **     File: project_reversi_skeleton.c               **
 **     Author: APS105 Teaching Team                   **
 **     Modified By: Dhruv Sharma                      **
 **     Date of Submission: Monday, March 22nd, 2021   ** 
 **     Purpose: Reversi Game                          **
 *******************************************************/ 

 #ifndef SKELETON_H
 #define SKELETON_H
 
 #include <stdio.h>
 #include <stdbool.h>
 #include <stdlib.h>
 #include "lab8part2lib.h"
 
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
 char oppColour(char colour);
 bool checkMoveLegality(char board[26][26], int n, int row, int col, char colour);
 bool movesAvailable(char board[26][26], int n, char colour); 
 void printLegalMovesAvailable(char board[26][26], int n, char colour);
 void flipTiles(char board [26][26], int n, char moveRow, char moveCol, char moveColour);
 void flipTilesInDirection(char board [26][26], int n, int row, int col, char colour, int deltaRow, int deltaCol);
 void playerMoveMaker(char board[26][26], int n, char colour);
 void compMoveMaker(char board[26][26], int n, char colour);
 int minimax(char board[26][26], int n, char colour, bool maximizeComp, int *row, int *col, int depth);
 int boardScore(char board[26][26], int n, char colour);
 int max(int maxEval, int eval);
 int min(int minEval, int eval);
 int addMoveScore(char board[26][26], int n, int row, int col, int colour);
 int addMoveScoreInDirection(char board[26][26], int n, int row, int col, int colour, int deltaRow, int deltaCol);
 void declareWinner(char board[26][26], int n, char playerColour);
 
 // ======= New function declarations for dynamic weight matrix and legal move count =======
 /*
  * Function: generateWeightMatrix
  * --------------------
  * Purpose: Generates a dynamic weight matrix based on board dimension.
  *          Corners are highly weighted, edges are moderately weighted,
  *          and other positions are given a base weight.
  * Input: board dimension n, and a 2D array weights[26][26] to be filled.
  * Output: Fills the weights array.
  */
 void generateWeightMatrix(int n, int weights[26][26]);
 
 /*
  * Function: countLegalMoves
  * --------------------
  * Purpose: Counts the number of legal moves available for a given colour.
  * Input: board, board dimension n, and the colour.
  * Output: Returns the count of legal moves.
  */
 int countLegalMoves(char board[26][26], int n, char colour);
 
 // ======= New functions for Alpha–Beta Pruning =======
 /*
  * Function: minimax_ab
  * --------------------
  * Purpose: Modified minimax algorithm with alpha–beta pruning.
  *          Evaluates board positions for optimal move selection.
  * Input: board, board dimension n, current colour, maximizing flag,
  *        search depth, current alpha and beta values, and pointers to best move.
  * Output: Returns the evaluation score.
  */
 int minimax_ab(char board[26][26], int n, char colour, bool maximizeComp, int depth, int alpha, int beta, int *bestRow, int *bestCol);
 
 /*
  * Function: minimax
  * --------------------
  * Purpose: Wrapper for the alpha–beta minimax function with initial alpha and beta values.
  * Input: board, board dimension n, current turn colour, maximizing flag,
  *        pointers to row and col to store the best move, and search depth.
  * Output: Returns the evaluation score.
  */
 int minimax(char board[26][26], int n, char colour, bool maximizeComp, int *row, int *col, int depth);
 
 // ========= Function implementation ==========
 
 //main function
 int main(void) {
     // Complete your main function here
     int boardDimension, rowCount, colCount;
     char board[26][26]; // initializing the board array
     char playerColour = ' ';
     char compColour;
     int rowMove, colMove;
     
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
     
     //Assigning player colour based on input, making move if compColour is black, or printing error message if input is invalid
     if(compColour == 'B'){
         playerColour = 'W';
         printLegalMovesAvailable(board,boardDimension, compColour);
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
             printLegalMovesAvailable(board, boardDimension, playerColour);
             findSmartestMove(board, boardDimension, playerColour, &rowMove, &colMove);
             flipTiles(board, boardDimension, ('a'+rowMove), ('a'+colMove), playerColour);
             board[rowMove][colMove] = playerColour;
             printf("%c player places %c at %c%c.\n", playerColour, playerColour, ('a'+rowMove), ('a'+colMove));
             printBoard(board, boardDimension);
         }
         else if(movesAvailable(board, boardDimension, compColour)){ //if move is legal but cannot be performed, check if computer has moves remaining and print no legal moves message
             
             printf("%c player has no valid move.\n", playerColour);
         }
         
         //check to see if computer has any moves available and then perform the move if they are
         if(movesAvailable(board, boardDimension, compColour)){
             printLegalMovesAvailable(board, boardDimension, compColour);
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
     
     return 0; // default return value if no other path is taken
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
 
 char oppColour(char colour){
     if(colour == 'W'){
         return 'B';
     }
     else if(colour == 'B'){
         return 'W';
     }
     else
         return 'U';
 }
 
 /*
 * Function:  printBoard
 * --------------------
 * Purpose: Prints the whole board to the terminal window. 
 * Employed by: main, printBoardConfiguration, and checkValidAndFlip functions.
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
 * Function:  printLegalMovesAvailable
 * --------------------
 * Purpose: Prints all the legal moves available for the given element at that moment.
 * Employed by: main function.
 */
 void printLegalMovesAvailable(char board[26][26], int n, char colour) {
     bool moveFound = false;
     printf("Legal moves for %c:", colour);
     for (int row = 0; row < n; row++) {
         for (int col = 0; col < n; col++) {
             // Check if the cell is unoccupied and if it's a legal move
             if (board[row][col] == 'U' && checkMoveLegality(board, n, row, col, colour)) {
                 // Print move as row and column letters (e.g., "a1" becomes "aa"), we print row+‘a’ and col+‘a’)
                 printf(" %c%c", (char)(row + 'a'), (char)(col + 'a'));
                 moveFound = true;
             }
         }
     }
     if (!moveFound) {
         printf(" No legal moves");
     }
     printf("\n");
 }
 
 /*
 * Function:  checkMoveLegality
 * --------------------
 * Purpose: Checks all the legal moves that can be made for a particular element of the board. 
 * Employed by: movesAvailable and checkValidAndFlip functions .
 */
 bool checkMoveLegality(char board[26][26], int n, int row, int col, char colour){
     char oppositeColour;
     
     //opposite colours assigned based on input.
     oppositeColour = oppColour(colour);
     
     for(int deltaRow = -1; deltaRow <= 1; deltaRow ++){
         for(int deltaCol = -1; deltaCol <=1; deltaCol ++){ // nested for loops for each direction
             if(deltaRow == 0 && deltaCol == 0); // since (0,0) is the element itself, so no check is required and it is skipped
             else if(positionInBounds(n, ('a'+row+deltaRow), ('a'+col+deltaCol))){ // position of neighbouring elements within bounds are checked
                 if(board[row+deltaRow][col+deltaCol] == oppositeColour){ // check to see if any neighbouring element is of the opposite colour
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
     char oppositeColour;
     
     //assigning opposite colour depending on input.
     oppositeColour = oppColour(colour);
     
     //starting at the input element, moving through all tiles in given direction
     for(int rowCounter = row, colCounter = col; 0 <= rowCounter && rowCounter < n && 0 <= colCounter && colCounter < n; 
         rowCounter += deltaRow, colCounter += deltaCol){ 
         //neighbouring position in the given direction must be opposite colour.
         if(board[row+deltaRow][col+deltaCol] == oppositeColour){
             
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
 * Purpose: Asks for a move input, checks its legality, and performs it by flipping tiles in same colour. 
 * Employed by: main function.
 */
 void flipTiles(char board[26][26], int n, char moveRow, char moveCol, char moveColour){
     
     //converting user input character into integer
     int moveRowInt = moveRow - 'a';
     int moveColInt = moveCol - 'a';
     
     //if move is valid, then neighbouring tile with opposite element is located and tiles flipped in that direction
     for(int deltaRow = -1; deltaRow <= 1; deltaRow ++){
         for(int deltaCol = -1; deltaCol <= 1; deltaCol++){
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
     oppositeColour = oppColour(colour);
     
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
     
     int *row, *col;
     int bestRow = 0, bestCol = 0;
     int score;
     
     row = &bestRow;
     col = &bestCol;
     
     score = makeMove(board, n, colour, &bestRow, &bestCol);
     flipTiles(board, n, ('a'+*row), ('a'+*col), colour);
     printf("Computer places %c at %c%c.\n", colour, (*row+'a'), (*col+'a'));
     board[*row][*col] = colour; //board element is changed to move colour
 
 }
 
 /*
  * Function:  playerMoveMaker
  * --------------------
  * Purpose: the computer makes a move whenever it is called by analysing the board and using the player to make the best move somehow.
  * Employed by: main function
  */
 void playerMoveMaker(char board[26][26], int n, char colour) {
     char move[3];  // to store the row and column letters plus a null terminator
     int row, col;
     bool validMove = false;
     
     while (!validMove) {
         printf("Enter move for %c (rowcol): ", colour);
         scanf("%2s", move);  // read two characters; e.g., "ad"
         
         // Check if the input is in bounds using positionInBounds (expects characters)
         if (!positionInBounds(n, move[0], move[1])) {
             printf("Move out of bounds. Please try again.\n");
             continue;
         }
         
         // Convert letters to board indices (0-indexed)
         row = move[0] - 'a';
         col = move[1] - 'a';
         
         // Check that the position is unoccupied and that the move is legal
         if (board[row][col] != 'U') {
             printf("That square is already occupied. Please try again.\n");
         }
         else if (!checkMoveLegality(board, n, row, col, colour)) {
             printf("That move is not legal. Please try again.\n");
         }
         else {
             validMove = true;
         }
     }
     
     // Perform the move by flipping the necessary tiles and placing the piece.
     flipTiles(board, n, move[0], move[1], colour);
     board[row][col] = colour;
     printf("%c player places %c at %c%c.\n", colour, colour, move[0], move[1]);
 }
 
 /*
  * Function:  makeMove 
  * --------------------
  * The player "turn" makes a move at (row, col).
  * Note: This function MUST NOT change board, only row and col can be changed to reflect the move.
  */
 int makeMove(const char board[26][26], int n, char turn, int *row, int *col) {
     
     char futureBoard[26][26];
     int score;
     
     for(int i = 0; i < n; i++){
         for(int j = 0; j < n; j++){
             futureBoard[i][j] = board[i][j];
         }
     }
     score = minimax(futureBoard, n, turn, true, row, col, 5);    
     
     return score;
 }
 
 /*
  * ===== New Functions: Alpha–Beta Pruning and Dynamic Weight Matrix =====
  */
 
 /*
  * Function: minimax_ab
  * --------------------
  * Purpose: Modified minimax algorithm with alpha–beta pruning.
  *          Evaluates board positions for optimal move selection.
  * Input: board, board dimension n, current colour, maximizing flag,
  *        search depth, current alpha and beta values, and pointers to best move.
  * Output: Returns the evaluation score.
  */
 int minimax_ab(char board[26][26], int n, char colour, bool maximizeComp, int depth, int alpha, int beta, int *bestRow, int *bestCol) {
     int rowCount, colCount;
     int eval;
     char opp = oppColour(colour);
     
     // Terminal condition: maximum depth reached or no legal moves available
     if (depth == 0 || !movesAvailable(board, n, colour)) {
         return boardScore(board, n, colour);
     }
     
     if (maximizeComp) {
         int maxEval = -99999;
         for (rowCount = 0; rowCount < n; rowCount++){
             for (colCount = 0; colCount < n; colCount++){
                 if (board[rowCount][colCount] == 'U' && checkMoveLegality(board, n, rowCount, colCount, colour)){
                     char tempBoard[26][26];
                     // Copy board
                     for (int i = 0; i < n; i++){
                         for (int j = 0; j < n; j++){
                             tempBoard[i][j] = board[i][j];
                         }
                     }
                     // Simulate move for maximizing player
                     flipTiles(tempBoard, n, ('a' + rowCount), ('a' + colCount), colour);
                     tempBoard[rowCount][colCount] = colour;
                     
                     // Recursively evaluate move (opponent's turn)
                     eval = minimax_ab(tempBoard, n, opp, false, depth - 1, alpha, beta, NULL, NULL);
                     if (eval > maxEval) {
                         maxEval = eval;
                         if (bestRow != NULL && bestCol != NULL) {
                             *bestRow = rowCount;
                             *bestCol = colCount;
                         }
                     }
                     if (maxEval > alpha) {
                         alpha = maxEval;
                     }
                     if (beta <= alpha) {
                         return maxEval; // Beta cutoff
                     }
                 }
             }
         }
         return maxEval;
     } else { // Minimizing branch
         int minEval = 99999;
         for (rowCount = 0; rowCount < n; rowCount++){
             for (colCount = 0; colCount < n; colCount++){
                 if (board[rowCount][colCount] == 'U' && checkMoveLegality(board, n, rowCount, colCount, colour)){
                     char tempBoard[26][26];
                     // Copy board
                     for (int i = 0; i < n; i++){
                         for (int j = 0; j < n; j++){
                             tempBoard[i][j] = board[i][j];
                         }
                     }
                     // Simulate move for minimizing player
                     flipTiles(tempBoard, n, ('a' + rowCount), ('a' + colCount), colour);
                     tempBoard[rowCount][colCount] = colour;
                     
                     // Recursively evaluate move (opponent's turn)
                     eval = minimax_ab(tempBoard, n, opp, true, depth - 1, alpha, beta, NULL, NULL);
                     if (eval < minEval) {
                         minEval = eval;
                         if (bestRow != NULL && bestCol != NULL) {
                             *bestRow = rowCount;
                             *bestCol = colCount;
                         }
                     }
                     if (minEval < beta) {
                         beta = minEval;
                     }
                     if (beta <= alpha) {
                         return minEval; // Alpha cutoff
                     }
                 }
             }
         }
         return minEval;
     }
 }
 
 /*
  * Function: minimax
  * --------------------
  * Purpose: Wrapper for the alpha–beta minimax function with initial alpha and beta values.
  * Input: board, board dimension n, current turn colour, maximizing flag,
  *        pointers to row and col to store the best move, and search depth.
  * Output: Returns the evaluation score.
  */
 int minimax(char board[26][26], int n, char colour, bool maximizeComp, int *row, int *col, int depth) {
     return minimax_ab(board, n, colour, maximizeComp, depth, -99999, 99999, row, col);
 }
 
 /*
  * Function: generateWeightMatrix
  * --------------------
  * Purpose: Generates a dynamic weight matrix based on board dimension.
  *          Corners are highly weighted, edges are moderately weighted,
  *          and other positions are given a base weight.
  * Input: board dimension n, and a 2D array weights[26][26] to be filled.
  * Output: Fills the weights array.
  */
 void generateWeightMatrix(int n, int weights[26][26]) {
     for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            // Corners: high value
            if ((i == 0 && j == 0) || (i == 0 && j == n-1) || (i == n-1 && j == 0) || (i == n-1 && j == n-1)) {
                 weights[i][j] = 100;
            }
            // Squares adjacent to corners: negative value
            else if ((i == 0 && (j == 1 || j == n-2)) ||
                     (i == n-1 && (j == 1 || j == n-2)) ||
                     ((i == 1 || i == n-2) && (j == 0 || j == n-1))) {
                 weights[i][j] = -20;
            }
            // Edges: moderate value
            else if (i == 0 || i == n-1 || j == 0 || j == n-1) {
                 weights[i][j] = 10;
            }
            // Other positions: base value
            else {
                 weights[i][j] = 1;
            }
        }
     }
 }
 
 /*
  * Function: boardScore
  * --------------------
  * Purpose: Evaluates the board for a given colour using a dynamic weight matrix and mobility.
  *          This is the evaluation function for the minimax algorithm.
  * Input: board, board dimension n, and the colour to evaluate.
  * Output: Returns the computed score.
  */
 int boardScore(char board[26][26], int n, char colour) {
     int score = 0;
     char oppositeColour = oppColour(colour);
     int weights[26][26];
     
     // Generate dynamic weight matrix based on board dimension
     generateWeightMatrix(n, weights);
     
     // Evaluate board using weights for occupied squares
     for (int rowCount = 0; rowCount < n; rowCount++){
         for (int colCount = 0; colCount < n; colCount++){
             if(board[rowCount][colCount] == colour){
                 score += weights[rowCount][colCount];
             }
             else if(board[rowCount][colCount] == oppositeColour){
                 score -= weights[rowCount][colCount];
             }
         }
     }
     
     // Mobility: bonus based on difference in legal moves
     int myMoves = countLegalMoves(board, n, colour);
     int oppMoves = countLegalMoves(board, n, oppositeColour);
     score += 10 * (myMoves - oppMoves);
     
     return score;
 }
 
 /*
  * Function: countLegalMoves
  * --------------------
  * Purpose: Counts the number of legal moves available for a given colour.
  * Input: board, board dimension n, and the colour.
  * Output: Returns the count of legal moves.
  */
 int countLegalMoves(char board[26][26], int n, char colour) {
     int count = 0;
     for (int row = 0; row < n; row++){
         for (int col = 0; col < n; col++){
             if(board[row][col] == 'U' && checkMoveLegality(board, n, row, col, colour)){
                 count++;
             }
         }
     }
     return count;
 }
 
 int max(int maxEval, int eval){
     if(maxEval >= eval){
         return maxEval;
     }
     else if(maxEval < eval){
         return eval;
     }
     else
         return 0;
 }
 
 int min(int minEval, int eval){
     if(minEval <= eval){
         return minEval;
     }
     else if(minEval > eval){
         return eval;
     }
     else
         return 0;
 }
 
 int addMoveScore(char board[26][26], int n, int row, int col, int colour){
     int moveScore = 0;
     int deltaRow, deltaCol;
     
     for(deltaRow = -1; deltaRow <= 1; deltaRow++){
         for(deltaCol = -1; deltaCol <= 1; deltaCol++){
             if(deltaRow == 0 && deltaCol == 0);
             else
                 moveScore += addMoveScoreInDirection(board, n, row, col, colour, deltaRow, deltaCol);
         }
     }
     return moveScore;
 }
 
 int addMoveScoreInDirection(char board[26][26], int n, int row, int col, int colour, int deltaRow, int deltaCol){
     int moveScore = 0;
     char oppColour;
     
     if(colour == 'W'){
         oppColour = 'B';
     }
     else if(colour == 'B'){
         oppColour = 'W';
     }
     
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
     return 0;
 }
 
 /*
  * Function:  declareWinner
  * --------------------
  * Purpose: After all moves are made, it checks the entire board to see who has won.
  * Employed By: main function
  */
  void declareWinner(char board[26][26], int n, char playerColour){
      
      int playerTiles = 0;
      int computerTiles = 0;
      char compColour;
      
      compColour = oppColour(playerColour);
      
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
 