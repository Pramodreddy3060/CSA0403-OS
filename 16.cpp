#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "employees.dat"

// Employee Structure
typedef struct {
    int id;
    char name[50];
    float salary;
} Employee;

// Function to add a new employee record
void addEmployee() {
    FILE *file = fopen(FILE_NAME, "ab"); // Open file in append-binary mode
    if (!file) {
        printf("Error: Could not open file!\n");
        return;
    }

    Employee emp;
    printf("Enter Employee ID: ");
    scanf("%d", &emp.id);
    printf("Enter Employee Name: ");
    scanf(" %[^\n]", emp.name);  // To read full name including spaces
    printf("Enter Employee Salary: ");
    scanf("%f", &emp.salary);

    fwrite(&emp, sizeof(Employee), 1, file); // Write structure to file
    fclose(file);
    printf("Employee record added successfully!\n");
}

// Function to display all employees
void displayEmployees() {
    FILE *file = fopen(FILE_NAME, "rb"); // Open file in read-binary mode
    if (!file) {
        printf("Error: Could not open file!\n");
        return;
    }

    Employee emp;
    printf("\nEmployee Details:\n");
    printf("ID\tName\t\tSalary\n");
    printf("--------------------------------\n");

    while (fread(&emp, sizeof(Employee), 1, file)) {
        printf("%d\t%-15s\t%.2f\n", emp.id, emp.name, emp.salary);
    }

    fclose(file);
}

// Function to search for an employee by ID
void searchEmployee() {
    FILE *file = fopen(FILE_NAME, "rb");
    if (!file) {
        printf("Error: Could not open file!\n");
        return;
    }

    int searchID;
    printf("Enter Employee ID to search: ");
    scanf("%d", &searchID);

    Employee emp;
    while (fread(&emp, sizeof(Employee), 1, file)) {
        if (emp.id == searchID) {
            printf("Employee Found!\n");
            printf("ID: %d\nName: %s\nSalary: %.2f\n", emp.id, emp.name, emp.salary);
            fclose(file);
            return;
        }
    }

    printf("Error: Employee with ID %d not found!\n", searchID);
    fclose(file);
}

// Function to update an employee record
void updateEmployee() {
    FILE *file = fopen(FILE_NAME, "r+b"); // Open file in read+write mode
    if (!file) {
        printf("Error: Could not open file!\n");
        return;
    }

    int searchID;
    printf("Enter Employee ID to update: ");
    scanf("%d", &searchID);

    Employee emp;
    long pos;
    while (fread(&emp, sizeof(Employee), 1, file)) {
        if (emp.id == searchID) {
            printf("Enter new Name: ");
            scanf(" %[^\n]", emp.name);
            printf("Enter new Salary: ");
            scanf("%f", &emp.salary);

            pos = ftell(file) - sizeof(Employee); // Move to the correct position
            fseek(file, pos, SEEK_SET); // Move file pointer back to update record
            fwrite(&emp, sizeof(Employee), 1, file); // Overwrite record
            fclose(file);
            printf("Employee record updated successfully!\n");
            return;
        }
    }

    printf("Error: Employee with ID %d not found!\n", searchID);
    fclose(file);
}

int main() {
    int choice;
    
    while (1) {
        printf("\nEmployee Management System\n");
        printf("1. Add Employee\n");
        printf("2. Display Employees\n");
        printf("3. Search Employee\n");
        printf("4. Update Employee\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addEmployee(); break;
            case 2: displayEmployees(); break;
            case 3: searchEmployee(); break;
            case 4: updateEmployee(); break;
            case 5: printf("Exiting...\n"); return 0;
            default: printf("Invalid choice! Try again.\n");
        }
    }
}
