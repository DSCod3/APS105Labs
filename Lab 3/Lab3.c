/********************************************************
 **     Definition: This is my Lab 3 code in C         **                                         
 **     Author: Dhruv Sharma                           **
 **     Student Number: 1006926631                     **
 **     Date of Submission: Monday, January 25th, 2021 ** 
 **     IDE used: Codelite                             **
 *******************************************************/ 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv)
{
    if(argc==1)
    srand(time(NULL));
         else
    srand(atoi(argv[1]));
     
    int dealerFirstCard = rand() % 13 + 1;
    int playerFirstCard = rand() % 13 + 1;
    int hitStay;
    int playerSum = 0, dealerSum = 0;
   
/*First we assign a random card to the player and dealer using rand.*/ 
    printf("First Cards: player %d, dealer %d\n", playerFirstCard, dealerFirstCard);
    
/*Using an if statement, we ensure the first cards with a face value above 10 are worth 10.*/
    if (playerFirstCard >= 10)
        playerFirstCard = 10;
        
    if (dealerFirstCard >= 10)
        dealerFirstCard = 10;
        
        playerSum = playerSum + playerFirstCard;
        dealerSum = dealerSum + dealerFirstCard;
        

/*We use a while loop, if statements, and Logical AND to assign the player and
 * dealer cards until the respective win conditions are satisfied.*/
    while( playerSum <= 21 && dealerSum < 17)
    {   
        printf("Type 1 for Hit, 0 to Stay:");
        scanf("%d", &hitStay);
    
/*If player hits, the cards first display face value,then cards above 
 * 10 are assigned a value of 10, and finally the cards are added.*/
        if(hitStay == 1){
            int playerCard= rand() % 13 + 1;
            
            printf("Player gets a %d, worth is ", playerCard);
            
            if (playerCard > 10)
                playerCard = 10;
                
            playerSum= playerSum + playerCard;
            printf("%d\n", playerSum);
        }
        
/*After player stays, the dealer receives cards constantly in 
 * a nested while loop until he/she goes over 17.*/
        else
        if(hitStay == 0){
           printf("Dealer gets: ");
            
           while(dealerSum < 17){
           int dealerCard= rand() % 13 + 1;

           printf("%d ", dealerCard);
           
           if (dealerCard > 10)
               dealerCard = 10;  
           dealerSum = dealerSum + dealerCard;
             }
        }
        
     }
    
/*Using if...else statements, we output all possible outcomes
 * based on the random cards the player/dealer receive and their decisions.*/

    if(playerSum > 21){
            printf("Player over 21, Dealer wins\n");
        }
  
    else   
        if(dealerSum >21){
            printf("\nDealer over 21, Player wins\n");
        }    
    
    else
        if(dealerSum == playerSum){
            printf("\nTie!\n");
        }
    
    else
        if(playerSum <= 21 && dealerSum <= 21 && playerSum > dealerSum){
            printf("\nPlayer better than Dealer, Player wins\n");
        }
    else
        if(playerSum <= 21 && dealerSum <= 21 && dealerSum > playerSum){
            printf("\nDealer better than Player, Dealer wins\n");
        }
    
    
    return 0;
    
    
}