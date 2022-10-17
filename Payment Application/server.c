#include"server.h"
/*server-side accounts' database*/
ST_accountsDB_t server_side_acc_database[255] = { {100.0,"4358123514789654"},
	{400.0,"4358123511239654"},
	{2500.0,"4358123511237654"},
	{200.0,"4354723511239654"},
	{500.0,"4735455589652145"} };

/*server-side transactions' database*/
ST_transaction_t server_side_trans_database[255] = { 0 };

signed short Existed_account = -1;// will return index of the account if found

EN_transState_t recieveTransactionData(ST_transaction_t* transData){
	uint8_t found = 0; 
	//signed short Existed_account = -1;// will return index of the account if found
	for (uint8_t i=0;i<255;i++) {
		for (uint8_t j = 0; j < 16; j++) {
			if (transData->cardHolderData.primaryAccountNumber[j]==server_side_acc_database[i].primaryAccountNumber[j]){
				found++;
			}
		
		}
		if (found > 15) {
			Existed_account = i;
			break;
		}
		else {
			found = 0;
		}
	}
	if (Existed_account != -1) {
		if (transData->terminalData.transAmount > server_side_acc_database[Existed_account].balance) {
			transData->transState = DECLINED_INSUFFECIENT_FUND;
			return DECLINED_INSUFFECIENT_FUND;
		}
		else {//
			float Balance = server_side_acc_database[Existed_account].balance;
			server_side_acc_database[Existed_account].balance -= transData->terminalData.transAmount;
			if (server_side_acc_database[Existed_account].balance == Balance) {
				transData->transState = INTERNAL_SERVER_ERROR;
				return  INTERNAL_SERVER_ERROR;
			}
			else {
				transData->transState = APPROVED;
				return APPROVED;
			}
		}
	}
	else {
		transData->transState = DECLINED_STOLEN_CARD;
		return DECLINED_STOLEN_CARD;
	}

}

EN_serverError_t isValidAccount(ST_cardData_t* cardData){
	uint8_t found = 0;
	//signed short Existed_account = -1;// will return index of the account if found
	for (uint8_t i = 0; i < 255; i++) {
		for (uint8_t j = 0; j < 16; j++) {
			if (cardData->primaryAccountNumber[j]==server_side_acc_database[i].primaryAccountNumber[j]){
				found++;
			}
		}
		if (found > 15) {
			Existed_account = i;
			break;
		}
		else {
			found = 0;
		}
	}
	if (Existed_account != -1) {
		return OK;
	}
	else {
		return DECLINED_STOLEN_CARD;
	}
}


EN_serverError_t isAmountAvailable(ST_terminalData_t* termData){//ST_trminalData_t
	if (termData->transAmount > server_side_acc_database[Existed_account].balance) {
		return LOW_BALANCE;
	}
	else {
		return OK;
	}
}


EN_serverError_t saveTransaction(ST_transaction_t* transData){
	uint8_t Transaction_state = server_side_trans_database[Existed_account].transState;
	server_side_trans_database[Existed_account].cardHolderData = transData->cardHolderData;
	server_side_trans_database[Existed_account].terminalData = transData->terminalData;
	server_side_trans_database[Existed_account].transState = transData->transState;
	server_side_trans_database[Existed_account].transactionSequenceNumber +=1;
	if (server_side_trans_database[Existed_account].transState == Transaction_state) {
		return SAVING_FAILED;
	}
	else {
		return OK;
	}
}
/*
EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t* transData);
*/