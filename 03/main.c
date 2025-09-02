#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TASKS 500
#define MAX_DESC_LENGTH 150
#define FILENAME "tasks.dat"

// Enum for task priority
typedef enum {
    LOW,
    MEDIUM,
    HIGH
} TaskPriority;

// Enum for task status
typedef enum {
    PENDING,
    IN_PROGRESS,
    COMPLETED
} TaskStatus;

// Structure to hold a single task
typedef struct {
    char description[MAX_DESC_LENGTH];
    TaskPriority priority;
    TaskStatus status;
    time_t due_date;
} Task;

// Global array and counter for tasks
Task tasks[MAX_TASKS];
int task_count = 0;

// Function Prototypes
void addTask();
void updateTaskStatus();
void viewTasks();
void saveDataToFile();
void loadDataFromFile();
void displayMenu();
void clearInputBuffer();
time_t stringToTime(const char* date_str);
const char* priorityToString(TaskPriority p);
const char* statusToString(TaskStatus s);

int main() {
    loadDataFromFile();
    int choice;

    do {
        displayMenu();
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            clearInputBuffer();
            choice = 0;
            continue;
        }
        clearInputBuffer();

        system("cls"); // Use "clear" for Linux/macOS

        switch (choice) {
            case 1:
                addTask();
                break;
            case 2:
                updateTaskStatus();
                break;
            case 3:
                viewTasks();
                break;
            case 4:
                saveDataToFile();
                printf("Data saved. Exiting Time Management System. Goodbye!\n");
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
    system("cls");
    printf("\n===== ADVANCED TIME MANAGEMENT SYSTEM =====\n");
    printf("1. Add New Task\n");
    printf("2. Update Task Status\n");
    printf("3. View Tasks\n");
    printf("4. Save and Exit\n");
    printf("=========================================\n");
    printf("Enter your choice: ");
}

// Adds a new task to the list
void addTask() {
    if (task_count >= MAX_TASKS) {
        printf("Task limit reached.\n");
        return;
    }

    Task new_task;
    int priority_choice;
    char date_str[11]; // YYYY-MM-DD

    printf("--- Add New Task ---\n");
    printf("Enter task description: ");
    fgets(new_task.description, MAX_DESC_LENGTH, stdin);
    new_task.description[strcspn(new_task.description, "\n")] = 0;

    printf("Enter priority (1-Low, 2-Medium, 3-High): ");
    scanf("%d", &priority_choice);
    clearInputBuffer();
    new_task.priority = (priority_choice == 3) ? HIGH : (priority_choice == 2) ? MEDIUM : LOW;

    printf("Enter due date (YYYY-MM-DD): ");
    fgets(date_str, sizeof(date_str), stdin);
    clearInputBuffer();
    new_task.due_date = stringToTime(date_str);

    new_task.status = PENDING; // New tasks are always pending

    tasks[task_count++] = new_task;
    printf("\nTask added successfully!\n");
}

// Updates the status of an existing task
void updateTaskStatus() {
    if (task_count == 0) {
        printf("No tasks to update.\n");
        return;
    }

    int task_id, status_choice;
    printf("--- Update Task Status ---\n");
    // Display tasks for selection
    for (int i = 0; i < task_count; i++) {
        printf("%d. [%s] %s\n", i + 1, statusToString(tasks[i].status), tasks[i].description);
    }
    printf("---------------------------\n");
    printf("Enter the ID of the task to update: ");
    scanf("%d", &task_id);
    clearInputBuffer();

    if (task_id < 1 || task_id > task_count) {
        printf("Invalid task ID.\n");
        return;
    }

    printf("Enter new status (1-Pending, 2-In Progress, 3-Completed): ");
    scanf("%d", &status_choice);
    clearInputBuffer();

    switch (status_choice) {
        case 1: tasks[task_id - 1].status = PENDING; break;
        case 2: tasks[task_id - 1].status = IN_PROGRESS; break;
        case 3: tasks[task_id - 1].status = COMPLETED; break;
        default: printf("Invalid status choice.\n"); return;
    }

    printf("Task status updated successfully!\n");
}

// Displays tasks with options for filtering and sorting
void viewTasks() {
    if (task_count == 0) {
        printf("No tasks to display.\n");
        return;
    }

    printf("--- View Tasks ---\n");
    printf("%-5s | %-50s | %-10s | %-12s | %-12s\n", "ID", "Description", "Priority", "Status", "Due Date");
    printf("--------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < task_count; i++) {
        char due_date_str[11];
        strftime(due_date_str, sizeof(due_date_str), "%Y-%m-%d", localtime(&tasks[i].due_date));

        printf("%-5d | %-50s | %-10s | %-12s | %-12s\n",
               i + 1,
               tasks[i].description,
               priorityToString(tasks[i].priority),
               statusToString(tasks[i].status),
               due_date_str);
    }
    printf("--------------------------------------------------------------------------------------------------\n");
}

// Saves task data to a binary file
void saveDataToFile() {
    FILE *file = fopen(FILENAME, "wb");
    if (!file) {
        printf("Error: Could not open file %s for writing.\n", FILENAME);
        return;
    }
    fwrite(&task_count, sizeof(int), 1, file);
    fwrite(tasks, sizeof(Task), task_count, file);
    fclose(file);
}

// Loads task data from a binary file
void loadDataFromFile() {
    FILE *file = fopen(FILENAME, "rb");
    if (!file) {
        // File doesn't exist, first run.
        return;
    }
    fread(&task_count, sizeof(int), 1, file);
    fread(tasks, sizeof(Task), task_count, file);
    fclose(file);
    printf("Task data loaded successfully from %s.\n", FILENAME);
    printf("Press Enter to continue...");
    getchar();
}

// Helper to convert a "YYYY-MM-DD" string to a time_t object
time_t stringToTime(const char* date_str) {
    struct tm tm = {0};
    if (sscanf(date_str, "%d-%d-%d", &tm.tm_year, &tm.tm_mon, &tm.tm_mday) == 3) {
        tm.tm_year -= 1900; // tm_year is years since 1900
        tm.tm_mon -= 1;     // tm_mon is 0-11
        return mktime(&tm);
    }
    return time(NULL); // Return current time on failure
}

// Helper to convert priority enum to string
const char* priorityToString(TaskPriority p) {
    switch (p) {
        case HIGH: return "High";
        case MEDIUM: return "Medium";
        case LOW: return "Low";
        default: return "N/A";
    }
}

// Helper to convert status enum to string
const char* statusToString(TaskStatus s) {
    switch (s) {
        case PENDING: return "Pending";
        case IN_PROGRESS: return "In Progress";
        case COMPLETED: return "Completed";
        default: return "N/A";
    }
}

// Utility to clear the input buffer
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

