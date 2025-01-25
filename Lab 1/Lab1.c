/********************************************************
 **     Definition: This is my Lab 1 code in C         **                                         
 **     Author: Dhruv Sharma                           **
 **     Student Number: 1006926631                     **
 **     Date of Submission: Monday, January 25th, 2021 ** 
 **     IDE used: Codelite                             **
 *******************************************************/ 
 
 /*We include the stdio library to use printf and scanf functions as well as basic mathematical operators
  * to solve the given problem and output the correct values.*/
#include <stdio.h>

 int main() 
 { 
     int     totnumbers=3;
     int     x = 2;
     double  FN, SN, TN;
     double  HalfSum, TwiceProduct, Average;
    
/* First we input the first double number */
     printf("Enter First Number: ");
     scanf("%lf", &FN);
     
/* We move on to input the second double number */
     printf("Enter Second Number: ");
     scanf("%lf", &SN);

/* Finally we input the third double number */
     printf("Enter Third Number: ");
     scanf("%lf", &TN);
     
/* Calculate and display the half of the sum of the three double numbers*/
     HalfSum=(FN + SN + TN)/x;
     printf("Half the Sum: %.2lf\n", HalfSum);
     
/* Calculate and display twice the product of the three double numbers */
     TwiceProduct=x*(FN*SN*TN);
     printf("Twice the Product: %.2lf\n", TwiceProduct);
     
/* Finally Calculate and display the average of the three double numbers */
     Average = (FN + SN + TN)/totnumbers;
     printf("Average: %.2lf\n", Average);

return 0;

/* Thus, we have successfully used C language to input three double numbers and calculate half of their sum, 
 * twice their product, and their average using printf and scanf functions and concluded the Lab 1 program*/

 }