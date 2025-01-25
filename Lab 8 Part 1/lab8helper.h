/*
 * File:   lab8helper.h
 * Author: Siwei He
 *
 * Date: March 2021
 */

// NOTE: Do NOT change this file, add more functions in your C file
#ifndef LAB8HELPER_H
#define LAB8HELPER_H

#include <stdbool.h>

/**
 * Function Declrations for the project, the purpose of the functions are
 * stated in your lab handout
 */
void _reference_printBoard(char board[][26], int n);
bool _reference_positionInBounds(int n, int row, int col);
bool _reference_checkLegalInDirection(char board[][26], int n, int row,
 		int col, char colour, int deltaRow, int deltaCol);

/**
 * This function flips the piece(s), starting at (row, col) in the direction
 * specified by rowStep and colStep.  This is also used for scoring.
 * if the parameter doFlip is 1, the actual flipping happens; otherwise,
 * no flipping happens.  In either case, the function returns the number
 * of pieces that are/would be flipped in the particular direction.
 */
int _reference_flipInDirection(char board[][26], int row, int col, 
        char colour, int rowStep, int colStep, bool doFlip);

/**
 * This function checks whether, for colour, row,col is a valid move.
 * If flip is true, it actually goes ahead and makes the move.
 * This function returns the number of tiles that would be flipped
 * if colour were placed and row, col.
 */
int _reference_checkValidAndFlip(char board[][26], int row, int col, char colour, int n, bool flip);

#endif