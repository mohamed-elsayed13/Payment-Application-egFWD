#include"terminal.h"

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData) {
	uint8_t Date_length = 0,Number_flag=0;
	printf("Enter Transaction Date : ");
	fgets(termData->transactionDate, sizeof(termData->transactionDate), stdin);
	for (uint8_t i = 0; termData->transactionDate[i] != '\0'; i++) {
		Date_length++;
		if (termData->transactionDate[i] < '/' || termData->transactionDate[i] > '9') {
			Number_flag++;
		}
	}
	if (Date_length < 10 || Date_length >10 ||Number_flag!=0) {
		return WRONG_DATE;
	}
	else if (termData->transactionDate[2] != '/' || termData->transactionDate[5] != '/') {
		return WRONG_DATE;
	}
	else {
		return OK;
	}
}

EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData) {
	uint8_t expiry_year = (cardData.cardExpirationDate[3]-48)   * 10 + cardData.cardExpirationDate[4]-48;
	uint8_t expiry_month = (cardData.cardExpirationDate[0] - 48) * 10 + cardData.cardExpirationDate[1] - 48;
	uint8_t transaction_year = (termData.transactionDate[8] - 48) * 10 + termData.transactionDate[9] - 48;
	uint8_t transaction_month = (termData.transactionDate[3] - 48) * 10 + termData.transactionDate[4] - 48;
	if (transaction_year < expiry_year) {
		return OK;
	}
	else if (transaction_year == expiry_year) {
		if (transaction_month <= expiry_month){
			return OK;
		}
		else {
			return EXPIRED_CARD;
		}
		}
	else {
		return EXPIRED_CARD;
	}
}

EN_terminalError_t isValidCardPAN(ST_cardData_t* cardData) {
	uint8_t PAN_length = 0, Number_flag = 0;
	for (uint8_t i = 0; cardData->primaryAccountNumber[i] != '\0'; i++) {
		PAN_length++;
		if ((cardData->primaryAccountNumber[i] < '0') || (cardData->primaryAccountNumber[i] > '9')) {
			Number_flag++;
		}
	}
	if (PAN_length < 16 || PAN_length >19 || Number_flag > 1) {
		return INVALID_CARD;
	}
	else {
		return OK;
	}
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData){
	printf("Enter Transaction Amount : ");
	scanf_s("%f",&termData->transAmount);
	if (termData->transAmount <= 0) {
		return INVALID_AMOUNT;
	}
	else {
		return OK;
	}


}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData){
	if (termData->transAmount <= termData->maxTransAmount){
		return OK;
	}
	else {
		return  EXCEED_MAX_AMOUNT;
	}
}

EN_terminalError_t setMaxAmount(ST_terminalData_t* termData){
	printf("Set Max Transaction Amount : ");
	scanf_s("%f", &termData->maxTransAmount);
	if (termData->maxTransAmount <= 0) {
		return INVALID_MAX_AMOUNT;
	}
	else {
		return OK;
	}

}
