#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the structure for student record
struct Student {
    int rollNumber;
    char name[50];
    float marks;
    struct Student* next;
};

// Function to add a new student record
void addStudent(struct Student** head) {
    struct Student* newStudent = (struct Student*)malloc(sizeof(struct Student));
    if (newStudent == NULL) {
        printf("Memory allocation failed. Unable to add student record.\n");
        return;
    }

    printf("Enter roll number: ");
    scanf("%d", &(newStudent->rollNumber));
    printf("Enter name: ");
    scanf("%s", newStudent->name);
    printf("Enter marks: ");
    scanf("%f", &(newStudent->marks));

    newStudent->next = NULL;

    if (*head == NULL) {
        *head = newStudent;
    } else {
        struct Student* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newStudent;
    }

    printf("Student record added successfully.\n");
}

// Function to display all student records
void displayStudents(struct Student* head) {
    if (head == NULL) {
        printf("No student records found.\n");
        return;
    }

    printf("Roll Number\tName\t\tMarks\n");
    printf("----------------------------------\n");

    struct Student* current = head;
    while (current != NULL) {
        printf("%d\t\t%s\t\t%.2f\n", current->rollNumber, current->name, current->marks);
        current = current->next;
    }
}

// Function to search student record by roll number
void searchByRollNumber(struct Student* head, int rollNumber) {
    if (head == NULL) {
        printf("No student records found.\n");
        return;
    }

    struct Student* current = head;
    while (current != NULL) {
        if (current->rollNumber == rollNumber) {
            printf("Roll Number\tName\t\tMarks\n");
            printf("----------------------------------\n");
            printf("%d\t\t%s\t\t%.2f\n", current->rollNumber, current->name, current->marks);
            return;
        }
        current = current->next;
    }

    printf("Student record not found for roll number %d.\n", rollNumber);
}

// Function to search student record by name
void searchByName(struct Student* head, const char* name) {
    if (head == NULL) {
        printf("No student records found.\n");
        return;
    }

    struct Student* current = head;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            printf("Roll Number\tName\t\tMarks\n");
            printf("----------------------------------\n");
            printf("%d\t\t%s\t\t%.2f\n", current->rollNumber, current->name, current->marks);
            return;
        }
        current = current->next;
    }

    printf("Student record not found for name %s.\n", name);
}

// Function to delete student record by roll number
void deleteByRollNumber(struct Student** head, int rollNumber) {
    if (*head == NULL) {
        printf("No student records found.\n");
        return;
    }

    struct Student* current = *head;
    struct Student* previous = NULL;

    while (current != NULL) {
        if (current->rollNumber == rollNumber) {
            if (previous == NULL) {
                *head = current->next;
            } else {
                previous->next = current->next;
            }
            free(current);
            printf("Student record deleted successfully.\n");
            return;
        }
        previous = current;
        current = current->next;
    }

    printf("Student record not found for roll number %d.\n", rollNumber);
}

// Function to update student record by roll number
void updateByRollNumber(struct Student* head, int rollNumber) {
    if (head == NULL) {
        printf("No student records found.\n");
        return;
    }

    struct Student* current = head;
    while (current != NULL) {
        if (current->rollNumber == rollNumber) {
            printf("Enter new name: ");
            scanf("%s", current->name);
            printf("Enter new marks: ");
            scanf("%f", &(current->marks));
            printf("Student record updated successfully.\n");
            return;
        }
        current = current->next;
    }

    printf("Student record not found for roll number %d.\n", rollNumber);
}

// Function to free the memory allocated for student records
void freeMemory(struct Student* head) {
    struct Student* current = head;
    while (current != NULL) {
        struct Student* temp = current;
        current = current->next;
        free(temp);
    }
}

// Function to sort student records by roll number
void sortByRollNumber(struct Student** head) {
    if (*head == NULL) {
        printf("No student records found.\n");
        return;
    }

    int swapped;
    struct Student* current;
    struct Student* last = NULL;

    do {
        swapped = 0;
        current = *head;

        while (current->next != last) {
            if (current->rollNumber > current->next->rollNumber) {
                struct Student* temp = current;
                current = current->next;
                temp->next = current->next;
                current->next = temp;
                swapped = 1;
            }
            current = current->next;
        }
        last = current;
    } while (swapped);

    printf("Student records sorted by roll number.\n");
}

// Function to sort student records by name
void sortByName(struct Student** head) {
    if (*head == NULL) {
        printf("No student records found.\n");
        return;
    }

    int swapped;
    struct Student* current;
    struct Student* last = NULL;

    do {
        swapped = 0;
        current = *head;

        while (current->next != last) {
            if (strcmp(current->name, current->next->name) > 0) {
                struct Student* temp = current;
                current = current->next;
                temp->next = current->next;
                current->next = temp;
                swapped = 1;
            }
            current = current->next;
        }
        last = current;
    } while (swapped);

    printf("Student records sorted by name.\n");
}

// Function to sort student records by marks in ascending order
void sortByMarks(struct Student** head) {
    if (*head == NULL) {
        printf("No student records found.\n");
        return;
    }

    int swapped;
    struct Student* current;
    struct Student* last = NULL;

    do {
        swapped = 0;
        current = *head;

        while (current->next != last) {
            if (current->marks > current->next->marks) {
                struct Student* temp = current;
                current = current->next;
                temp->next = current->next;
                current->next = temp;
                swapped = 1;
            }
            current = current->next;
        }
        last = current;
    } while (swapped);

    printf("Student records sorted by marks in ascending order.\n");
}

// Function to sort student records by total marks in descending order
void sortByTotalMarks(struct Student** head) {
    if (*head == NULL) {
        printf("No student records found.\n");
        return;
    }

    int swapped;
    struct Student* current;
    struct Student* last = NULL;

    do {
        swapped = 0;
        current = *head;

        while (current->next != last) {
            float currentTotalMarks = current->marks;
            struct Student* next = current->next;
            while (next != NULL) {
                if (next->marks > currentTotalMarks) {
                    currentTotalMarks = next->marks;
                    struct Student* temp = current;
                    current = next;
                    temp->next = current->next;
                    current->next = temp;
                    swapped = 1;
                }
                next = next->next;
            }
            current = current->next;
        }
        last = current;
    } while (swapped);

    printf("Student records sorted by total marks in descending order.\n");
}

// Function to calculate student grade statistics
void calculateStatistics(struct Student* head) {
    if (head == NULL) {
        printf("No student records found.\n");
        return;
    }

    int count = 0;
    float totalMarks = 0;
    float highestMarks = head->marks;
    float lowestMarks = head->marks;

    struct Student* current = head;
    while (current != NULL) {
        count++;
        totalMarks += current->marks;

        if (current->marks > highestMarks) {
            highestMarks = current->marks;
        }

        if (current->marks < lowestMarks) {
            lowestMarks = current->marks;
        }

        current = current->next;
    }

    float averageMarks = totalMarks / count;

    printf("Total number of students: %d\n", count);
    printf("Total marks: %.2f\n", totalMarks);
    printf("Average marks: %.2f\n", averageMarks);
    printf("Highest marks: %.2f\n", highestMarks);
    printf("Lowest marks: %.2f\n", lowestMarks);
}
int main(){
    struct Student* head = NULL;
    int choice;
    int rollNumber;
    char name[50];
    float marks;
    do {
        printf("\nStudent Record Management System\n");
        printf("1. Add Student Record\n");
        printf("2. Display Student Records\n");
        printf("3. Search Student Record by Roll Number\n");
        printf("4. Search Student Record by Name\n");
        printf("5. Delete Student Record by Roll Number\n");
        printf("6. Update Student Record by Roll Number\n");
        printf("7. Sort Student Records by Roll Number\n");
        printf("8. Sort Student Records by Name\n");
        printf("9. Sort Student Records by Marks in Ascending Order\n");
        printf("10. Sort Student Records by Total Marks in Descending Order\n");
        printf("11. Calculate Student Grade Statistics\n");
        printf("12. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                addStudent(&head);
                break;
            case 2:
                displayStudents(head);
                break;
            case 3:
                printf("Enter roll number to search: ");
                scanf("%d", &rollNumber);
                searchByRollNumber(head, rollNumber);
                break;
            case 4:
                printf("Enter name to search: ");
                scanf("%s", name);
                searchByName(head, name);
                break;
            case 5:
                printf("Enter roll number to delete: ");
                scanf("%d", &rollNumber);
                deleteByRollNumber(&head, rollNumber);
                break;
            case 6:
                printf("Enter roll number to update: ");
                scanf("%d", &rollNumber);
                updateByRollNumber(head, rollNumber);
                break;
            case 7:
                sortByRollNumber(&head);
                break;
            case 8:
                sortByName(&head);
                break;
            case 9:
                sortByMarks(&head);
                break;
            case 10:
                sortByTotalMarks(&head);
                break;
            case 11:
                calculateStatistics(head);
                break;
            case 12:
                freeMemory(head);
                printf("Exiting from the program...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 12);
}