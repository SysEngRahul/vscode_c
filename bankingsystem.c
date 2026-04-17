#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 100

// Structure for account
struct Account {
    unsigned long long accountNumber;
    char name[MAX_NAME_LENGTH];
    double balance;
    struct Account* next;
};

// Head pointer for linked list
struct Account* head = NULL;

// Function to clear input buffer
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Function to create a new account
void createAccount() {
    unsigned long long accNum;
    char name[MAX_NAME_LENGTH];
    printf("Enter account number: ");
    scanf("%llu", &accNum);
    clearInputBuffer();

    // Check if account already exists
    struct Account* temp = head;
    while (temp != NULL) {
        if (temp->accountNumber == accNum) {
            printf("Account number already exists!\n");
            return;
        }
        temp = temp->next;
    }

    printf("Enter name: ");
    fgets(name, MAX_NAME_LENGTH, stdin);
    name[strcspn(name, "\n")] = 0; // Remove newline

    // Allocate new account
    struct Account* newAcc = (struct Account*)malloc(sizeof(struct Account));
    newAcc->accountNumber = accNum;
    strcpy(newAcc->name, name);
    newAcc->balance = 0.0;
    newAcc->next = head;
    head = newAcc;

    printf("Account created successfully!\n");
}

// Function to display all accounts
void displayAccounts() {
    if (head == NULL) {
        printf("No accounts to display.\n");
        return;
    }
    struct Account* temp = head;
    printf("=== Accounts List ===\n");
    while (temp != NULL) {
        printf("Account Number: %llu, Name: %s, Balance: %.2f\n",
               temp->accountNumber, temp->name, temp->balance);
        temp = temp->next;
    }
}

// Function to deposit amount
void deposit() {
    unsigned long long accNum;
    double amount;
    printf("Enter account number: ");
    scanf("%llu", &accNum);
    clearInputBuffer();

    printf("Enter amount to deposit: ");
    scanf("%lf", &amount);
    clearInputBuffer();

    struct Account* temp = head;
    while (temp != NULL) {
        if (temp->accountNumber == accNum) {
            temp->balance += amount;
            printf("Deposit successful! New balance: %.2f\n", temp->balance);
            return;
        }
        temp = temp->next;
    }
    printf("Account not found.\n");
}

// Function to withdraw amount
void withdraw() {
    unsigned long long accNum;
    double amount;
    printf("Enter account number: ");
    scanf("%llu", &accNum);
    clearInputBuffer();

    printf("Enter amount to withdraw: ");
    scanf("%lf", &amount);
    clearInputBuffer();

    struct Account* temp = head;
    while (temp != NULL) 
    {
        if (temp->accountNumber == accNum) {
            if (temp->balance >= amount) 
            {
                temp->balance -= amount;
                printf("Withdrawal successful! New balance: %.2f\n", temp->balance);
            } 
            
            else 
            {
                printf("Insufficient balance.\n");
            }
            return;
        }

        temp = temp->next;
    }

    printf("Account not found.\n");
}

// Function to save accounts to file
void saveAccounts() {
    FILE* fp = fopen("accounts.txt", "w");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }
    struct Account* temp = head;
    while (temp != NULL) {
        fprintf(fp, "%llu,%s,%.2f\n", temp->accountNumber, temp->name, temp->balance);
        temp = temp->next;
    }
    fclose(fp);
    printf("Accounts saved successfully.\n");
}

// Function to load accounts from file
void loadAccounts() {
    FILE* fp = fopen("accounts.txt", "r");
    if (fp == NULL) {
        printf("No saved accounts found.\n");
        return;
    }
    // Clear existing list
    struct Account* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }

    unsigned long long accNum;
    char name[MAX_NAME_LENGTH];
    double balance;
    while (fscanf(fp, "%llu,%[^,],%lf\n", &accNum, name, &balance) == 3) {
        struct Account* newAcc = (struct Account*)malloc(sizeof(struct Account));
        newAcc->accountNumber = accNum;
        strcpy(newAcc->name, name);
        newAcc->balance = balance;
        newAcc->next = head;
        head = newAcc;
    }
    fclose(fp);
    printf("Accounts loaded successfully.\n");
}

// Main menu
void menu() {
    int choice;
    do {
        printf("\n=== Banking System Menu ===\n");
        printf("1. Create Account\n");
        printf("2. Display Accounts\n");
        printf("3. Deposit\n");
        printf("4. Withdraw\n");
        printf("5. Save Accounts\n");
        printf("6. Load Accounts\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice) {
            case 1:
                createAccount();
                break;
            case 2:
                displayAccounts();
                break;
            case 3:
                deposit();
                break;
            case 4:
                withdraw();
                break;
            case 5:
                saveAccounts();
                break;
            case 6:
                loadAccounts();
                break;
            case 7:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 7);
}

int main() {
    menu();
    // Free allocated memory
    struct Account* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
    return 0;
}