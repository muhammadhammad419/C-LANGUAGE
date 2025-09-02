#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CONTACTS 200
#define MAX_FIELD_LENGTH 50
#define FILENAME "contacts.dat"

// Structure to represent a single contact
typedef struct {
    char name[MAX_FIELD_LENGTH];
    char phone[MAX_FIELD_LENGTH];
    char email[MAX_FIELD_LENGTH];
} Contact;

// Global array to store contacts and a counter
Contact contacts[MAX_CONTACTS];
int contact_count = 0;

// --- Function Prototypes ---
// Core CRUD Operations
void addContact();
void viewContacts(); // Will now be the sorted view
void updateContact();
void deleteContact();
void searchContact();
void listContactsForSelection(); // Unsorted view with IDs for management

// File I/O
void saveContactsToFile();
void loadContactsFromFile();

// UI and Utilities
void displayMenu();
void clearInputBuffer();
int getContactChoice(const char* action);

// Helper for qsort
int compareContactsByName(const void* a, const void* b);

int main() {
    loadContactsFromFile();
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

        system("cls"); // Use "clear" for Linux/macOS

        switch (choice) {
            case 1: addContact(); break;
            case 2: viewContacts(); break;
            case 3: searchContact(); break;
            case 4: updateContact(); break;
            case 5: deleteContact(); break;
            case 6:
                saveContactsToFile();
                printf("Contacts saved. Exiting application. Goodbye!\n");
                break;
            default:
                printf("Invalid choice! Please select a valid option (1-6).\n");
        }

        if (choice != 6) {
            printf("\nPress Enter to return to the menu...");
            getchar();
        }
    } while (choice != 6);

    return 0;
}

// --- Core CRUD Function Implementations ---

void addContact() {
    if (contact_count >= MAX_CONTACTS) {
        printf("Contact book is full. Cannot add more contacts.\n");
        return;
    }

    Contact new_contact;
    printf("--- Add New Contact ---\n");

    printf("Enter Name: ");
    fgets(new_contact.name, MAX_FIELD_LENGTH, stdin);
    new_contact.name[strcspn(new_contact.name, "\n")] = 0; // Remove newline

    printf("Enter Phone Number: ");
    fgets(new_contact.phone, MAX_FIELD_LENGTH, stdin);
    new_contact.phone[strcspn(new_contact.phone, "\n")] = 0;

    printf("Enter Email: ");
    fgets(new_contact.email, MAX_FIELD_LENGTH, stdin);
    new_contact.email[strcspn(new_contact.email, "\n")] = 0;

    contacts[contact_count] = new_contact;
    contact_count++;

    printf("\nContact added successfully!\n");
}

// Comparison function for qsort to sort contacts by name
int compareContactsByName(const void* a, const void* b) {
    const Contact* contactA = (const Contact*)a;
    const Contact* contactB = (const Contact*)b;
    return strcmp(contactA->name, contactB->name);
}

// Displays all contacts, sorted alphabetically by name
void viewContacts() {
    if (contact_count == 0) {
        printf("No contacts to display.\n");
        return;
    }

    // Create a temporary copy for sorting to not mess up original indices
    Contact sorted_contacts[MAX_CONTACTS];
    memcpy(sorted_contacts, contacts, contact_count * sizeof(Contact));

    // Sort the temporary array using the standard library's qsort
    qsort(sorted_contacts, contact_count, sizeof(Contact), compareContactsByName);

    printf("--- All Contacts (Sorted by Name) ---\n");
    printf("%-25s | %-20s | %-25s\n", "Name", "Phone Number", "Email");
    printf("------------------------------------------------------------------\n");
    for (int i = 0; i < contact_count; i++) {
        printf("%-25s | %-20s | %-25s\n", sorted_contacts[i].name, sorted_contacts[i].phone, sorted_contacts[i].email);
    }
    printf("------------------------------------------------------------------\n");
}

// Displays all contacts with their IDs for selection purposes (Update/Delete)
void listContactsForSelection() {
    printf("--- Select a Contact ---\n");
    printf("%-5s | %-25s | %-20s | %-25s\n", "ID", "Name", "Phone Number", "Email");
    printf("--------------------------------------------------------------------------------\n");
    for (int i = 0; i < contact_count; i++) {
        printf("%-5d | %-25s | %-20s | %-25s\n", i + 1, contacts[i].name, contacts[i].phone, contacts[i].email);
    }
    printf("--------------------------------------------------------------------------------\n");
}

void updateContact() {
    int id = getContactChoice("update");
    if (id == -1) return; // No contacts or invalid choice

    printf("\nEnter new details for contact #%d (leave blank to keep current value):\n", id);
    
    char buffer[MAX_FIELD_LENGTH];

    // Update Name
    printf("Current Name: %s\nNew Name: ", contacts[id - 1].name);
    fgets(buffer, MAX_FIELD_LENGTH, stdin);
    if (buffer[0] != '\n') {
        buffer[strcspn(buffer, "\n")] = 0;
        strcpy(contacts[id - 1].name, buffer);
    }

    // Update Phone
    printf("Current Phone: %s\nNew Phone: ", contacts[id - 1].phone);
    fgets(buffer, MAX_FIELD_LENGTH, stdin);
    if (buffer[0] != '\n') {
        buffer[strcspn(buffer, "\n")] = 0;
        strcpy(contacts[id - 1].phone, buffer);
    }

    // Update Email
    printf("Current Email: %s\nNew Email: ", contacts[id - 1].email);
    fgets(buffer, MAX_FIELD_LENGTH, stdin);
    if (buffer[0] != '\n') {
        buffer[strcspn(buffer, "\n")] = 0;
        strcpy(contacts[id - 1].email, buffer);
    }

    printf("\nContact updated successfully!\n");
}

void deleteContact() {
    int id = getContactChoice("delete");
    if (id == -1) return;

    char confirm;
    printf("Are you sure you want to delete '%s'? (y/n): ", contacts[id - 1].name);
    scanf(" %c", &confirm);
    clearInputBuffer();

    if (confirm == 'y' || confirm == 'Y') {
        // Shift all subsequent elements one position to the left
        for (int i = id - 1; i < contact_count - 1; i++) {
            contacts[i] = contacts[i + 1];
        }
        contact_count--;
        printf("Contact deleted successfully.\n");
    } else {
        printf("Deletion cancelled.\n");
    }
}

void searchContact() {
    if (contact_count == 0) {
        printf("No contacts to search.\n");
        return;
    }

    char query[MAX_FIELD_LENGTH];
    printf("Enter search term (name, phone, or email): ");
    fgets(query, MAX_FIELD_LENGTH, stdin);
    query[strcspn(query, "\n")] = 0;

    int found = 0;
    printf("\n--- Search Results ---\n");
    for (int i = 0; i < contact_count; i++) {
        // strstr checks if the query is a substring of the field
        if (strstr(contacts[i].name, query) || strstr(contacts[i].phone, query) || strstr(contacts[i].email, query)) {
            if (!found) { // Print header only once
                printf("%-5s | %-25s | %-20s | %-25s\n", "ID", "Name", "Phone Number", "Email");
                printf("--------------------------------------------------------------------------------\n");
            }
            printf("%-5d | %-25s | %-20s | %-25s\n", i + 1, contacts[i].name, contacts[i].phone, contacts[i].email);
            found++;
        }
    }

    if (found == 0) {
        printf("No contacts found matching your search term.\n");
    } else {
        printf("--------------------------------------------------------------------------------\n");
        printf("Found %d matching contact(s).\n", found);
    }
}

// --- File I/O Implementations ---

void saveContactsToFile() {
    FILE *file = fopen(FILENAME, "wb");
    if (file == NULL) {
        printf("Error: Could not open file %s for writing.\n", FILENAME);
        return;
    }
    fwrite(&contact_count, sizeof(int), 1, file);
    fwrite(contacts, sizeof(Contact), contact_count, file);
    fclose(file);
}

void loadContactsFromFile() {
    FILE *file = fopen(FILENAME, "rb");
    if (file == NULL) {
        // File doesn't exist, probably the first run.
        return;
    }
    fread(&contact_count, sizeof(int), 1, file);
    fread(contacts, sizeof(Contact), contact_count, file);
    fclose(file);
}

// --- UI and Utility Implementations ---

void displayMenu() {
    system("cls");
    printf("\n===== CONTACT BOOK APPLICATION =====\n");
    printf("1. Add Contact\n");
    printf("2. View All Contacts\n");
    printf("3. Search Contact\n");
    printf("4. Update Contact\n");
    printf("5. Delete Contact\n");
    printf("6. Save and Exit\n");
    printf("==================================\n");
    printf("Enter your choice: ");
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Helper function to display contacts and get a valid user choice
int getContactChoice(const char* action) {
    if (contact_count == 0) {
        printf("No contacts to %s.\n", action);
        return -1;
    }
    listContactsForSelection();
    printf("\nEnter the ID of the contact to %s: ", action);
    int id;
    scanf("%d", &id);
    clearInputBuffer();

    if (id < 1 || id > contact_count) {
        printf("Invalid ID.\n");
        return -1;
    }
    return id;
}
