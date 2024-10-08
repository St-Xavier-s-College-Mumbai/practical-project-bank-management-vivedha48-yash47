#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_ACCOUNTS 100
#define NAME_LENGTH 50
#define ADDRESS_LENGTH 100
#define PHONE_LENGTH 15

typedef struct {
    int accountNumber;
    char fullName[NAME_LENGTH];
    char address[ADDRESS_LENGTH];
    char phoneNumber[PHONE_LENGTH];
    float balance;
} Account;

Account accounts[MAX_ACCOUNTS];
int accountCount = 0;

int isValidPhoneNumber(const char *phone) {
    // Validate phone number (length and digits)
    if (strlen(phone) != 10) return 0;
    for (int i = 0; i < 10; i++) {
        if (!isdigit(phone[i])) return 0;
    }
    return 1;
}

void saveToFile() {
    FILE *file = fopen("store.txt", "w");  // Open file for writing (overwrite mode)
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    for (int i = 0; i < accountCount; i++) {
        fprintf(file, "Account Number: %d\n", accounts[i].accountNumber);
        fprintf(file, "Full Name: %s\n", accounts[i].fullName);
        fprintf(file, "Address: %s\n", accounts[i].address);
        fprintf(file, "Phone Number: %s\n", accounts[i].phoneNumber);
        fprintf(file, "Balance: %.2f\n\n", accounts[i].balance);
    }

    fclose(file);  // Close the file
}

void createAccount() {
    if (accountCount >= MAX_ACCOUNTS) {
        printf("Maximum account limit reached.\n");
        return;
    }

    Account newAccount;
    newAccount.accountNumber = accountCount + 1;

    printf("Enter account holder's full name: ");
    scanf(" %[^\n]", newAccount.fullName);

    printf("Enter address: ");
    scanf(" %[^\n]", newAccount.address);

    printf("Enter phone number (10 digits): ");
    scanf(" %[^\n]", newAccount.phoneNumber);

    if (!isValidPhoneNumber(newAccount.phoneNumber)) {
        printf("Invalid phone number. It must be 10 digits long.\n");
        return;
    }

    newAccount.balance = 0.0;
    accounts[accountCount] = newAccount;
    accountCount++;

    saveToFile();  // Save to file after account creation

    printf("Account created successfully! Account Number: %d\n", newAccount.accountNumber);
}

void deposit() {
    int accountNumber;
    float amount;

    printf("Enter account number: ");
    scanf("%d", &accountNumber);

    if (accountNumber < 1 || accountNumber > accountCount) {
        printf("Invalid account number.\n");
        return;
    }

    printf("Enter amount to deposit: ");
    scanf("%f", &amount);

    if (amount <= 0) {
        printf("Deposit amount must be greater than zero.\n");
        return;
    }

    accounts[accountNumber - 1].balance += amount;
    saveToFile();  // Save changes to file after deposit

    printf("Deposited %.2f to account number %d. New balance: %.2f\n",
           amount, accountNumber, accounts[accountNumber - 1].balance);
}

void withdraw() {
    int accountNumber;
    float amount;

    printf("Enter account number: ");
    scanf("%d", &accountNumber);

    if (accountNumber < 1 || accountNumber > accountCount) {
        printf("Invalid account number.\n");
        return;
    }

    printf("Enter amount to withdraw: ");
    scanf("%f", &amount);

    if (amount <= 0) {
        printf("Withdrawal amount must be greater than zero.\n");
        return;
    }

    if (amount > accounts[accountNumber - 1].balance) {
        printf("Insufficient funds.\n");
        return;
    }

    accounts[accountNumber - 1].balance -= amount;
    saveToFile();  // Save changes to file after withdrawal

    printf("Withdrew %.2f from account number %d. New balance: %.2f\n",
           amount, accountNumber, accounts[accountNumber - 1].balance);
}

void checkBalance() {
    int accountNumber;

    printf("Enter account number: ");
    scanf("%d", &accountNumber);

    if (accountNumber < 1 || accountNumber > accountCount) {
        printf("Invalid account number.\n");
        return;
    }

    float balance = accounts[accountNumber - 1].balance;
    printf("Account Number: %d\n", accountNumber);
    printf("Balance: %.2f\n", balance);
}

int main() {
    int choice;

    while (1) {
        printf("\n--- Bank Management System ---\n");
        printf("1. Create Account\n");
        printf("2. Deposit\n");
        printf("3. Withdraw\n");
        printf("4. Check Balance\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createAccount();
                break;
            case 2:
                deposit();
                break;
            case 3:
                withdraw();
                break;
            case 4:
                checkBalance();
                break;
            case 5:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
