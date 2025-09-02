#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h> // For system("cls") or system("clear")
// --------------------------------------- Mulitplication Function ------------------------------
// int main() {
//     printf("Multiplication Program \n");
//     int x , y , z;
//     printf("Enter a number:");
//     scanf("%d" , &x);
//     printf("Enter a number:");
//     scanf("%d" , &y);
//     z = x * y;
//     printf("result : %d", z);
//     getch();
// }
// ------------------------------------------- Area of Rectangle ------------------------------
// int main() {
//     printf("Area Of Rectangle: \n");
//     int w , h , r;
//     printf("Enter a width:");
//     scanf("%d", &w);
//     printf("Enter a length:");
//     scanf("%d", &h);
//     r = w * h;
//     printf("Result: %d", r / 9);
//     getch();
// };
// ====================================== Muliplication Function ================================
// int add(int a , int b) {
//     int c ;
//     c = a * b;
//     return c;
// };

// int main() {
//     int x = 2  , y = 2 , res;
//     printf("Enter a two number:\n");
//     printf("Enter a number:");
//     scanf("%d", &x);
//     printf("Enter a number");
//     scanf("%d", &y);
//     res = add(x,y);
//     printf("Print a Result: %d" , res);
//     return 0;
// };
// =========================== Find the bug =========================================
// void main() {
//     char ch , ch , sum;
//     clrscr();
//     ch="a";
//     ch="b";
//     sum = ch + ch;
//     printf("sum = %d", sum);
//     getch();
// };

// ========================== warning this is a infanite loop ==================================
// int main() {
//     for(int n = 10; n >= 10; n++) {
//         printf("hello sir %d",n);
//     };
// };

// ------------------------------------ pattren programming -----------------------------------
// int main() { 
// int i , j , s;
// for(i = 15; i >= 1; i--) {
//     for(s = 1; s <= 15-i; s++) {
//         printf(" ");
//     }
//     for(j = 1; j <= i; j++) {
//         printf("*");
//     }
//     printf("\n");
// }
// };

// ================================== pattren programming =======================================
// int main() {
//     int i,j,s;
//     for(i = 1; i <= 15; i++) {
//         for(s = 1; s <= 15-i; s++){
//             printf(" ");
//         }
//         for(j = 1; j <= i; j++) {
//             printf("*");
//         };
//         printf("\n");
//     };
// };
// -------------------------- Calculate the area of triangle ------------------------------
// int main() {
//     float base , height;
//     double area;
//     printf("Enter the base:");
//     scanf("%f", &base);
//     printf("Enter the height:");
//     scanf("%f", &height);
//     area = 0.5 * base * height;
//     printf("Result is: %5.2f\n", area);
//     getch();
//     return 0;
// };


// int main() {
//     char a[] = "                   ";
//     printf("Enter the charcters:");
//     scanf("%c", &a);
//     printf("The ACII code is %c%d",a,a);
//     getch();
//     return 0;
// }
 
// ============================= test and check the error ===============================
// int main() {
//         char vovels = "";
//         printf("Check the Vovels Characters:");
//         scanf("%c",&vovels);
//         if(vovels == "a" || vovels == "A" || vovels == "e" || vovels == "E" || vovels == "i" || vovels == "I" || vovels == "o" || vovels == "O" || vovels == "u" || vovels == "U") {
//             printf("%cThis is a vovels:", vovels);
//         } else {
//             printf("%cThis is not vovels:", vovels);
//         };
    
//     return 0;
// };

// ============================ find the grather number =================================
// int main() {
//     int a , b , c;
//     printf("Enter a three number:");
//     scanf("%d%d%d", &a, &b, &c);
//     if(a>b && a>c) {
//         printf("%d is grather then %d and %d", a,b,c);
//     }else if(b>a && b>c) {
//         printf("%d is grather then %d and %d", b,a,c);
//     } else if(a == b && b == c && c == a) {
//         printf("Both are equel %d %d %d",a,b,c);
//     } else {
//         printf("%d is grather then %d and %d", c,a,b);
//     };
//     return 0;
// };

// int main() {
//     int x = 4;
//     ++x;
//     printf("%d",x);
//     return 0;
// };

// int main() {
//     int i , j;
//     for(i = 1; i > 31; i--) {
//       for(j = 1; j <= i; j++) {
//         printf("%d ",j);
//       };
//       printf("\n");
//     };
// };

// int main() {
//     int a , b;
//     for(a=11; a>=1; a--) {
//         for(b=1; b<a; b++) {
//             printf("%d ",b);
//         }
//         printf("\n");
//     }
//     return 0;
// }

// int main() {
//     int arr[7];
//     int i;
//     float s = 0.0f;
//     float per;
//     const char* subjects[] = {
//         "English", "Urdu", "Maths", "Economic", "Computer","pk","Al Quran"
//     };

//     for(i = 0; i < 7; i++) {
//         printf("Enter the %s subject number: ", subjects[i]);
//         scanf("%d", &arr[i]);
//     }

//     for(i = 0; i < 7; i++) {
//         s = s + arr[i];
//     }
//     printf("Total Number: %.0f\n",s);
//     per = (s / 550.0f) * 100.0f;
//     printf("Percentage is: %.2f%%\n",per);
//     return 0;
// }



#define MAX_CANDIDATES 10
#define MAX_NAME_LENGTH 50

// Structure to represent a single candidate
typedef struct {
    char name[MAX_NAME_LENGTH];
    int votes;
} Candidate;

// Global array to store all candidates and a counter
Candidate candidates[MAX_CANDIDATES];
int candidate_count = 0;

// Function Prototypes
void addCandidate();
void castVote();
void displayResults();
void findWinner();
void clearInputBuffer();
void displayMenu();

int main() {
    int choice;

    // Main menu loop
    do {
        displayMenu();
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            clearInputBuffer(); // Clear the faulty input
            choice = 0; // Reset choice to avoid exiting
            continue;
        }
        clearInputBuffer(); // Consume the newline character left by scanf

        // Use system("cls") for Windows or system("clear") for Linux/macOS
        system("cls"); 

        switch (choice) {
            case 1:
                addCandidate();
                break;
            case 2:
                castVote();
                break;
            case 3:
                displayResults();
                break;
            case 4:
                findWinner();
                break;
            case 5:
                printf("Exiting the voting system. Goodbye!\n");
                break;
            default:
                printf("Invalid choice! Please select a valid option (1-5).\n");
        }
        printf("\nPress Enter to continue...");
        getchar(); // Wait for user to press Enter

    } while (choice != 5);

    return 0;
}

// Displays the main menu options
void displayMenu() {
    // Use system("cls") for Windows or system("clear") for Linux/macOS
    system("cls");
    printf("\n===== VOTE MANAGEMENT SYSTEM =====\n");
    printf("1. Add Candidate\n");
    printf("2. Cast Vote\n");
    printf("3. Show Vote Count\n");
    printf("4. Find Winner\n");
    printf("5. Exit\n");
    printf("==================================\n");
    printf("Enter your choice: ");
}

// Adds a new candidate to the election
void addCandidate() {
    if (candidate_count >= MAX_CANDIDATES) {
        printf("Maximum number of candidates reached (%d).\n", MAX_CANDIDATES);
        return;
    }

    printf("Enter the name of the new candidate: ");
    // fgets is safer than scanf for strings as it prevents buffer overflows
    fgets(candidates[candidate_count].name, MAX_NAME_LENGTH, stdin);
    // Remove the newline character that fgets stores
    candidates[candidate_count].name[strcspn(candidates[candidate_count].name, "\n")] = 0;

    candidates[candidate_count].votes = 0; // Initialize votes to zero
    candidate_count++;

    printf("Candidate added successfully!\n");
}

// Casts a vote for a chosen candidate
void castVote() {
    if (candidate_count == 0) {
        printf("No candidates have been registered yet. Please add a candidate first.\n");
        return;
    }

    int choice;
    printf("----- Cast Your Vote -----\n");
    for (int i = 0; i < candidate_count; i++) {
        printf("%d. %s\n", i + 1, candidates[i].name);
    }
    printf("--------------------------\n");
    printf("Enter the number of the candidate you want to vote for: ");

    if (scanf("%d", &choice) != 1) {
        printf("Invalid input. Please enter a number.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    if (choice > 0 && choice <= candidate_count) {
        candidates[choice - 1].votes++;
        printf("Your vote for %s has been cast!\n", candidates[choice - 1].name);
    } else {
        printf("Invalid candidate number. Please try again.\n");
    }
}

// Displays the current results for all candidates
void displayResults() {
    if (candidate_count == 0) {
        printf("No votes to display as no candidates are registered.\n");
        return;
    }

    printf("----- ELECTION RESULTS -----\n");
    for (int i = 0; i < candidate_count; i++) {
        printf("%s: %d votes\n", candidates[i].name, candidates[i].votes);
    }
    printf("----------------------------\n");
}

// Finds and displays the winner(s) of the election
void findWinner() {
    if (candidate_count == 0) {
        printf("Cannot determine a winner. No candidates are registered.\n");
        return;
    }

    int max_votes = -1;

    // First, find the highest vote count
    for (int i = 0; i < candidate_count; i++) {
        if (candidates[i].votes > max_votes) {
            max_votes = candidates[i].votes;
        }
    }
    
    if (max_votes == 0) {
        printf("No votes have been cast yet. Cannot determine a winner.\n");
        return;
    }

    printf("----- WINNER(S) -----\n");
    // Second, find all candidates who have that highest vote count (to handle ties)
    for (int i = 0; i < candidate_count; i++) {
        if (candidates[i].votes == max_votes) {
            printf("Winner: %s with %d votes!\n", candidates[i].name, max_votes);
        }
    }
    printf("----------------------\n");
}

// A utility function to clear the input buffer after using scanf
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
