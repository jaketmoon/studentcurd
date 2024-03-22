#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 建立学生信息的结构体
struct Student {
    int rollNumber;
    char name[50];
    float marks;
    struct Student* next;
};

// 添加学生信息
void addStudent(struct Student** head) {
    struct Student* newStudent = (struct Student*)malloc(sizeof(struct Student));
    if (newStudent == NULL) {
        printf("内存分配失败，无法添加学生记录。\n");
        return;
    }

    printf("输入学号： ");
    scanf("%d", &(newStudent->rollNumber));
    printf("输入姓名：");
    scanf("%s", newStudent->name);
    printf("输入成绩：");
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

    printf("学生记录添加成功。\n");
}

// 展示所有学生记录
void displayStudents(struct Student* head) {
    if (head == NULL) {
        printf("学生记录不存在。\n");
        return;
    }

    printf("学号\t姓名\t\t成绩\n");
    printf("----------------------------------\n");

    struct Student* current = head;
    while (current != NULL) {
        printf("%d\t\t%s\t\t%.2f\n", current->rollNumber, current->name, current->marks);
        current = current->next;
    }
}

// 通过学号寻找学生记录 
void searchByRollNumber(struct Student* head, int rollNumber) {
    if (head == NULL) {
        printf("学生记录不存在。\n");
        return;
    }

    struct Student* current = head;
    while (current != NULL) {
        if (current->rollNumber == rollNumber) {
            printf("学号\t姓名\t\t成绩\n");
            printf("----------------------------------\n");
            printf("%d\t\t%s\t\t%.2f\n", current->rollNumber, current->name, current->marks);
            return;
        }
        current = current->next;
    }

    printf("学号：%d的学生记录不存在。\n", rollNumber);
}

// 通过姓名寻找学生记录
void searchByName(struct Student* head, const char* name) {
    if (head == NULL) {
        printf("学生记录不存在。\n");
        return;
    }

    struct Student* current = head;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            printf("学号\t姓名\t\t成绩\n");
            printf("----------------------------------\n");
            printf("%d\t\t%s\t\t%.2f\n", current->rollNumber, current->name, current->marks);
            return;
        }
        current = current->next;
    }

    printf("姓名：%s的学生记录不存在。\n", name);
}

// 通过学号删除学生记录
void deleteByRollNumber(struct Student** head, int rollNumber) {
    if (*head == NULL) {
        printf("学生记录不存在\n");
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
            printf("学生记录成绩删除成功。\n");
            return;
        }
        previous = current;
        current = current->next;
    }

    printf("学号：%d的学生记录不存在。\n", rollNumber);
}

// 通过学号更新学生记录
void updateByRollNumber(struct Student* head, int rollNumber) {
    if (head == NULL) {
        printf("学生记录不存在。\n");
        return;
    }

    struct Student* current = head;
    while (current != NULL) {
        if (current->rollNumber == rollNumber) {
            printf("重新输入姓名：");
            scanf("%s", current->name);
            printf("重新输入成绩：");
            scanf("%f", &(current->marks));
            printf("学生记录更新成功。\n");
            return;
        }
        current = current->next;
    }

    printf("学号：%d的学生记录不存在。\n", rollNumber);
}

//释放分配给学生记录的内存
void freeMemory(struct Student* head) {
    struct Student* current = head;
    while (current != NULL) {
        struct Student* temp = current;
        current = current->next;
        free(temp);
    }
}

// 按学号进行排序
void sortByRollNumber(struct Student** head) {
    if (*head == NULL) {
        printf("学生记录不存在\n");
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

    printf("学生记录已按学号排序。\n");
}

// 按姓名进行排序
void sortByName(struct Student** head) {
    if (*head == NULL) {
        printf("学生记录不存在。\n");
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

    printf("学生记录已按姓名排序。\n");
}

// 按成绩进行升序排序
void sortByMarks(struct Student** head) {
    if (*head == NULL) {
        printf("学生记录不存在。\n");
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

    printf("学生记录已按成绩升序排序。\n");
}

// 按总成绩降序排序
void sortByTotalMarks(struct Student** head) {
    if (*head == NULL) {
        printf("学生记录不存在。\n");
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

    printf("学生记录已按总成绩降序排序。\n");
}

// 学生成绩统计信息
void calculateStatistics(struct Student* head) {
    if (head == NULL) {
        printf("学生记录不存在。\n");
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

    printf("学生总数：%d\n", count);
    printf("总分： %.2f\n", totalMarks);
    printf("平均分： %.2f\n", averageMarks);
    printf("最高分： %.2f\n", highestMarks);
    printf("最低分： %.2f\n", lowestMarks);
}
int main(){
    struct Student* head = NULL;
    int choice;
    int rollNumber;
    char name[50];
    float marks;
    do {
        printf("\n学生成绩管理系统\n");
        printf("1.添加学生信息\n");
        printf("2. 展示所有学生记录\n");
        printf("3. 通过学号寻找学生记录\n");
        printf("4. 通过姓名寻找学生记录\n");
        printf("5. 通过学号删除学生记录\n");
        printf("6. 通过学号更新学生记录\n");
        printf("7. 按学号进行排序\n");
        printf("8. 按姓名进行排序\n");
        printf("9. 按成绩进行升序排序\n");
        printf("10. 按总成绩降序排序\n");
        printf("11. 学生成绩统计信息\n");
        printf("12. 退出\n");
        printf("输入你的操作：");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                addStudent(&head);
                break;
            case 2:
                displayStudents(head);
                break;
            case 3:
                printf("输入查找的学号：");
                scanf("%d", &rollNumber);
                searchByRollNumber(head, rollNumber);
                break;
            case 4:
                printf("输入查找的姓名：");
                scanf("%s", name);
                searchByName(head, name);
                break;
            case 5:
                printf("输入删除的学号：");
                scanf("%d", &rollNumber);
                deleteByRollNumber(&head, rollNumber);
                break;
            case 6:
                printf("输入更新的学号：");
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
                printf("退出程序中...\n");
                break;
            default:
                printf("无效操作，请再试一次。\n");
        }
    } while (choice != 12);
}