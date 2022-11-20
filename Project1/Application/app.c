//
// Created by mahmo on 11/8/2022.
//
//#include <stdio.h>
#include "app.h"

void appStart(void) {
    //printf("enter your name :");
    //getCardHolderName(&TestC);
    //printf("enter your expierd date:");
    //getCardExpiryDate(&TestC);

    printf("enter your PAN :");
    getCardPAN(&TestC);
    getDataCard(&TestC); //this functin take pan num and say hi,your name from DB or cant found;
    //terminal
    setMaxAmount(&TestT, 6000);
    getTransactionDate(&TestT);
    if (isCardExpired(&TestC, &TestT) == EXPIRED_CARD) { printf("the card is expaird\n");exit(1);};
    printf("How much money do you want ?\n");
    getTransactionAmount(&TestT);
    if(isBelowMaxAmount(&TestT)== EXCEED_MAX_AMOUNT){ printf("You have exceeded the maximum limit\n");exit(1); };
    

    //sever
   if( isValidAccount(&TestC,&TestDB)== ACCOUNT_NOT_FOUND){ printf("the Account not found\n");exit(1); };
    if(isBlockedAccount(&TestT, &TestC)== BLOCKED_ACCOUNT){ printf("the Account is blooked\n");exit(1); };
    if(isAmountAvailable(&TestT ,&TestC)== LOW_BALANCE){printf("Your balance is not enough\n");exit(1);};
    saveTransaction(&TestS);
    recieveTransactionData(&TestS);
}