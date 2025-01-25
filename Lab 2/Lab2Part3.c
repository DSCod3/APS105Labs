/********************************************************
 **     Definition: This is my Lab 2 Part 3 code in C  **                                         
 **     Author: Dhruv Sharma                           **
 **     Student Number: 1006926631                     **
 **     Date of Submission: Monday, January 25th, 2021 ** 
 **     IDE used: Codelite                             **
 *******************************************************/ 

/*Firstly we include the stdio and math libraries, from which we will
* use the printf, scanf and pow functions to solve the given problem.*/
#include <stdio.h>
#include <math.h>

int main()
{
/* We begin by declaring the Initial Deposit P, the compounding frequency n, the interest rate r, the time period t, 
 * the future value A, the base and power of the growth of the investment, and the growth rate as double numbers.*/
    double P, n, r, t, A, GrowthBase, GrowthPower, GrowthRate;
    
/*We begin by entering the principal value or the initial deposit P.*/
    printf("The amount deposited P: ");
    scanf(" %lf", &P);
    
/*We then enter the rate of interest as a decimal value, which will be between 0.00 and 0.100,
 * since it is a percentage.*/
    printf("The interest rate r: ");
    scanf(" %lf", &r);
    
/* We then move on to entering the frequency of the compounding interest, which will vary
 * based on whether it is yearly, monthly, weekly, daily or a custom frequency. */
    printf("The number of times the interest is compounded n: ");
    scanf(" %lf", &n);
    
/* Finally, we enter the time period of the investment, which is in years. */
    printf("The period of time t the money is invested (in years): ");
    scanf(" %lf", &t);
    
/* In order to apply the compound interest formula, we first split the formula into two parts, the principal and the growth.
 * Now, we first compute the exponential/growth component by defining the base and power of it. */
    GrowthBase = (1+(r/n));
    GrowthPower = n*t;
    
/* Further we use the pow function from the math.h library to calculate the exponent. */
    GrowthRate = pow(GrowthBase, GrowthPower);
    
/*Finally, we calculate the future value of investment by multiplying the Initial Deposit with the Growth Rate (the exponent),
 * and output the value. */
    A = P*GrowthRate;
    printf("The future value of the investment A: %.2lf\n", A);
    
    return 0;
    
/* Thus, by using the math and stdio libraries, we can calculate compound interest for a given initial investment, 
 * growth rate, frequency and time period using C language.*/
    
    }
    