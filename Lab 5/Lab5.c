/********************************************************
 **     Definition: This is my Lab 5 code in C         **                                         
 **     Author: Dhruv Sharma                           **
 **     Student Number: 1006926631                     **
 **     Date of Submission: Monday, February 22th, 2021** 
 **     Purpose: Making a Pascal's Triangle            **
 *******************************************************/ 
 
#include <stdio.h>

/* Declaring the given three functions so that they can be defined and called later.*/
void triangle (int numberOfRows);
int choose (int n, int r);
int factorial (int n);

int main(){
    int numberOfRows = 1;
 
/*Code loops for all numbers from 0 to 13. However, the triangle
 * is only formed when numbers is from 1 to 13.*/   
    while(numberOfRows < 14 && numberOfRows >=0){
        printf("Enter the number of rows: ");
        scanf("%d", &numberOfRows);
        
        if(numberOfRows < 14 && numberOfRows >0)
            triangle(numberOfRows);  // Calling triangle function in main.
    } 
    
    return 0;
}

/*Defining the triangle function, which inputs values taken before.*/
void triangle(int numberOfRows){
    
/* Printing Leading white spaces and numbers through nested for loops.*/
    for (int row = 0; row < numberOfRows; row ++){
        
        for(int column = 1; column < numberOfRows-row; column ++){
            printf("   ");
        }
        
        for(int column = 0; column <= row; column ++){
            int nCr = choose(row, column);
            
/*Dynamic spacing between numbers to ensure correct formatting.
 * 5 are printed when single digit, 4 when double digit, and 3 when triple digit.*/
            if(nCr < 10){
                printf("%d", nCr);
                printf("     ");
            }
            else
                if(nCr < 100 && nCr >= 10){
                    printf("%d", nCr);
                    printf("    ");
                }

            else
                if(nCr < 1000 && nCr >= 100){
                    printf("%d", nCr);
                    printf("   ");
                }
        }
        printf("\n");
    }
    
}

/*Defining function choose which calculates number of ways of choosing r from n (called in triangle function).*/
int choose(int n, int r){
    if(n == r)
        return 1;
    else
        return factorial(n)/(factorial(r)*factorial(n-r));
}

/*Defining factorial function to calculate factorials with ease using a for loop.
 * Can also be done through while loops and recursions (called in choose function).*/
int factorial(int n){
    int product = 1;
    for(int i=1; i<= n; i++){
        product *= i;
    }
    
    return product;
}
