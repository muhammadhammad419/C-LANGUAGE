#include <stdio.h>
#include <stdlib.h> // For system("cls")
#include <math.h>   // For sqrt(), pow()

#define M_PI 3.14159265358979323846
// Function Prototypes
void performArithmetic();
void solveQuadratic();
void calculateArea();
void calculateFactorial();
void displayMenu();
void clearInputBuffer();

int main() {
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
            case 1:
                performArithmetic();
                break;
            case 2:
                solveQuadratic();
                break;
            case 3:
                calculateArea();
                break;
            case 4:
                calculateFactorial();
                break;
            case 5:
                printf("Exiting Math Solver. Goodbye!\n");
                break;
            default:
                printf("Invalid choice! Please select a valid option (1-5).\n");
        }

        if (choice != 5) {
            printf("\nPress Enter to return to the menu...");
            getchar();
        }

    } while (choice != 5);

    return 0;
}

// Displays the main menu
void displayMenu() {
    system("cls");
    printf("\n===== MATH QUESTION SOLVER =====\n");
    printf("1. Basic Arithmetic (+, -, *, /)\n");
    printf("2. Solve Quadratic Equation (ax^2 + bx + c = 0)\n");
    printf("3. Calculate Area of a Shape\n");
    printf("4. Calculate Factorial (n!)\n");
    printf("5. Exit\n");
    printf("================================\n");
    printf("Enter your choice: ");
}

// Solves basic arithmetic problems
void performArithmetic() {
    double num1, num2, result;
    char op;

    printf("--- Basic Arithmetic ---\n");
    printf("Enter an expression (e.g., 5 * 3): ");
    if (scanf("%lf %c %lf", &num1, &op, &num2) != 3) {
        printf("Invalid expression format.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    switch (op) {
        case '+':
            result = num1 + num2;
            break;
        case '-':
            result = num1 - num2;
            break;
        case '*':
            result = num1 * num2;
            break;
        case '/':
            if (num2 == 0) {
                printf("Error: Division by zero is not allowed.\n");
                return;
            }
            result = num1 / num2;
            break;
        default:
            printf("Error: Invalid operator '%c'.\n", op);
            return;
    }
    printf("Result: %.2lf %c %.2lf = %.2lf\n", num1, op, num2, result);
}

// Solves a quadratic equation for its real roots
void solveQuadratic() {
    double a, b, c, discriminant, root1, root2;

    printf("--- Quadratic Equation Solver (ax^2 + bx + c = 0) ---\n");
    printf("Enter coefficients a, b, and c: ");
    if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
        printf("Invalid input. Please enter three numbers.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    if (a == 0) {
        printf("This is not a quadratic equation (a cannot be 0).\n");
        return;
    }

    discriminant = b * b - 4 * a * c;

    if (discriminant > 0) {
        root1 = (-b + sqrt(discriminant)) / (2 * a);
        root2 = (-b - sqrt(discriminant)) / (2 * a);
        printf("Two distinct real roots exist: %.2lf and %.2lf\n", root1, root2);
    } else if (discriminant == 0) {
        root1 = -b / (2 * a);
        printf("One real root exists: %.2lf\n", root1);
    } else { // discriminant < 0
        printf("No real roots exist (roots are complex).\n");
    }
}

// Calculates the area of a selected shape
void calculateArea() {
    int choice;
    printf("--- Area Calculator ---\n");
    printf("1. Circle\n2. Rectangle\n3. Triangle\n");
    printf("Select a shape: ");
    scanf("%d", &choice);
    clearInputBuffer();

    switch (choice) {
        case 1: { // Circle
            double radius, area;
            printf("Enter the radius of the circle: ");
            scanf("%lf", &radius);
            clearInputBuffer();
            area = M_PI * pow(radius, 2);
            printf("Area of the circle is: %.2lf\n", area);
            break;
        }
        case 2: { // Rectangle
            double length, width, area;
            printf("Enter the length and width of the rectangle: ");
            scanf("%lf %lf", &length, &width);
            clearInputBuffer();
            area = length * width;
            printf("Area of the rectangle is: %.2lf\n", area);
            break;
        }
        case 3: { // Triangle
            double base, height, area;
            printf("Enter the base and height of the triangle: ");
            scanf("%lf %lf", &base, &height);
            clearInputBuffer();
            area = 0.5 * base * height;
            printf("Area of the triangle is: %.2lf\n", area);
            break;
        }
        default:
            printf("Invalid shape selection.\n");
    }
}

// Calculates the factorial of a non-negative integer
void calculateFactorial() {
    int n;
    unsigned long long factorial = 1;

    printf("--- Factorial Calculator (n!) ---\n");
    printf("Enter a non-negative integer: ");
    scanf("%d", &n);
    clearInputBuffer();

    if (n < 0) {
        printf("Factorial is not defined for negative numbers.\n");
    } else if (n > 20) {
        // Factorial of numbers > 20 exceeds the capacity of unsigned long long
        printf("Input too large. This program supports factorials up to 20.\n");
    } else {
        for (int i = 1; i <= n; ++i) {
            factorial *= i;
        }
        printf("Factorial of %d = %llu\n", n, factorial);
    }
}

// Utility function to clear the input buffer
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
