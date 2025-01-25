/********************************************************
 **     Definition: This is my Lab 4 Part 2 code in C  **                                         
 **     Author: Dhruv Sharma                           **
 **     Student Number: 1006926631                     **
 **     Date of Submission: Monday, February 8th, 2021 ** 
 **     Purpose: Making a star triangle for given rows **
 *******************************************************/ 

#include <stdio.h>

int main(void)
{
    int row, column, numberOfRows;
 
/*We begin by inputting the number of rows in the triangle, which is
 * assumed to be between 1 and 20 using an if statement.*/   
    printf("Enter the number of rows in the triangle: ");
    scanf("%d", &numberOfRows);
    
    if(numberOfRows <= 20 && numberOfRows >= 1){
        
/*Used a for loop to move through each row of the triangle.*/        
       for(row = 1; row <= numberOfRows; row ++){
 
/*With the first nested for loop, we print white spaces that occur
 * before the first star, whose number is one less than the previous
 * line, so after every row, one less whitespace is printed.*/   
           for(column = row; column < numberOfRows; column ++){
               printf(" ");
           }
 
/*With second for, we print stars after whitespace every row since for column = 1,
 * a star is printed. Then, for every other value of column, a whitespace is printed
 * until the value of column is (2*row)-1, which I calculated was when the second star 
 * needed to be printed. Finally, for the final row, the for loop allows for only stars
 * to be printed until the for loop ends.*/       
           for(column = 1; column <= (2*row)-1; column ++){
               if(column == 1 || column == (2*row)-1 || row == numberOfRows){
                  printf("*");
               }
               else{
                  printf(" ");
               }
           } 
 
/*After each new row is printed, we move on to the next line using this printf statement within the first for loop.*/      
       printf("\n");
        
       }
    }
    
    return 0;

}
