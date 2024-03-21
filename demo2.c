#include <stdio.h>
#include <stdlib.h>

// Define the structure for a student
typedef struct Student {
    int id;
    char name[50];
    float mathGrade;
    float englishGrade;
    float scienceGrade;
    float totalGrade;
    struct Student* next;
} Student;

// Function to create a new student node
Student* createStudent(int id, char name[], float mathGrade, float englishGrade, float scienceGrade) {
    Student* newStudent = (Student*)malloc(sizeof(Student));
    newStudent->id = id;
    strcpy(newStudent->name, name);
    newStudent->mathGrade = mathGrade;
    newStudent->englishGrade = englishGrade;
    newStudent->scienceGrade = scienceGrade;
    newStudent->totalGrade = mathGrade + englishGrade + scienceGrade;
    newStudent->next = NULL;
    return newStudent;
}

// Function to insert a student at the end of the linked list
void insertStudent(Student** head, int id, char name[], float mathGrade, float englishGrade, float scienceGrade) {
    Student* newStudent = createStudent(id, name, mathGrade, englishGrade, scienceGrade);
    if (*head == NULL) {
        *head = newStudent;
    } else {
        Student* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newStudent;
    }
}

// Function to display all students and their grades
void displayStudents(Student* head) {
    if (head == NULL) {
        printf("No students found.\n");
    } else {
        printf("ID\tName\tMath\tEnglish\tScience\tTotal\n");
        printf("----------------------------------------------\n");
        Student* temp = head;
        while (temp != NULL) {
            printf("%d\t%s\t%.2f\t%.2f\t%.2f\t%.2f\n", temp->id, temp->name, temp->mathGrade, temp->englishGrade, temp->scienceGrade, temp->totalGrade);
            temp = temp->next;
        }
    }
}

// Function to calculate the total grade and rank the students
void calculateTotalGradeAndRank(Student* head) {
    if (head == NULL) {
        printf("No students found.\n");
    } else {
        int rank = 1;
        Student* temp = head;
        while (temp != NULL) {
            temp->totalGrade = temp->mathGrade + temp->englishGrade + temp->scienceGrade;
            temp = temp->next;
        }
        
        // Sort the students based on total grade (descending order)
        Student* current = head;
        while (current != NULL) {
            Student* next = current->next;
            while (next != NULL) {
                if (current->totalGrade < next->totalGrade) {
                    // Swap the students
                    int tempId = current->id;
                    char tempName[50];
                    strcpy(tempName, current->name);
                    float tempMathGrade = current->mathGrade;
                    float tempEnglishGrade = current->englishGrade;
                    float tempScienceGrade = current->scienceGrade;
                    float tempTotalGrade = current->totalGrade;
                    
                    current->id = next->id;
                    strcpy(current->name, next->name);
                    current->mathGrade = next->mathGrade;
                    current->englishGrade = next->englishGrade;
                    current->scienceGrade = next->scienceGrade;
                    current->totalGrade = next->totalGrade;
                    
                    next->id = tempId;
                    strcpy(next->name, tempName);
                    next->mathGrade = tempMathGrade;
                    next->englishGrade = tempEnglishGrade;
                    next->scienceGrade = tempScienceGrade;
                    next->totalGrade = tempTotalGrade;
                }
                next = next->next;
            }
            current = current->next;
        }
        
        // Assign ranks to the students
        temp = head;
        while (temp != NULL) {
            #include <math.h> // Include the math.h header file for the roundf function

            if (temp != NULL) {
                temp->totalGrade = roundf((temp->mathGrade + temp->englishGrade + temp->scienceGrade) * 100) / 100;
            }
            temp->next = rank++;
            temp = temp->next;
        }
    }
}

// Function to free the memory allocated for the linked list
void freeMemory(Student* head) {
    Student* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    Student* head = NULL;
    int choice, id;
    char name[50];
    float mathGrade, englishGrade, scienceGrade;
    
    do {
        printf("\nStudent Grade Management System\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Calculate Total Grade and Rank\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter student ID: ");
                scanf("%d", &id);
                printf("Enter student name: ");
                scanf("%s", name);
                printf("Enter math grade: ");
                scanf("%f", &mathGrade);
                printf("Enter english grade: ");
                scanf("%f", &englishGrade);
                printf("Enter science grade: ");
                scanf("%f", &scienceGrade);
                insertStudent(&head, id, name, mathGrade, englishGrade, scienceGrade);
                break;
            case 2:
                displayStudents(head);
                break;
            case 3:
                calculateTotalGradeAndRank(head);
                printf("Total grade calculated and students ranked.\n");
                break;
            case 4:
                freeMemory(head);
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 4);
    
    return 0;
}