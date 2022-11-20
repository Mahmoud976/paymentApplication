//
// Created by mahmoud saleh on 11/8/2022.
//

#ifndef CARD_H
#define CARD_H


typedef unsigned char uint8_t;


 
typedef struct
{
    uint8_t cardHolderName[25];
    char primaryAccountNumber[20];
    uint8_t cardExpirationDate[6];
    long long int PAN;
}ST_cardData_t;

ST_cardData_t TestC;

typedef enum 
{
    CARD_OK, WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN, WRONG_DATA
}EN_cardError_t;


EN_cardError_t getCardHolderName(ST_cardData_t* cardData);

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData);

EN_cardError_t getCardPAN(ST_cardData_t* cardData);

long long int getPin();

void getCardHolderNameTest(void);

void getCardExpiryDateTest(void);

void getCardPANTest(void);


#endif //CARD_H
