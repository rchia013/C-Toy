#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char name[50];
    char department[50];
    char position[50];
    float salary;
} Employee;

Employee* addEmployee(Employee* database, int* currentEmployeeCount, int* databaseSize);
void displayEmployee(Employee* database, int currentEmployeeCount);
void searchEmployee(Employee* database, int currentEmployeeCount);
void updateEmployee(Employee* database, int currentEmployeeCount);
void removeEmployee(Employee* database, int* currentEmployeeCount);
void listAllEmployees(Employee* database, int currentEmployeeCount);

int main() {
    int choice;
    Employee* database = malloc(sizeof(Employee) * 10); // initially space for 10 employees
    int databaseSize = 10;
    int currentEmployeeCount = 0;

    do {
        printf("\nEmployee Management System\n");
        printf("1. Add Employee\n");
        printf("2. Display Employee\n");
        printf("3. Search Employee\n");
        printf("4. Update Employee\n");
        printf("5. Remove Employee\n");
        printf("6. List All Employees\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                database = addEmployee(database, &currentEmployeeCount, &databaseSize);
                break;
            case 2:
                displayEmployee(database, currentEmployeeCount);
                break;
            case 3:
                searchEmployee(database, currentEmployeeCount);
                break;
            case 4:
                updateEmployee(database, currentEmployeeCount);
                break;
            case 5:
                removeEmployee(database, &currentEmployeeCount);
                break;
            case 6:
                listAllEmployees(database, currentEmployeeCount);
                break;
            case 0:
                free(database);
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
                break;
        }
    } while (choice != 0);

    return 0;
}

Employee* addEmployee(Employee* database, int* currentEmployeeCount, int* databaseSize) {
    if(*currentEmployeeCount == *databaseSize) {
        *databaseSize *= 2;
        database = realloc(database, sizeof(Employee) * (*databaseSize));
    }

    printf("Enter Employee ID: ");
    scanf("%d", &database[*currentEmployeeCount].id);
    printf("Enter Name: ");
    scanf("%s", database[*currentEmployeeCount].name);
    printf("Enter Department: ");
    scanf("%s", database[*currentEmployeeCount].department);
    printf("Enter Position: ");
    scanf("%s", database[*currentEmployeeCount].position);
    printf("Enter Salary: ");
    scanf("%f", &database[*currentEmployeeCount].salary);

    (*currentEmployeeCount)++;

    return database;
}

void displayEmployee(Employee* database, int currentEmployeeCount) {
    int id;
    printf("Enter Employee ID to Display: ");
    scanf("%d", &id);

    for (int i = 0; i < currentEmployeeCount; i++) {
        if (database[i].id == id) {
            printf("ID: %d\n", database[i].id);
            printf("Name: %s\n", database[i].name);
            printf("Department: %s\n", database[i].department);
            printf("Position: %s\n", database[i].position);
            printf("Salary: %.2f\n", database[i].salary);
            return;
        }
    }

    printf("Employee not found!\n");
}

void searchEmployee(Employee* database, int currentEmployeeCount) {
    // You can extend this function to search by name or other fields as well
    int id;
    printf("Enter Employee ID to Search: ");
    scanf("%d", &id);

    for (int i = 0; i < currentEmployeeCount; i++) {
        if (database[i].id == id) {
            printf("Employee found!\n");
            return;
        }
    }

    printf("Employee not found!\n");
}

void updateEmployee(Employee* database, int currentEmployeeCount) {
    int id;
    printf("Enter Employee ID to Update: ");
    scanf("%d", &id);

    for (int i = 0; i < currentEmployeeCount; i++) {
        if (database[i].id == id) {
            // You can extend this to update other fields
            printf("Enter New Salary: ");
            scanf("%f", &database[i].salary);
            printf("Employee updated!\n");
            return;
        }
    }

    printf("Employee not found!\n");
}

void removeEmployee(Employee* database, int* currentEmployeeCount) {
    int id;
    printf("Enter Employee ID to Remove: ");
    scanf("%d", &id);

    for (int i = 0; i < *currentEmployeeCount; i++) {
        if (database[i].id == id) {
            for (int j = i; j < (*currentEmployeeCount) - 1; j++) {
                database[j] = database[j + 1];
            }

            (*currentEmployeeCount)--;
            printf("Employee removed!\n");
            return;
        }
    }

    printf("Employee not found!\n");
}

void listAllEmployees(Employee* database, int currentEmployeeCount) {
    for (int i = 0; i < currentEmployeeCount; i++) {
        printf("ID: %d, Name: %s, Department: %s, Position: %s, Salary: %.2f\n", 
               database[i].id, database[i].name, database[i].department, database[i].position, database[i].salary);
    }
}
