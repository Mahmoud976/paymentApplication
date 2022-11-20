//
// Created by mahmoud saleh on 11/8/2022.
//

#ifndef PROJECT_SERVER_H
#define PROJECT_SERVER_H

#include "../Card/card.h"
#include "../Terminal/terminal.h" 

typedef unsigned int uint32_t;

typedef enum 
{
    APPROVED, DECLINED_INSUFFECIENT_FUND, DECLINED_STOLEN_CARD, FRAUD_CARD, INTERNAL_SERVER_ERROR
}EN_transState_t;

typedef struct 
{
    ST_cardData_t cardHolderData;
    ST_terminalData_t terminalData;
    EN_transState_t transState;
    uint32_t transactionSequenceNumber;
}ST_transaction_t;

ST_transaction_t TestS;




typedef enum EN_serverError_t
{
    SERVER_OK, SAVING_FAILED, TRANSACTION_NOT_FOUND, ACCOUNT_NOT_FOUND, LOW_BALANCE, BLOCKED_ACCOUNT
}EN_serverError_t;

typedef enum EN_accountState_t
{
    RUNNING,
    BLOCKED
}EN_accountState_t;

typedef struct ST_accountsDB_t
{
    float balance;
    EN_accountState_t state;
    uint8_t primaryAccountNumber[20];
}ST_accountsDB_t;

ST_accountsDB_t  TestDB;

EN_transState_t recieveTransactionData(ST_transaction_t* transData);

EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountRefrence);

EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence);

EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_accountsDB_t* accountRefrence);

EN_serverError_t saveTransaction(ST_transaction_t* transData);

void listSavedTransactions(void);

void recieveTransactionDataTest(void);

void isValidAccountTest(void);

void isBlockedAccountTest(void);

void isAmountAvailableTest(void);

void saveTransactionTest(void);

void listSavedTransactionsTest(void);





void setTransactionSequenceNumber(void);
#endif //PROJECT_SERVER_H
