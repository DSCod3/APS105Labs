/********************************************************
 **     Definition: This is my Lab 2 Part 2 code in C  **                                         
 **     Author: Dhruv Sharma                           **
 **     Student Number: 1006926631                     **
 **     Date of Submission: Monday, January 25th, 2021 ** 
 **     IDE used: Codelite                             **
 *******************************************************/ 

/*Firstly we include the stdio and math libraries, from which we will
* use the printf, scanf and round functions to solve the given problem.*/
#include <stdio.h>
#include <math.h>

int main()
{
    double Nickel = 0.05;
    float PriceOfGroceries, UnroundedNickelsInPrice, RoundedNickelsInPrice, TotalCharge;
    
    
/*We begin by entering the price of the groceries as a floating point number. */
    printf("Enter the price as a float with two decimals: ");
    scanf(" %f", &PriceOfGroceries);
    
/* To round the price to the nearest nickel, we first calculate     
 * the value of the nickels in their barebones or decimal form by   
 * by dividing the price with the value of a Nickel, which is 0.05$.*/
    UnroundedNickelsInPrice = PriceOfGroceries/Nickel;
    
/* Now, with the help of the round function in the math library,
 * we calculate the rounded number of nickels in the price.*/
    RoundedNickelsInPrice = roundf(UnroundedNickelsInPrice);
    
/* Finally, we multiply this rounded number of nickels with 
 * the value of a nickel to get the rounded price of the groceries
 * to the nearest nickel and print the given statement.*/
    TotalCharge = Nickel*RoundedNickelsInPrice;
    printf("The total charge is: %.2f\n", TotalCharge);
    
    return 0;
    
/* Thus, by using clever math and the roudn fucntion to our advantage, we can
 * solve the given problem and compute the rounded price. Reflecting back, this method
 * is one that I found easier than using if conditions. */
    }