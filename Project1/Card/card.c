//
// Created by mahmoud saleh on 11/8/2022.
//

#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#include "card.h"



typedef unsigned char uint8_t;

long long int pin = 0;

void reversec(char* str, int len)
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

void intToStrc(long long int x, char str[])
{
	int i = 0;
	while (x) 
	{
		str[i++] = (x % 10) + '0';
		x = x / 10;
	}
	reversev(str, i);
	str[i] = '\0';

}


EN_cardError_t getCardHolderName(ST_cardData_t* cardData) 
{
	fseek(stdin, 0, SEEK_END);
	   gets(cardData->cardHolderName);
		if ((NULL == (cardData->cardHolderName)) ||
			(20 > (strlen(cardData->cardHolderName))) ||
			(24 < (strlen(cardData->cardHolderName))))
			return WRONG_NAME;
		return CARD_OK;
}

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
	fseek(stdin, 0, SEEK_END);
	scanf("%s",cardData->cardExpirationDate);
	if ((NULL == cardData->cardExpirationDate) || 
		(5!=strlen(cardData->cardExpirationDate))|| 
		(cardData->cardExpirationDate[2]!='/'))
		    return WRONG_EXP_DATE;

	
	return CARD_OK;
	
}

EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{    
	fseek(stdin, 0, SEEK_END);
	  scanf("%lld",&cardData->PAN);
	  char arr[20]={'0'};
	  intToStrc(cardData->PAN,arr,20);
	 // printf("pin :%lld\n", cardData->PAN);
	  memcpy(cardData->primaryAccountNumber, arr, 20);
	 // printf("card:%s\n", cardData->primaryAccountNumber);
	  if ( (NULL == cardData->primaryAccountNumber) ||
		  (19 < strlen(cardData->primaryAccountNumber)) || 
		  (16 >strlen(cardData->primaryAccountNumber) ) )
		return WRONG_PAN;


	  return CARD_OK;
}
/***************************************************************/
EN_cardError_t getDataCard(ST_cardData_t* cardData)
{
	//printf("card in:%s\n", cardData->primaryAccountNumber);
	FILE* file = NULL;
	uint8_t pandb[20] = { '0' };
    file = fopen("Accounts DB.txt", "r");
	if (NULL != file)
	{
		char arr[81];
		for (int i = 0; i < 12; i++)
		{
			fgets(arr, 80, file);
			memcpy(pandb, (arr + 35), 19);
			removeSpacesFromStr(pandb);
			if (!(memcmp(cardData->primaryAccountNumber, pandb, strlen(cardData->primaryAccountNumber))))
			{
				memcpy(cardData->cardHolderName, (arr + 5), 23);
				memcpy(cardData->cardExpirationDate, (arr + 60), 5);
				fclose(file);
				printf("welcome, %s\n",cardData->cardHolderName);
				return CARD_OK;
			}
		}
		return WRONG_DATA;
	}
	else
		printf("can't read card");
} 

void getDataCardTest()
{
	uint8_t ActualResult, ExpectedResult;

	ActualResult = getDataCard(&TestC);

	printf("Expected Result:");
	fseek(stdin, 0, SEEK_END);
	scanf("\n%c", &ExpectedResult);

	printf("Actual Result  :%d\n", ActualResult);

}
/**********mahmoud mohammed saleh*******************/


void getCardHolderNameTest(void) 
{
	uint8_t ActualResult, ExpectedResult;
		printf("please enter your NAME:");
		ActualResult = getCardHolderName(&TestC);
		printf("Expected Result : ");scanf(" % c", &ExpectedResult);
		printf("Actual Result  :%d\n", ActualResult);
}

void getCardExpiryDateTest(void)
{
	
	uint8_t ActualResult, Expectedresult;
	printf("please enter your ExpiryDate:");

	ActualResult = getCardExpiryDate(&TestC);

	printf("Expected Result:");scanf("\n%c", &Expectedresult);

	printf("Actual Result  :%d\n", ActualResult);
	
	
}

void getCardPANTest(void)
{
	
	uint8_t ActualResult, ExpectedResult;
	printf("please enter your PAN:");
	ActualResult = getCardPAN(&TestC);
	printf("Expected Result:");scanf("\n%c", &ExpectedResult);
	printf("Actual Result  :%d\n", ActualResult);
	

}
