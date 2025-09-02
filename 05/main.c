#include <stdio.h>
#include <stdlib.h> // For rand(), srand(), system()
#include <time.h>   // For time()

// Function Prototypes
void playGame();
void displayMenu();
void clearInputBuffer();

int main() {
    // Seed the random number generator only once when the program starts
    srand(time(NULL));

    int choice;
    do {
        displayMenu();
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            clearInputBuffer();
            choice = 0; // Reset to loop again
            continue;
        }
        clearInputBuffer();

        switch (choice) {
            case 1:
                playGame();
                break;
            case 2:
                printf("\nThank you for playing Mind Trap! Goodbye!\n");
                break;
            default:
                printf("\nInvalid choice! Please select a valid option (1-2).\n");
                printf("Press Enter to continue...");
                getchar();
        }

    } while (choice != 2);

    return 0;
}

// Displays the main menu
void displayMenu() {
    system("cls"); // Use "clear" for Linux/macOS
    printf("\n\n\t\t*** Welcome to the Mind Trap Puzzle! ***\n\n");
    printf("\tThe computer has trapped a secret number between 1 and 100.\n");
    printf("\tYou have 7 attempts to guess it and escape the trap.\n\n");
    printf("\t\t\t.-----------------.\n");
    printf("\t\t\t|   1. Play Game  |\n");
    printf("\t\t\t|   2. Exit       |\n");
    printf("\t\t\t'-----------------'\n\n");
    printf("\t\t\tEnter your choice: ");
}

// Main game logic
void playGame() {
    system("cls");
    // Generate a random number between 1 and 100
    int secretNumber = (rand() % 100) + 1;
    int guess;
    int attempts = 7;
    int attempts_taken = 0;

    printf("\nThe trap is set! I'm thinking of a number between 1 and 100.\n");

    while (attempts > 0) {
        printf("\n- You have %d attempts left. -\n", attempts);
        printf("Enter your guess: ");

        if (scanf("%d", &guess) != 1) {
            printf("That's not a number! You're wasting your guesses.\n");
            clearInputBuffer();
            attempts--;
            attempts_taken++;
            continue;
        }
        clearInputBuffer();

        attempts--;
        attempts_taken++;

        if (guess < secretNumber) {
            printf("Too low! The secret number is higher.\n");
        } else if (guess > secretNumber) {
            printf("Too high! The secret number is lower.\n");
        } else {
            printf("\n********************************************************\n");
            printf("*\n");
            printf("*   Congratulations! You guessed the number %d in %d attempts!   *\n", secretNumber, attempts_taken);
            printf("*   You have escaped the Mind Trap!                      *\n");
            printf("*\n");
            printf("********************************************************\n");
            printf("\nPress Enter to return to the menu...");
            getchar();
            return; // Exit the function and go back to the menu
        }
    }

    // This code runs only if the while loop finishes (player runs out of attempts)
    printf("\n--------------------------------------------------------\n");
    printf("|   Oh no! You've run out of attempts.                 |\n");
    printf("|   The Mind Trap has closed! The secret number was %d.  |\n", secretNumber);
    printf("|   Better luck next time!                             |\n");
    printf("--------------------------------------------------------\n");
    printf("\nPress Enter to return to the menu...");
    getchar();
}

// Utility function to clear the input buffer
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

