#include <stdio.h>
#include <stdlib.h>

// Global Variables
int PIN = 1111, authenticationAttempts = 3, authenticated = 0, balance = 10000;
int *pAuthenticated = &authenticated;

// My Own Functions
void clear() {
	system("clear || cls");
}

// Authentication Functions
int verifyPin(int *pAuthenticated, int pin) {
		
	if(pin == PIN) {
		clear();
		*pAuthenticated = 1;
		return 1;
	} else {
		clear();
		printf("Incorrect pin, enter a correct pin\n");
		*pAuthenticated = 0;

		return 0;
	}
}

int inCaseOfBlockedCard() {
	if (authenticationAttempts == 0 && authenticated == 0) {
		clear();
		printf("Your card has been blocked\n");
		printf("Please, contact to bank's offices\n");
		printf("Quiting...\n");
	}

	return 1;
}

// Options Functions
void showOptions() {
	printf("Press c for credit\n");
	printf("Press d for debit\n");
	printf("Press b for balance\n");
	printf("Press q for quit\n");
}

void balanceOption() {
	printf("Your balance is: %d\n\n", balance);	
}

void creditOption() {
	int amountToCredit;

	printf("Enter amount to credit: ");
	scanf(" %d", &amountToCredit);

	balance += amountToCredit;

	clear();

	printf("Approved!\n");
	balanceOption();
}

void debitOption() {
	int amountToDebit, pin;

	printf("Please, enter your PIN again: ");
	scanf(" %d", &pin);

	if (verifyPin(pAuthenticated, pin) == 1) {
		printf("Enter amount to debit: ");
		scanf(" %d", &amountToDebit);

		balance -= amountToDebit;

		clear();

		printf("Approved!\n");
		balanceOption();
	} else {
		clear();

		printf("There was an error with authentication\n");
		printf("Please, contact to bank's offices\n");
		printf("Quiting...\n");
	}

}

void checkAndProceedWithOption(char option, int *pUserWantsToQuit) {
	clear();

	if(option == 'C' || option == 'c') {
		creditOption();

		option = '\0';
	} else if(option == 'D' || option == 'd') {
		debitOption();

		option = '\0';
	} else if(option == 'B' || option == 'b') {
		balanceOption();

		option = '\0';
	} else if(option == 'Q' || option == 'q') {
		clear();

		printf("Have a nice day! :)\n");
		*pUserWantsToQuit = 1;

		option = '\0';
	} else {
		printf("Please, enter a valid option\n");

		option = '\0';
	}	
}

int main() {
	int pin, userWantsToQuit = 0;
	int *pUserWantsToQuit = &userWantsToQuit;
	char option;

	clear();

	// Get user's pin and verify it
	while (authenticated == 0 && authenticationAttempts != 0) {
		printf("Please insert your PIN: ");
		scanf(" %i", &pin); 
		verifyPin(pAuthenticated, pin);

		authenticationAttempts--;
	}

	inCaseOfBlockedCard(authenticationAttempts);
	
	// Show ATM options to the user
	// Get their option
	// Check their option and proceed with the query
	printf("Welcome! User\n");

	while (authenticated == 1 && userWantsToQuit != 1) {
		showOptions();

		printf("\nPlease, select an option: ");
		scanf(" %c", &option);

		checkAndProceedWithOption(option, pUserWantsToQuit);
	}

}
