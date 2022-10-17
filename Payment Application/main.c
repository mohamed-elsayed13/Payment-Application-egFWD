#include "app.h"
extern ST_transaction_t server_side_trans_database[255];
extern ST_accountsDB_t server_side_acc_database[255];
extern signed short Existed_account;
int main(){
	appStart();
	printf("%s\n", server_side_trans_database[Existed_account].cardHolderData.cardHolderName);
	printf("%s\n", server_side_trans_database[Existed_account].cardHolderData.primaryAccountNumber);
	printf("%s\n", server_side_trans_database[Existed_account].cardHolderData.cardExpirationDate);
	printf("%f\n", server_side_trans_database[Existed_account].terminalData.maxTransAmount);
	printf("%f\n", server_side_trans_database[Existed_account].terminalData.transAmount);
	printf("%s\n", server_side_trans_database[Existed_account].terminalData.transactionDate);
	printf("%d\n", server_side_trans_database[Existed_account].transState);
	printf("%d\n", server_side_trans_database[Existed_account].transactionSequenceNumber);
	printf("Your Balance now is %f",server_side_acc_database[Existed_account].balance);
	return 0;
}