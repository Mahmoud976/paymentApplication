//
// Created by mahmoud saleh on 11/8/2022.
//

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include<string.h>
#include "terminal.h"
#include<time.h>
#include <limits.h>
#include"../Card/card.h"



uint8_t FinalDate[10];

int month=0,year=0;

void reversev(char* str, int len)
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

void intToStrv(int x, char str[], int d)
{
    int i = 0;
    while (x) {
        str[i++] = (x % 10) + '0';
        x = x / 10;
    }

    while (i < d)
        str[i++] = '0';

    reversev(str, i);
    str[i] = '\0';
  
}

long long int ConvertCharToLong64(char* pSrc) {
    int i = 1;
    long result = (int)pSrc[0] - '0';
    while (i < strlen(pSrc)) {
        result = result * 10 + ((int)pSrc[i] - '0');
        ++i;
    }
    return result;
}

void cvtpin(char arr[], long long int* num)
{
    long long int temp = atoll((arr));
    *num = temp;
    temp= atoll((arr+10));
    *num += temp;
    printf("%lld", *num);
}

void myMemCpy(void* finaldate, void* date, int n)
{
    char* src = (char*)date;
    char* dest = (char*)finaldate;
    int j = 0;
    for (int i = 0; i < n; i++) {
        if ((2 == j) || (5 == j)) { dest[j] = '/';j++;}
        dest[j] = src[i];
        j++;
    }
}

void get_time() {
    int* ptr = &month;
    time_t t;
    t = time(NULL);
    struct tm tm = *localtime(&t);
    *ptr= (tm.tm_mon + 1);
    year= (tm.tm_year-100);
    long tt = (tm.tm_mday * 1000000)+ ((tm.tm_mon + 1) * 10000)+ (tm.tm_year + 1900);
    uint8_t date[9];
     intToStrv(tt, date, 8);
    myMemCpy(FinalDate, date, 10);

}

/*************************************************************************************************************/
EN_terminalError_t getTransactionDate(ST_terminalData_t* termData) 
{   
    get_time();
    memcpy(termData->transactionDate, FinalDate, 11);

    //printf("get date from OS : %s\n", termData->transactionDate);

    return TERMINAL_OK;
}


EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData)
{
  //  printf("we will get data from card and and memcmp with system date!!! \n");
    char arr[6];
    memcpy(arr, cardData->cardExpirationDate, 6);
   // printf("arr:%s\n",arr);
    int x = atoi(arr);

    arr[0] = '0';arr[1] = '0';arr[2] = '0';

    int y= atoi(arr);
    
    if(year<y){ return TERMINAL_OK; }

    else if(year==y&&x>month){ return TERMINAL_OK; }

    return EXPIRED_CARD;
}


EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData) 
{
    fseek(stdin, 0, SEEK_END);
    scanf("%f",&termData->transAmount);
    
    if ((termData->transAmount)<=0)  return INVALID_AMOUNT;
    return TERMINAL_OK;
}


EN_terminalError_t setMaxAmount(ST_terminalData_t* termData, float maxAmount) 
{
    termData->maxTransAmount = maxAmount;
   if((termData->maxTransAmount)<=0)return INVALID_MAX_AMOUNT;
   return TERMINAL_OK;
}


EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{
    //printf("is the Amount < MaxAmount\n");
   if(termData->maxTransAmount < termData->transAmount) return EXCEED_MAX_AMOUNT;
   return TERMINAL_OK;
}


EN_terminalError_t isValidCardPAN(ST_cardData_t* cardData)  
{
    long long int pin = cardData->PAN;
    int first_multiply = 0;
    int second_summ = 0;
    int final_summ = 0;

    if ((pin < (long long)100000000000 && !(pin > LLONG_MAX)))
        return INVALID_CARD;


    int n[10]; for (int i = 0; i < 10; i++) n[i] = 0;

    n[1] = (pin % 100) / 10;
    n[2] = (pin % 10000) / 1000;
    n[3] = (pin % 1000000) / 100000;
    n[4] = (pin % 100000000) / 10000000;
    n[5] = (pin % 10000000000) / 1000000000;
    n[6] = (pin % 1000000000000) / 100000000000;
    n[7] = (pin % 100000000000000) / 10000000000000;
    n[8] = (pin % 10000000000000000) / 1000000000000000;


    int d[10]; for (int i = 0; i < 10; i++) d[i] = 0;

    d[1] = (n[1] * 2);
    d[2] = (n[2] * 2);
    d[3] = (n[3] * 2);
    d[4] = (n[4] * 2);
    d[5] = (n[5] * 2);
    d[6] = (n[6] * 2);
    d[7] = (n[7] * 2);
    d[8] = (n[8] * 2);

    int m[10]; for (int i = 0; i < 10; i++) m[i] = 0;

    for (int i = 1; i < 9; i++)
    {
        if (d[i] > 10)
            m[i] = (d[i] % 10) + 1;
        else if (d[i] == 10)
            m[i] = 1;
        else
            m[i] = d[i];
    }


    first_multiply = m[1] + m[2] + m[3] + m[4] + m[5] + m[6] + m[7] + m[8];


    int x[10]; for (int i = 0; i < 10; i++) x[i] = 0;

    x[1] = (pin % 10);
    x[2] = (pin % 1000) / 100;
    x[3] = (pin % 100000) / 10000;
    x[4] = (pin % 10000000) / 1000000;
    x[5] = (pin % 1000000000) / 100000000;
    x[6] = (pin % 100000000000) / 10000000000;
    x[7] = (pin % 10000000000000) / 1000000000000;
    x[8] = (pin % 1000000000000000) / 100000000000000;


    second_summ = x[1] + x[2] + x[3] + x[4] + x[5] + x[6] + x[7] + x[8];
    final_summ = first_multiply + second_summ;

    if (final_summ % 10 == 0)
    {
        if (pin < (long long)10000000000000)
        {
            printf("VISA\n");
            return TERMINAL_OK;
        }

        else if (pin < (long long)1000000000000000)
        {
            printf("AMEX\n");
            return TERMINAL_OK;
        }

        else if (pin < (long long)10000000000000000)
        {
            if (n[8] == 4)
            {
                printf("VISA\n");
                return TERMINAL_OK;
            }
            else
            {
                printf("MCARD\n");
            return TERMINAL_OK;
             }

        }
    }
    else
        return INVALID_CARD;
    
    
} // Optional

/************************************************************************************************************/


void getTransactionDateTest(void) 
{
    uint8_t ActualResult, ExpectedResult;
    printf("We will always get the right date because it from OS!!\n");

    ActualResult = getTransactionDate(&TestT);

    printf("Expected Result:");
    fseek(stdin, 0, SEEK_END);
    scanf("%c", &ExpectedResult);
    printf("Actual Result  :%d\n", ActualResult);

}


void isCardExpriedTest(void)
{
    uint8_t ActualResult, Expectedresult;

    ActualResult= isCardExpired(&TestC, &TestT);

    printf("Expected Result:");
    fseek(stdin, 0, SEEK_END);
    scanf("\n%c", &Expectedresult);

    printf("Actual Result:%d\n", ActualResult);

}


void getTransactionAmountTest(void)
{
    uint8_t ActualResult, Expectedresult;
    printf("please enter amount of money:");
    ActualResult = getTransactionAmount(&TestT);
    printf("Expected Result:");
    fseek(stdin, 0, SEEK_END);
    scanf("\n%c", &Expectedresult);

    printf("Actual Result  :%d\n", ActualResult);
}


void setMaxAmountTest(void)
{
    float maxm;
    uint8_t ActualResult, Expectedresult;
    printf("please enter Max amount of money:");
    fseek(stdin, 0, SEEK_END);
    scanf("%f", &maxm);
    ActualResult = setMaxAmount(&TestT,maxm);

    printf("Expected Result:");
    fseek(stdin, 0, SEEK_END);
    scanf("\n%c", &Expectedresult);

    printf("Actual Result  :%d\n", ActualResult);


}


void isBelowMaxAmountTest(void) 
{
    
    uint8_t ActualResult, Expectedresult;
    ActualResult = isBelowMaxAmount(&TestT);
    printf("Expected Result:");
    fseek(stdin, 0, SEEK_END);
    scanf("\n%c", &Expectedresult);
    printf("Actual Result  :%d\n", ActualResult);

}


void isValidCardPANTest(void)
{
    uint8_t ActualResult, Expectedresult;
    ActualResult = isValidCardPAN(&TestC);
    printf("Expected Result:");
    fseek(stdin, 0, SEEK_END);
    scanf("\n%c", &Expectedresult);
    printf("Actual Result  :%d\n", ActualResult);


} // Optional 


