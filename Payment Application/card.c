#include"card.h"

EN_cardError_t getCardHolderName(ST_cardData_t* cardData) {
	uint8_t Named_holder_length = 0;
	printf("Enter Card Holder Name : ");
	fgets(cardData->cardHolderName,sizeof(cardData->cardHolderName), stdin);
	for (uint8_t i=0; cardData->cardHolderName[i]!='\0'; i++) {
		Named_holder_length++;
	}
	if (Named_holder_length < 20 || Named_holder_length >24) {
		return WRONG_NAME;
	}
	else {
		return OK;
	}
}

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData) {
	uint8_t Expiry_date_length = 0,Number_flag=0;
	printf("Enter Expiry Date : ");
	fgets(cardData->cardExpirationDate, sizeof(cardData->cardExpirationDate), stdin);
	for (uint8_t i = 0; cardData->cardExpirationDate[i] != '\0'; i++) {
		Expiry_date_length++;
		if (cardData->cardExpirationDate[i]<'/'|| cardData->cardExpirationDate[i] > '9') {
			Number_flag++;
		}
	}
	if (Expiry_date_length < 5 || Expiry_date_length >5) {
		return WRONG_EXP_DATE;
	}
	else if(cardData->cardExpirationDate[2] != '/' || Number_flag!=0) {
		return WRONG_EXP_DATE;
	}
	else {
		return OK;
	}
}

EN_cardError_t getCardPAN(ST_cardData_t* cardData) {
	uint8_t PAN_length = 0, Number_flag = 0;
	printf("Enter Primary Account Number : ");
	fgets(cardData->primaryAccountNumber, sizeof(cardData->primaryAccountNumber), stdin);
	for (uint8_t i = 0; cardData->primaryAccountNumber[i] != '\0'; i++) {
		PAN_length++;
		if ((cardData->primaryAccountNumber[i] < '0') || (cardData->primaryAccountNumber[i] > '9')) {
			Number_flag++;
		}
	}
	if (PAN_length < 16 || PAN_length >19 || Number_flag > 1) {
		return WRONG_PAN;
	}
	else {
		return OK;
	}
}
