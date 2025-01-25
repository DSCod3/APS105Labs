/********************************************************
 **     Definition: This is my Lab 4 Part 1 code in C  **                                         
 **     Author: Dhruv Sharma                           **
 **     Student Number: 1006926631                     **
 **     Date of Submission: Monday, February 8th, 2021 ** 
 **     Purpose: Describing the change for given cents **
 *******************************************************/ 
 
#include <stdio.h>

int main()
{
    int change = 1;
    int change1, change2, change3;
    
/*We assign an initial value of 1 to the change so that the while loop can begin.
 * We could have used a do while loop to remove initializing the change variable in the
 * beginning.*/
    while(change<100 && change >= 1){
        
/*First we take the input of the change in cents from the user.*/
          printf("Please give an amount in cents less than 100: ");
          scanf("%d", &change);
          
/*To ensure that the change is counted only when the user inputs a valid number 
 * of cents, we use an if statement for the entire change counter.*/
          if(change<100 && change >= 1){
              
             printf("%d cents: ", change);
             int quarters = change/25;

/*Calculate quarters using basic division, and use nested if statements
 * to output either plural or singular word for quarters.*/               
             if(change > 0){
              
                if(quarters > 1){
                   printf("%d quarters", quarters);
                } 
                else
                    if(quarters == 1){
                       printf("%d quarter", quarters);
                }
             }
          
/*Calculate change again through remainder function, and assign a different value so that
 * initial if statement condition is not changed.*/
             change1 = change%25;
             int dimes = change1/10;
             
/*Check if change is left to count and if the value is greater than
 *a single quarter, we output a comma.*/
             if(change1 != 0 && quarters != 0){
                printf(", ");
             }
          
/*Print dimes similar to before and calculate new change again.*/ 
             if(change1 > 0){
             
                if(dimes > 1){
                   printf("%d dimes", dimes);        
                }
                else
                    if(dimes == 1){
                       printf("%d dime", dimes);
                }
             }   
        
             change2 = change1%10;
             int nickels = change2/5;
     
/*Similar to before, we calculate change again, check if it is
 * more than a single dime, and print a comma if it is.*/
             if(change2 != 0 && dimes != 0){
                printf(", ");
             }      
 
/*Calculate nickels similar to before and again calculate change afterwards
 * to check for any leftover change in cents.*/   
             if(change2 > 0){
             
                if(nickels > 1){
                   printf("%d nickels", nickels);
                }
                else
                    if(nickels == 1){
                       printf("%d nickel", nickels);
                }
             }
              
             change3 = change2%5;
             int cents = change3;
          
/*Check if change before is more than a nickel, and if yes,
 * print a comma.*/
             if(change3 != 0 && nickels != 0){
                printf(", ");
             }

/*Finally calculate change in cents and print a period in the end.
 * Note - If there aren't any cents, then the previous change is ended
 * with a period in this final if statement for change.*/
             if(change3 > 0){
                
                if(cents > 1){
                   printf("%d cents.\n", cents);
                }
                else
                    if(cents == 1){
                       printf("%d cent.\n", cents);
                }
             }         
             else{
                printf(".\n");
             }
                
          }
     
    }

/*Print Goodbye after an invalid input.*/
    printf("Goodbye\n");
    
    return 0;
}  
    
   
