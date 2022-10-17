#include"app.h"

void appStart(void) {
	ST_cardData_t CardHolder;
	ST_terminalData_t Terminal;
	ST_transaction_t Transaction;
	uint8_t a;
	do
		a = getCardHolderName(&CardHolder);
	while (a == WRONG_NAME);
	do
		a = getCardExpiryDate(&CardHolder);
	while (a== WRONG_EXP_DATE);
	do
		a = getCardPAN(&CardHolder);
	while (a == WRONG_PAN);
	a = isValidCardPAN(&CardHolder);
	if (a == INVALID_CARD) { return 0; }
	do
		a = setMaxAmount(&Terminal);
	while (a== INVALID_MAX_AMOUNT);
	do
		a = getTransactionDate(&Terminal);
	while (a== WRONG_DATE);
	a = isCardExpired(CardHolder,Terminal);
	if (a== EXPIRED_CARD){
		printf("EXPIRED CARD");
		return 0;
	}
	do
		a = getTransactionAmount(&Terminal);
	while (a== INVALID_AMOUNT);
	a = isBelowMaxAmount(&Terminal);
	if (a == EXCEED_MAX_AMOUNT) {
		printf("EXCEED MAX AMOUNT");
		return 0;
	}
	a = isValidAccount(&CardHolder);
	if (a== DECLINED_STOLEN_CARD){
		printf("DECLINED STOLEN CARD");
		return 0;
	}
	a = isAmountAvailable(&Terminal);
	if (a == LOW_BALANCE){
		printf("LOW BALANCE");
		return 0;
	}
	Transaction.cardHolderData = CardHolder;
	Transaction.terminalData = Terminal;
	do
		a = recieveTransactionData(&Transaction);
	while (a== INTERNAL_SERVER_ERROR);
	if (a == APPROVED) {
		printf("APPROVED");
	}
	a = saveTransaction(&Transaction);

}