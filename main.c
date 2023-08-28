#include <ctype.h>
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

typedef struct BSTNode {
    Employee *employee;
    struct BSTNode *left;
    struct BSTNode *right;
} BSTNode;

Employee *addEmployee(Employee *database, int *currentEmployeeCount, int *databaseSize);
void displayEmployee(Employee *database, int currentEmployeeCount, int ID);
void searchEmployee(Employee *database, int currentEmployeeCount);
void updateEmployee(Employee *database, int currentEmployeeCount);
void removeEmployee(Employee *database, int *currentEmployeeCount);
void listAllEmployees(Employee *database, int currentEmployeeCount);
void saveToFile(Employee *database, int currentEmployeeCount);
Employee *loadFromFile(Employee *database, int *currentEmployeeCount, int *databaseSize);
int isUniqueID(Employee *database, int currentEmployeeCount, int id);
int isAlphaString(const char *str);
float getSalary();
BSTNode *insertBSTNode(BSTNode *root, Employee *employee, int sortBySalary,int order);
void inOrderPrint(BSTNode *root);
void printSortedEmployees(Employee *database, int currentEmployeeCount, int sortBySalary, int order);

int main() {
    char inputBuffer[100];
    int choice;
    Employee *database = malloc(sizeof(Employee) * 10); // initially space for 10 employees
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
        printf("7. Sort and Print Employees\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        // fgets reads a line from the input and stores it in a buffer, and then sscanf parses the required value from that buffer.
        // This ensures that the input doesn't exceed the buffer size and provides more flexibility in handling incorrect input.
        fgets(inputBuffer, sizeof(inputBuffer), stdin);
        sscanf(inputBuffer, "%d", &choice);

        switch (choice) {
        case 1:
            database = addEmployee(database, &currentEmployeeCount, &databaseSize);
            break;
        case 2:
            displayEmployee(database, currentEmployeeCount, 0);
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
        case 7:
            printf("Sort by Name or Salary:\n");
            printf("1: Name\n");
            printf("2: Salary\n");
            printf("Enter your choice: ");
            fgets(inputBuffer, sizeof(inputBuffer), stdin);
            sscanf(inputBuffer, "%d", &choice);
            int order;
            printf("Ascending(1) or Descending(2)?\n");
            printf("Enter your choice: ");
            fgets(inputBuffer, sizeof(inputBuffer), stdin);
            sscanf(inputBuffer, "%d", &order);
            printSortedEmployees(database, currentEmployeeCount, choice == 2, order);
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

Employee *addEmployee(Employee *database, int *currentEmployeeCount, int *databaseSize) {
    char inputBuffer[100];
    if (*currentEmployeeCount == *databaseSize) {
        *databaseSize *= 2;
        database = realloc(database, sizeof(Employee) * (*databaseSize));
    }

    int id;
    // printf("Enter Employee ID (Numbers only): ");
    // fgets(inputBuffer, sizeof(inputBuffer), stdin);
    // if(sscanf(inputBuffer, "%d", &id) == 1){
    //     if (!isUniqueID(database, *currentEmployeeCount, id)) {
    //         printf("Error: ID must be unique! Existing employee details: \n");
    //         displayEmployee(database, *currentEmployeeCount, id);
    //         return database;
    //     }
    //     database[*currentEmployeeCount].id = id;
    // }

    // sscanf(inputBuffer, "%f", &salary) == 1

    char newlineCheck;
    do {
        printf("Enter Employee ID (Integer only): ");
        fgets(inputBuffer, sizeof(inputBuffer), stdin);

        if (sscanf(inputBuffer, "%d%c", &id, &newlineCheck) == 2 && newlineCheck == '\n') {
            if (!isUniqueID(database, *currentEmployeeCount, id)) {
                printf("Error: ID must be unique! Existing employee details: \n");
                displayEmployee(database, *currentEmployeeCount, id);
                return database;
            }
            break; // Exit the loop if a valid integer ID has been found.
        } else {
            printf("Error: ID can only be an Integer! Please try again.\n");
        }
    } while (1);

    do {
        printf("Enter Name (alphabetical characters only): ");
        fgets(inputBuffer, sizeof(inputBuffer), stdin);
        sscanf(inputBuffer, "%s", database[*currentEmployeeCount].name);
    } while (!isAlphaString(database[*currentEmployeeCount].name));

    do {
        printf("Enter Department (alphabetical characters only): ");
        fgets(inputBuffer, sizeof(inputBuffer), stdin);
        sscanf(inputBuffer, "%s", database[*currentEmployeeCount].department);
    } while (!isAlphaString(database[*currentEmployeeCount].department));

    do {
        printf("Enter Position (alphabetical characters only): ");
        fgets(inputBuffer, sizeof(inputBuffer), stdin);
        sscanf(inputBuffer, "%s", database[*currentEmployeeCount].position);
    } while (!isAlphaString(database[*currentEmployeeCount].position));

    database[*currentEmployeeCount].salary = getSalary();

    (*currentEmployeeCount)++;

    saveToFile(database, *currentEmployeeCount);

    return database;
}

void displayEmployee(Employee *database, int currentEmployeeCount, int ID) {
    char inputBuffer[100];
    int id;
    if (ID == 0) {
        printf("Enter Employee ID to Display: ");
        fgets(inputBuffer, sizeof(inputBuffer), stdin);
        sscanf(inputBuffer, "%d", &id);
    } else {
        id = ID;
    }

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

void searchEmployee(Employee *database, int currentEmployeeCount) {
    char inputBuffer[100];
    char name[50];
    int id;
    int choice;

    printf("Search by ID or Name:\n");
    printf("1: ID\n");
    printf("2: Name\n");
    printf("Enter your choce: ");
    fgets(inputBuffer, sizeof(inputBuffer), stdin);
    sscanf(inputBuffer, "%d", &choice);

    switch (choice) {
    case 1:
        printf("Enter Employee ID to Search: ");
        fgets(inputBuffer, sizeof(inputBuffer), stdin);
        sscanf(inputBuffer, "%d", &id);

        for (int i = 0; i < currentEmployeeCount; i++) {
            if (database[i].id == id) {
                printf("Employee found!\n");
                return;
            }
        }
        break;
    case 2:
        printf("Enter Employee Name to Search: ");
        fgets(inputBuffer, sizeof(inputBuffer), stdin);
        sscanf(inputBuffer, "%s", &name);
        for (int i = 0; i < currentEmployeeCount; i++) {
            // NOTE
            if (strncmp(database[i].name, name, sizeof(database[i].name)) == 0) {
                printf("Employee found!\n");
                return;
            }
        }
        break;
    }

    printf("Employee not found!\n");
}

void updateEmployee(Employee *database, int currentEmployeeCount) {
    char inputBuffer[100];
    int id, choice;
    printf("Enter Employee ID to Update: ");
    fgets(inputBuffer, sizeof(inputBuffer), stdin);
    sscanf(inputBuffer, "%d", &id);

    for (int i = 0; i < currentEmployeeCount; i++) {
        if (database[i].id == id) {
            printf("Select field to update:\n");
            printf("1. Name\n");
            printf("2. Department\n");
            printf("3. Position\n");
            printf("4. Salary\n");
            printf("Enter your choice: ");
            fgets(inputBuffer, sizeof(inputBuffer), stdin);
            sscanf(inputBuffer, "%d", &choice);

            switch (choice) {
            case 1:
                printf("Enter New Name: ");
                fgets(inputBuffer, sizeof(inputBuffer), stdin);
                sscanf(inputBuffer, "%s", database[i].name);
                break;
            case 2:
                printf("Enter New Department: ");
                fgets(inputBuffer, sizeof(inputBuffer), stdin);
                sscanf(inputBuffer, "%s", database[i].department);
                break;
            case 3:
                printf("Enter New Position: ");
                fgets(inputBuffer, sizeof(inputBuffer), stdin);
                sscanf(inputBuffer, "%s", database[i].position);
                break;
            case 4:
                printf("Enter New Salary: ");
                fgets(inputBuffer, sizeof(inputBuffer), stdin);
                sscanf(inputBuffer, "%f", &database[i].salary);
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

void removeEmployee(Employee *database, int *currentEmployeeCount) {
    char inputBuffer[100];
    int id;
    printf("Enter Employee ID to Remove: ");
    fgets(inputBuffer, sizeof(inputBuffer), stdin);
    sscanf(inputBuffer, "%d", &id);

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

void listAllEmployees(Employee *database, int currentEmployeeCount) {
    for (int i = 0; i < currentEmployeeCount; i++) {
        printf("ID: %d, Name: %s, Department: %s, Position: %s, Salary: %.2f\n",
               database[i].id, database[i].name, database[i].department, database[i].position, database[i].salary);
    }
}

void saveToFile(Employee *database, int currentEmployeeCount) {
    FILE *file = fopen("employees.csv", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    fprintf(file, "id,name,department,position,salary\n");
    for (int i = 0; i < currentEmployeeCount; i++) {
        fprintf(file, "%d,%s,%s,%s,%.2f\n", database[i].id, database[i].name, database[i].department, database[i].position, database[i].salary);
    }

    fclose(file);
    printf("Data saved to employees.csv\n");
}

Employee *loadFromFile(Employee *database, int *currentEmployeeCount, int *databaseSize) {
    FILE *file = fopen("employees.csv", "r");
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

        sscanf(line, "%d,%49[^,],   %49[^,],%49[^,],%f", &database[*currentEmployeeCount].id, database[*currentEmployeeCount].name, database[*currentEmployeeCount].department, database[*currentEmployeeCount].position, &database[*currentEmployeeCount].salary);
        (*currentEmployeeCount)++;
    }

    fclose(file);
    printf("Data loaded from employees.csv\n");

    return database;
}

// Function to check if an ID is unique
int isUniqueID(Employee *database, int currentEmployeeCount, int id) {
    for (int i = 0; i < currentEmployeeCount; i++) {
        if (database[i].id == id) {
            return 0; // Not unique
        }
    }
    return 1; // Unique
}

// Function to check if a string contains only alphabetical characters
int isAlphaString(const char *str) {
    for (int i = 0; str[i]; i++) {
        if (!isalpha(str[i]) && str[i] != ' ') {
            printf("Error: Only alphabetical characters allowed\n");
            return 0; // Contains non-alphabetical character
        }
    }
    return 1; // All characters are alphabetical
}

// Function to check if input is a float
float getSalary() {
    char inputBuffer[100];
    float salary;

    do {
        printf("Enter Salary: ");
        fgets(inputBuffer, sizeof(inputBuffer), stdin);

        if (sscanf(inputBuffer, "%f", &salary) == 1) {
            return salary;
        } else {
            printf("Error: Salary must be a float value! Please try again.\n");
        }
    } while (1);
}

BSTNode *insertBSTNode(BSTNode *root, Employee *employee, int sortBySalary, int order) {
    if (root == NULL) {
        root = (BSTNode *)malloc(sizeof(BSTNode));
        root->employee = employee;
        root->left = root->right = NULL;
        return root;
    }
    if (order == 1) {
        if (sortBySalary) {
            if (employee->salary < root->employee->salary)
                root->left = insertBSTNode(root->left, employee, sortBySalary,order);
            else
                root->right = insertBSTNode(root->right, employee, sortBySalary,order);
        } else {
            if (strcmp(employee->name, root->employee->name) < 0)
                root->left = insertBSTNode(root->left, employee, sortBySalary,order);
            else
                root->right = insertBSTNode(root->right, employee, sortBySalary,order);
        }
    } else {
        if (sortBySalary) {
            if (employee->salary > root->employee->salary)
                root->left = insertBSTNode(root->left, employee, sortBySalary,order);
            else
                root->right = insertBSTNode(root->right, employee, sortBySalary,order);
        } else {
            if (strcmp(employee->name, root->employee->name) > 0)
                root->left = insertBSTNode(root->left, employee, sortBySalary,order);
            else
                root->right = insertBSTNode(root->right, employee, sortBySalary,order);
        }
    }

    return root;
}

void inOrderPrint(BSTNode *root) {
    if (root == NULL)
        return;
    inOrderPrint(root->left);
    printf("ID: %d, Name: %s, Department: %s, Position: %s, Salary: %.2f\n",
           root->employee->id, root->employee->name, root->employee->department, root->employee->position, root->employee->salary);
    inOrderPrint(root->right);
}

void printSortedEmployees(Employee *database, int currentEmployeeCount, int sortBySalary, int order) {
    BSTNode *root = NULL;
    for (int i = 0; i < currentEmployeeCount; i++) {
        root = insertBSTNode(root, &database[i], sortBySalary, order);
    }

    inOrderPrint(root);
}
