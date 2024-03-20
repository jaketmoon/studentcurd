#include <stdio.h>
#include <stdlib.h>

// Define the structure for student information
typedef struct Student {
    int id;
    char name[50];
    struct Student* next;
} Student;

// Function to add a new student to the linked list
void addStudent(Student** head, int id, const char* name) {
    // Create a new student node
    Student* newStudent = (Student*)malloc(sizeof(Student));
    newStudent->id = id;
    strcpy(newStudent->name, name);
    newStudent->next = NULL;

    // If the linked list is empty, make the new student the head
    if (*head == NULL) {
        *head = newStudent;
    }
    // Otherwise, add the new student to the end of the list
    else {
        Student* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newStudent;
    }
}

// Function to delete a student from the linked list
void deleteStudent(Student** head, int id) {
    Student* current = *head;
    Student* prev = NULL;

    // Traverse the linked list to find the student with the given ID
    while (current != NULL && current->id != id) {
        prev = current;
        current = current->next;
    }

    // If the student is found, remove it from the list
    if (current != NULL) {
        // If the student is the head, update the head pointer
        if (prev == NULL) {
            *head = current->next;
        }
        // Otherwise, update the previous node's next pointer
        else {
            prev->next = current->next;
        }
        free(current);
    }
}

// Function to display all students in the linked list
void displayStudents(Student* head) {
    Student* current = head;

    printf("Student Information:\n");
    while (current != NULL) {
        printf("ID: %d, Name: %s\n", current->id, current->name);
        current = current->next;
    }
}

// Function to free the memory allocated for the linked list
void freeList(Student** head) {
    Student* current = *head;
    Student* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    *head = NULL;
}

int main() {
    Student* head = NULL;

    // Add some sample students
    addStudent(&head, 1, "John Doe");
    addStudent(&head, 2, "Jane Smith");
    addStudent(&head, 3, "Alice Johnson");

    // Display all students
    displayStudents(head);

    // Delete a student
    deleteStudent(&head, 2);

    // Display all students after deletion
    displayStudents(head);

    // Free the memory allocated for the linked list
    freeList(&head);

    return 0;
}