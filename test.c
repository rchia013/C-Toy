#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>


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
void saveToFile(Employee* database, int currentEmployeeCount);
Employee* loadFromFile(Employee* database, int* currentEmployeeCount, int* databaseSize);


int main() {
    int choice;
    Employee* database = malloc(sizeof(Employee) * 10); // initially space for 10 employees
    int databaseSize = 10;
    int currentEmployeeCount = 0;

    database = loadFromFile(database, &currentEmployeeCount, &databaseSize);

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

    saveToFile(database, *currentEmployeeCount); 

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
    char name[50];
    int id;
    int choice;

    printf("Search by ID or Name:\n");
    printf("1: ID\n");
    printf("2: Name\n");
    printf("Enter your choce: ");
    scanf("%d",&choice);


    switch(choice) {
        case 1:
            printf("Enter Employee ID to Search: ");
            scanf("%d", &id);

            for (int i = 0; i < currentEmployeeCount; i++) {
                if (database[i].id == id) {
                    printf("Employee found!\n");
                    return;
                }
            }
            break;
        case 2:
            printf("Enter Employee Name to Search: ");
            scanf("%s", &name);
            for (int i = 0; i < currentEmployeeCount; i++) {
                if (strcmp(database[i].name,name) == 0) {
                    printf("Employee found!\n");
                    return;
                }
            }
            break;          
    }

    printf("Employee not found!\n");
}

void updateEmployee(Employee* database, int currentEmployeeCount) {
    int id, choice;
    printf("Enter Employee ID to Update: ");
    scanf("%d", &id);

    for (int i = 0; i < currentEmployeeCount; i++) {
        if (database[i].id == id) {
            printf("Select field to update:\n");
            printf("1. Name\n");
            printf("2. Department\n");
            printf("3. Position\n");
            printf("4. Salary\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    printf("Enter New Name: ");
                    scanf("%s", database[i].name);
                    break;
                case 2:
                    printf("Enter New Department: ");
                    scanf("%s", database[i].department);
                    break;
                case 3:
                    printf("Enter New Position: ");
                    scanf("%s", database[i].position);
                    break;
                case 4:
                    printf("Enter New Salary: ");
                    scanf("%f", &database[i].salary);
                    break;
                default:
                    printf("Invalid choice!\n");
                    return;
            }

            printf("Employee updated!\n");

            saveToFile(database, currentEmployeeCount); 

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

            saveToFile(database, *currentEmployeeCount); 

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

void saveToFile(Employee* database, int currentEmployeeCount) {
    FILE* file = fopen("employees.csv", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    fprintf(file, "id,name,department,position,salary\n");
    for (int i = 0; i < currentEmployeeCount; i++) {
        fprintf(file, "%d,%s,%s,%s,%.2f\n", database[i].id, database[i].name, database[i].department, database[i].position, database[i].salary);
    }

    fclose(file);
    printf("h");
    printf("Data saved to employees.csv\n");
}

Employee* loadFromFile(Employee* database, int* currentEmployeeCount, int* databaseSize) {
    FILE* file = fopen("employees.csv", "r");
    if (file == NULL) {
        printf("No existing database found.\n");
        return database; // Return the existing pointer if no file is found
    }

    char line[200];
    fgets(line, sizeof(line), file); // Read the header

    while (fgets(line, sizeof(line), file) != NULL) {
        if (*currentEmployeeCount == *databaseSize) {
            *databaseSize *= 2;
            database = realloc(database, sizeof(Employee) * (*databaseSize));
        }

        sscanf(line, "%d,%49[^,],%49[^,],%49[^,],%f", &database[*currentEmployeeCount].id, database[*currentEmployeeCount].name, database[*currentEmployeeCount].department, database[*currentEmployeeCount].position, &database[*currentEmployeeCount].salary);
        (*currentEmployeeCount)++;
    }

    fclose(file);
    printf("Data loaded from employees.csv\n");

    return database;
}

void on_add_employee_button_clicked(GtkWidget *button, gpointer data) {
    // Code to add an employee
}

void on_display_employee_button_clicked(GtkWidget *button, gpointer data) {
    // Code to display an employee
}