#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TRANSACTIONS 500
#define MAX_DESC_LENGTH 100
#define FILENAME "money_data.dat"

// Enum to define the type of transaction
typedef enum {
    INCOME,
    EXPENSE
} TransactionType;

// Structure to hold details of a single transaction
typedef struct {
    double amount;
    TransactionType type;
    char category[MAX_DESC_LENGTH];
    char description[MAX_DESC_LENGTH];
    time_t transaction_time;
} Transaction;

// Global array to store all transactions and a counter
Transaction transactions[MAX_TRANSACTIONS];
int transaction_count = 0;

// Function Prototypes
void addTransaction();
void viewTransactions();
void displaySummary();
void saveDataToFile();
void loadDataFromFile();
void displayMenu();
void clearInputBuffer();

int main() {
    // Load existing data from the file when the program starts
    loadDataFromFile();

    int choice;
    do {
        displayMenu();
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            clearInputBuffer();
            choice = 0; // Reset choice to loop again
            continue;
        }
        clearInputBuffer(); // Consume the newline character

        system("cls"); // Use "clear" for Linux/macOS

        switch (choice) {
            case 1:
                addTransaction();
                break;
            case 2:
                viewTransactions();
                break;
            case 3:
                displaySummary();
                break;
            case 4:
                // Save data before exiting
                saveDataToFile();
                printf("Data saved. Exiting Money Manager. Goodbye!\n");
                break;
            default:
                printf("Invalid choice! Please select a valid option (1-4).\n");
        }

        if (choice != 4) {
            printf("\nPress Enter to return to the menu...");
            getchar();
        }

    } while (choice != 4);

    return 0;
}

// Displays the main menu
void displayMenu() {
    system("cls"); // Use "clear" for Linux/macOS
    printf("\n===== ADVANCED MONEY MANAGEMENT SYSTEM =====\n");
    printf("1. Add Transaction (Income/Expense)\n");
    printf("2. View All Transactions\n");
    printf("3. Display Summary\n");
    printf("4. Save and Exit\n");
    printf("==========================================\n");
    printf("Enter your choice: ");
}

// Adds a new income or expense transaction
void addTransaction() {
    if (transaction_count >= MAX_TRANSACTIONS) {
        printf("Transaction limit reached. Cannot add more.\n");
        return;
    }

    Transaction new_trans;
    int type_choice;

    printf("--- Add New Transaction ---\n");
    printf("Enter transaction type (1 for Income, 2 for Expense): ");
    scanf("%d", &type_choice);
    clearInputBuffer();

    if (type_choice == 1) {
        new_trans.type = INCOME;
    } else if (type_choice == 2) {
        new_trans.type = EXPENSE;
    } else {
        printf("Invalid transaction type.\n");
        return;
    }

    printf("Enter amount: ");
    scanf("%lf", &new_trans.amount);
    clearInputBuffer();

    printf("Enter category (e.g., Salary, Groceries, Rent): ");
    fgets(new_trans.category, MAX_DESC_LENGTH, stdin);
    new_trans.category[strcspn(new_trans.category, "\n")] = 0; // Remove newline

    printf("Enter a brief description: ");
    fgets(new_trans.description, MAX_DESC_LENGTH, stdin);
    new_trans.description[strcspn(new_trans.description, "\n")] = 0; // Remove newline

    new_trans.transaction_time = time(NULL); // Record current time

    transactions[transaction_count] = new_trans;
    transaction_count++;

    printf("\nTransaction added successfully!\n");
}

// Displays a list of all recorded transactions
void viewTransactions() {
    if (transaction_count == 0) {
        printf("No transactions recorded yet.\n");
        return;
    }

    printf("--- All Transactions ---\n");
    printf("%-5s | %-12s | %-15s | %-20s | %-25s\n", "ID", "Type", "Amount", "Category", "Description");
    printf("--------------------------------------------------------------------------------------\n");

    for (int i = 0; i < transaction_count; i++) {
        char time_str[30];
        strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M", localtime(&transactions[i].transaction_time));
        
        printf("%-5d | %-12s | $%-14.2f | %-20s | %-25s\n",
               i + 1,
               (transactions[i].type == INCOME) ? "Income" : "Expense",
               transactions[i].amount,
               transactions[i].category,
               transactions[i].description);
    }
    printf("--------------------------------------------------------------------------------------\n");
}

// Calculates and displays the financial summary
void displaySummary() {
    if (transaction_count == 0) {
        printf("No data for summary. Please add a transaction first.\n");
        return;
    }

    double total_income = 0.0;
    double total_expense = 0.0;

    for (int i = 0; i < transaction_count; i++) {
        if (transactions[i].type == INCOME) {
            total_income += transactions[i].amount;
        } else {
            total_expense += transactions[i].amount;
        }
    }

    printf("--- Financial Summary ---\n");
    printf("Total Income:   $%.2f\n", total_income);
    printf("Total Expenses: $%.2f\n", total_expense);
    printf("-------------------------\n");
    printf("Net Balance:    $%.2f\n", total_income - total_expense);
    printf("-------------------------\n");
}

// Saves all transaction data to a binary file
void saveDataToFile() {
    FILE *file = fopen(FILENAME, "wb"); // Open in binary write mode
    if (file == NULL) {
        printf("Error: Could not open file %s for writing.\n", FILENAME);
        return;
    }

    // Write the number of transactions first
    fwrite(&transaction_count, sizeof(int), 1, file);
    // Write the entire transactions array
    fwrite(transactions, sizeof(Transaction), transaction_count, file);

    fclose(file);
}

// Loads transaction data from the binary file
void loadDataFromFile() {
    FILE *file = fopen(FILENAME, "rb"); // Open in binary read mode
    if (file == NULL) {
        // If the file doesn't exist, it's the first run. Do nothing.
        return;
    }

    // Read the number of transactions
    fread(&transaction_count, sizeof(int), 1, file);
    // Read the transaction data into the array
    fread(transactions, sizeof(Transaction), transaction_count, file);

    fclose(file);
    printf("Data loaded successfully from %s.\n", FILENAME);
    printf("Press Enter to continue...");
    getchar();
}

// Utility function to clear the input buffer
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

