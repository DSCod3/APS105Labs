/********************************************************
 **     Definition: This is my Lab 2 Part 1 code in C  **                                         
 **     Author: Dhruv Sharma                           **
 **     Student Number: 1006926631                     **
 **     Date of Submission: Monday, January 25th, 2021 ** 
 **     IDE used: Codelite                             **
 *******************************************************/ 

/* Firstly, we include the stdio and math libraries that allow us to use the printf, scanf, and
 * floor functions, which are going to help us solve the given problem with ease.*/
#include <stdio.h>
#include <math.h>

int main()
{
    double CashbackAmt = 0.10;
    int SpendingperCashback = 3;
    double PricePerPound, TotWeight, UndiscountedCharge, Times3$spent, TotCharge, Savings;
    
/* We begin by entering the price per pound of the produce that we spend in the store.*/
    printf("Enter the price per pound: ");
    scanf("%lf", &PricePerPound);
    
/* We then enter the total weight of produce bought by us (in pounds). */
    printf("Enter the total weight: ");
    scanf("%lf", &TotWeight);
    
/* Now, we calculate the cost of the produce we bought without applying the promotion
 * by multiplying the price per pound with the weight that we entered before. */
    UndiscountedCharge= PricePerPound*TotWeight;
    
/* In order to caluclate the Savings, we are initially calculating the number of 
 * multiples of 3 dollars that we are spending without the discount by using the
 * floor function, which rounds the decimal number we get by dividing the undiscounted charge
 * with 3 dollars to find the multiples of 3 in the cost of the produce. */
    Times3$spent = floor(UndiscountedCharge/SpendingperCashback);
    
/* We can now calculate the savings by simply multiplying the number of multiples of 3
 * dollars with the cashback of 10 cents we receive for each  3 dollars spent.*/
    Savings = Times3$spent*CashbackAmt; 
    
/* Finally, we can easily calculate the total charge of the produce after the promotion
 * by subtracting the savings from the undiscounted charge of the produce.*/
    TotCharge = UndiscountedCharge-Savings;
    
/*Finally, we just use the printf function twice to display the total charge and savings
 * on the produce that we buy. */
    printf("The total charge is: %.2lf\n", TotCharge);
    printf("You saved: %.2lf\n", Savings );

    return 0;

/*Thus, by using clever mathematics, we are able to execute a basic discounting function on produce brought from a store. */

    }