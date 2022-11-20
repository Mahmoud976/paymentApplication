//
// Created by mahmo on 11/8/2022.
//

#ifndef PROJECT_TERMINAL_H
#define PROJECT_TERMINAL_H

#include "../Card/card.h"

typedef unsigned char uint8_t;

typedef struct 
{
    float transAmount;
    float maxTransAmount;
    uint8_t transactionDate[11];
}ST_terminalData_t;

ST_terminalData_t TestT;
typedef enum 
{
    TERMINAL_OK, WRONG_DATE, EXPIRED_CARD, INVALID_CARD, INVALID_AMOUNT, EXCEED_MAX_AMOUNT, INVALID_MAX_AMOUNT
}EN_terminalError_t;

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData);

EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData);

EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData);

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData);

EN_terminalError_t setMaxAmount(ST_terminalData_t* termData, float maxAmount);

EN_terminalError_t isValidCardPAN(ST_cardData_t* cardData); // Optional

void getTransactionDateTest(void);

void isCardExpriedTest(void);

void getTransactionAmountTest(void);

void isBelowMaxAmountTest(void);

void setMaxAmountTest(void);

void isValidCardPANTest(void);// Optional

void cvtpin(char arr[], long long int* num);

#endif //PROJECT_TERMINAL_H
