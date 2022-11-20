//
// Created by mahmoud saleh on 11/8/2022.
//

#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<string.h>
#include<math.h>
#include"server.h"
#include"../Card/card.h"
#include"../Terminal/terminal.h"


uint8_t nameC[24]={'0'};
uint8_t panC[20]={'0'};
uint8_t  exC[6]={'0'};

char state[7]={'0'};

FILE* file = NULL;
FILE* file1 = NULL;

void reverse(char* str, int len)
{
    int i = 0, j = len - 1, temp;
    while (i < j) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
}
void intToStr(int x, char str[], int d)
{
    int i = 0;
    while (x) {
        str[i++] = (x % 10) + '0';
        x = x / 10;
    }

    reverse(str, i);
    str[i] = '\0';
     
}
char* removeSpacesFromStr(char* string)
{
    int non_space_count = 0;
    for (int i = 0; string[i] != '\0'; i++)
    {
        if (string[i] != ' ')
        {
            string[non_space_count] = string[i];
            non_space_count++;
        }
    }
    string[non_space_count] = '\0';
    return string;
}
int searchInCard(char ptr[], char n)
{
    file = fopen("Accounts DB.txt", "r");
    if (NULL != file)
    {
       // printf("i can read card\n");
        char arr[81];
        if (n == 'n')
        {
            for (int i = 0; i < 12; i++)
            {
                fgets(arr, 80, file);
                memcpy(nameC, (arr + 5), 23);
                removeSpacesFromStr(nameC);
                removeSpacesFromStr(ptr);
                if (!(memcmp(ptr, nameC, strlen(ptr))))
                {
                    fclose(file);
                    return 1;
                 }
            }
            fclose(file);
            return 0;
        }
        else if (n == 'p')
        {
            for (int i = 0; i < 12; i++)
            {
                fgets(arr, 80, file);
                memcpy(panC, (arr + 35), 19);
                removeSpacesFromStr(panC);
                if (!(memcmp(ptr, panC,strlen(ptr)) ))
                {
                   
                    fclose(file);
                    return 1;
                }
            }
            return 0;
        }
        else if (n == 'e')
        {
            for (int i = 0; i < 12; i++)
            {
                fgets(arr, 80, file);
                memcpy(exC, (arr + 60), 5);
                removeSpacesFromStr(exC);
                removeSpacesFromStr(ptr);
                if (!(memcmp(ptr,exC, strlen(ptr))))
                {   fclose(file);
                    return 1;
                }
            }
            return 0;
        }        
        else
        {                    
            fclose(file);
            printf("error value of n");
        }
    }
    else 
        printf("rerror in file");
    
}
int searchInTransaction(char ptr[], float amaount, char n)
{
    char arr[81]={'0'};float  balance = 0;
    file = fopen("Transactions DB.txt", "r");
    if (NULL != file)
    {
       // printf("i can read\n");
        
        for (int i = 0; i < 12; i++)
        {
            fgets(arr, 80, file);
            memcpy(panC, (arr +22), 19);
            removeSpacesFromStr(panC);
            if (!(memcmp(ptr, panC, strlen(ptr))))
            {
               fclose(file);

                if (n == 'p')
                {
                    char rr[11]={'0'};
                    memcpy(rr, arr, 10);
                    removeSpacesFromStr(rr);
                    balance = atoi(rr);
                    if (balance > amaount)
                    {
                        fclose(file);
                        return 1;
                    }
                    return 0;
                }
                else if (n == 's')
                {   memcpy(state, (arr + 11), 10);
                    removeSpacesFromStr(state);
                    if (!(memcmp(state , "RUNNING",7)))
                        return 1;
                    return 0;
                }
                
            }
        }
        fclose(file);
    }
   // printf("can't found this user");
}
void update_balance(char ptr[], float amaount)
{
    char arr[81] = { '0' };float  balance = 0;
    file = fopen("Transactions DB.txt", "r"); 
    file1 = fopen("Transactions DB1.txt", "w");

    if (NULL != file)
    {
       // printf("i can read\n");

        for (int i = 0; i < 12; i++)
        {
            fgets(arr, 80, file);
            memcpy(panC, (arr + 22), 19);
            removeSpacesFromStr(panC);
            if (!(memcmp(ptr, panC, strlen(ptr))))
            {
                    char rr[11] = { '0' };
                    memcpy(rr, arr, 10);
                    removeSpacesFromStr(rr);
                    balance = atoi(rr);
                    balance -= amaount;
                    int balan = (int)balance;
                    char z[80]={'\0'};
                    intToStr(balan, z, 9);
                  //  printf("z:%s", z);
                    memset(arr, ' ', 9);
                    strcat(z, (arr + strlen(z)));
         
                   // printf("arr: %s\n",z);
                    fprintf(file1,z);
            }
            else fprintf(file1,arr);
        }
        fclose(file);
        fclose(file1);
    }
    fclose(file);
  //  printf("can't found this user");
}
int rem()
{
    if (remove("Transactions DB.txt") == 0) {
        //  printf("Deleted successfully");
        return 1;
    }
    else {
        
        printf("Unable to delete the file");
        return 0;
    }
}
int ren()
{
    char old_name[] = "Transactions DB1.txt";
    char new_name[] = "Transactions DB.txt";
    int value;
    value = rename(old_name, new_name);
    if (!value){ 
    // printf("%s", "File name changed successfully");
    return 1;
}
    else {
        // printf("Error");
        return 0;
    }
}


EN_serverError_t isValidAccount(ST_cardData_t* cardData,ST_accountsDB_t* accountRefrence)
{
    //printf("fetch primaryAccountNumber in card database\n");
    int ret= searchInCard(cardData->primaryAccountNumber, 'p');
    if (ret)return SERVER_OK;

        return ACCOUNT_NOT_FOUND;
}
EN_serverError_t isBlockedAccount(ST_terminalData_t* termData, ST_cardData_t* cardData)
{
    //printf("is blooked\n");
    int ret = searchInTransaction(cardData->primaryAccountNumber,
        termData->transAmount, 's');

    if (ret) return SERVER_OK;
    //printf("this card blooked\n");
    //exit(1);
    return BLOCKED_ACCOUNT;
}
EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_cardData_t* cardData)
{
   
   // printf("is amount < balance \n");
    int ret = searchInTransaction(cardData->primaryAccountNumber,
        termData->transAmount, 'p');

    if (ret) return SERVER_OK;
    return LOW_BALANCE;
}
EN_serverError_t saveTransaction(ST_transaction_t* transData)
{
    

    //card
    memcpy(transData->cardHolderData.cardHolderName, TestC.cardHolderName, 24);
    memcpy(transData->cardHolderData.primaryAccountNumber, TestC.primaryAccountNumber, 19);
    memcpy(transData->cardHolderData.cardExpirationDate, TestC.cardExpirationDate, 5);

    //terminal
    transData->terminalData.maxTransAmount = TestT.maxTransAmount;
    memcpy(transData->terminalData.transactionDate, TestT.transactionDate, 10);
    transData->terminalData.transAmount = TestT.transAmount;
    //server
    char stat[8] = { '0' };
    int ret = isBlockedAccount(&TestT, &TestC);
    if (ret == 5)
    {
        transData->transState = DECLINED_STOLEN_CARD;  
    }
    else
        
    
    transData->transactionSequenceNumber++;
    return SERVER_OK;
}
EN_transState_t recieveTransactionData(ST_transaction_t* transData)
{
    //printf("recieveTransactionData\n");

    memcpy(transData->cardHolderData.cardHolderName, TestC.cardHolderName, 24);
    memcpy(transData->cardHolderData.cardExpirationDate, TestC.cardExpirationDate, 6);
    memcpy(transData->cardHolderData.primaryAccountNumber, TestC.primaryAccountNumber, 20);

    transData->terminalData.transAmount = TestT.transAmount;

    int ret = searchInCard(transData->cardHolderData.cardHolderName, 'n');

    if (!ret) {// printf(" name cant found\n");
        return FRAUD_CARD;
    }

    transData->terminalData.transAmount = TestT.transAmount;
    transData->terminalData.maxTransAmount = TestT.maxTransAmount;

    if (transData->terminalData.transAmount > transData->terminalData.maxTransAmount) {
        printf("money not enof\n");
        return DECLINED_INSUFFECIENT_FUND;
    }


    if ((isBlockedAccount(&TestT, &TestC)) == BLOCKED_ACCOUNT) {
        printf("blooked number\n");
        return DECLINED_STOLEN_CARD;
    }

    if (saveTransaction(&TestS) != SERVER_OK) {
        // printf("can't save\n");
        return INTERNAL_SERVER_ERROR;
    }

    update_balance(transData->cardHolderData.primaryAccountNumber, TestT.transAmount);
    if (!rem())
    {printf("can't save this transaction\n");
    exit(1);
     }
    
    if (!ren())
    {
        printf("can't save this transaction\n");
        exit(1);
    }

    printf("done\n");
    return APPROVED;
}

void setTransactionSequenceNumber() {
    TestS.transactionSequenceNumber = 0;
}
void isValidAccountTest(void) 
{
    uint8_t ActualResult, Expectedresult;
    ActualResult  = isValidAccount(&TestC,&TestDB);
    printf("Expected Result:");scanf("\n%c", &Expectedresult);
    printf("Actual Result  :%d\n", ActualResult);

}
void recieveTransactionDataTest(void) 
{
    uint8_t ActualResult, Expectedresult;
    printf("please enter your recieveTransaction:");
    ActualResult= recieveTransactionData(&TestS);
    printf("Expected Result:");scanf("\n%c", &Expectedresult);
    printf("Actual Result  :%d\n", ActualResult);
}
void isBlockedAccountTest(void) 
{
    uint8_t ActualResult, Expectedresult;
    ActualResult = isBlockedAccount(&TestT, &TestC);
    printf("Expected Result:");
    
    scanf("\n%c", &Expectedresult);
    printf("Actual Result  :%d\n", ActualResult);

}
void isAmountAvailableTest(void) 
{
    uint8_t ActualResult, Expectedresult;
    ActualResult = isAmountAvailable(&TestT,&TestC);
    printf("Expected Result:");scanf("\n%c", &Expectedresult);
    printf("Actual Result  :%d\n", ActualResult);
}
void saveTransactionTest(void) 
{
    
    uint8_t ActualResult, Expectedresult;
    ActualResult = saveTransaction(&TestS);
    printf("Expected Result:");scanf("\n%c", &Expectedresult);
    printf("Actual Result  :%d\n", ActualResult);
}
void listSavedTransactionsTest(void) 
{
    char stat[8] = "RUNNING";
    if (TestS.transState ==2)
    {
        memcpy(stat, "BLOCKED",7);
    }
    printf("\n################################\n");
    printf("Transaction Sequence : %i\n", TestS.transactionSequenceNumber );
    printf("Transaction Date     : %s\n", TestS.terminalData.transactionDate);
    printf("Transaction Amount   : %f\n", TestT.transAmount);
    printf("Transaction State    : %s\n", stat);
    printf("Terminal Max Amount  : %f\n", TestS.terminalData.maxTransAmount);
    printf("Cardholder Name      : %s\n", TestS.cardHolderData.cardHolderName);
    printf("PAN                  : %s\n", TestS.cardHolderData.primaryAccountNumber);
    printf("Card Expiration Date : %s\n", TestS.cardHolderData.cardExpirationDate);
    printf("#################################\n");
    

}

