#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

// 建立学生信息的结构体
struct Student {
	int rollNumber;
	char name[50];
	float mark1;
	float mark2;
	float marks;
	struct Student *next;
};
void printCenter(char* text) {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	int columns;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;

	int padding = (columns - strlen(text)) / 2;
	for (int i = 0; i < padding; i++) {
		printf(" ");
	}
	printf("%s\n", text);
}
void printCenterContinue(char* text) {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	int columns;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;

	int padding = (columns - strlen(text)) / 2;
	for (int i = 0; i < padding; i++) {
		printf(" ");
	}
	printf("%s", text);
}


int color(int col)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), col);
	return 0;
}
// 添加学生信息
void addStudent(struct Student **head) {
	struct Student *newStudent = (struct Student *)malloc(sizeof(struct Student));

	if (newStudent == NULL) {
		printCenter("内存分配失败，无法添加学生记录.");
		return;
	}

	printCenterContinue("输入学号： ");
	scanf("%d", &(newStudent->rollNumber));
	printCenterContinue("输入姓名：");
	scanf("%s", newStudent->name);
	printCenterContinue("输入学科1成绩：");
	scanf("%f", &(newStudent->mark1));
	printCenterContinue("输入学科2成绩：");
	scanf("%f", &(newStudent->mark2));
	newStudent->marks = newStudent->mark1 + newStudent->mark2;
	newStudent->next = NULL;

	if (*head == NULL) {
		*head = newStudent;

	} else {
		struct Student *current = *head;
		while (current->next != NULL) {
			current = current->next;
		}
		current->next = newStudent;
		current = current->next;
		current->next = NULL;
	}
}

// 展示所有学生记录
void displayStudents(struct Student *head) {

	if (head == NULL) {
		printCenter("学生记录不存在。");
		return;
	}

	printf("				学号\t\t姓名\t\t学科1\t学科2\t总成绩\n");
	printf("			-----------------------------------------------------------------\n");

	struct Student *current = head;

	while (current != NULL) {
		printf("				%d\t%s\t\t%.2f\t%.2f\t%.2f\n", current->rollNumber, current->name, current->mark1, current->mark2, current->marks);
		current = current->next;
	}
}

// 通过学号寻找学生记录
void searchByRollNumber(struct Student *head, int rollNumber) {

	if (head == NULL) {
		printCenter("学生记录不存在。\n");
		return;
	}

	struct Student *current = head;

	while (current != NULL) {
		if (current->rollNumber == rollNumber) {
			printf("				学号\t\t姓名\t\t学科1\t学科2\t总成绩\n");
			printf("			-----------------------------------------------------------------\n");

			printf("				%d\t%s\t\t%.2f\t%.2f\t%.2f\n", current->rollNumber, current->name, current->mark1, current->mark2, current->marks);
			return;
		}
		current = current->next;
	}

	printf("				学号：%d的学生记录不存在。", rollNumber);
}

// 通过姓名寻找学生记录
void searchByName(struct Student *head, const char *name) {

	if (head == NULL) {
		printCenter("学生记录不存在。");
		return;
	}

	struct Student *current = head;

	while (current != NULL) {
		if (strcmp(current->name, name) == 0) {
			printf("				学号\t\t姓名\t\t学科1\t学科2\t总成绩\n");
			printf("			-----------------------------------------------------------------\n");

			printf("				%d\t%s\t\t%.2f\t%.2f\t%.2f\n", current->rollNumber, current->name, current->mark1, current->mark2, current->marks);
			return;
		}
		current = current->next;
	}

	printf("						姓名：%s的学生记录不存在。\n", name);
}

// 通过学号删除学生记录
void deleteByRollNumber(struct Student **head, int rollNumber) {

	if (*head == NULL) {
		printCenter("学生记录不存在");
		return;
	}

	struct Student *current = *head;
	struct Student *previous = NULL;

	while (current != NULL) {

		if (current->rollNumber == rollNumber) {
			if (previous == NULL) {
				*head = current->next;
			} else {
				previous->next = current->next;
			}
			free(current);
			printCenter("学生记录成绩删除成功。");
			return;
		}
		previous = current;
		current = current->next;
	}

	printf("						学号：%d的学生记录不存在。\n", rollNumber);
}

// 通过学号更新学生记录
void updateByRollNumber(struct Student *head, int rollNumber) {

	if (head == NULL) {
		printCenter("学生记录不存在。");
		return;
	}

	struct Student *current = head;

	while (current != NULL) {

		if (current->rollNumber == rollNumber) {
			printCenterContinue("重新输入姓名：");
			scanf("%s", current->name);
			printCenterContinue("重新输入学科1成绩：");
			scanf("%f", &(current->mark1));
			printCenterContinue("重新输入学科2成绩：");
			scanf("%f", &(current->mark2));
			current->marks = current->mark1 + current->mark2;
			
			printCenter("学生记录更新成功。");
			return;
		}
		current = current->next;
	}

	printf("						学号：%d的学生记录不存在。\n", rollNumber);
}

//释放分配给学生记录的内存
void freeMemory(struct Student *head) {
	struct Student *current = head;

	while (current != NULL) {
		struct Student *temp = current;
		current = current->next;
		free(temp);
	}
}

// 按学号进行排序
void sortByRollNumber(struct Student **head) {

		if (*head == NULL || (*head)->next == NULL) {
			printCenter("学生记录不存在或只有一个学生。");
			return;
		}

		int swapped;
		struct Student* temp;
		struct Student* current = NULL;

		do {
			swapped = 0;
			temp = *head;

			while (temp->next != current) {
				if (temp->rollNumber > temp->next->rollNumber) {
					float tempMarks = temp->marks;
					float tempMark1 = temp->mark1;
					float tempMark2 = temp->mark2;
					char tempname[50];
					int tempnum = temp->rollNumber;
					strcpy(tempname, temp->name);

					temp->marks = temp->next->marks;
					temp->next->marks = tempMarks;
					temp->mark1 = temp->next->mark1;
					temp->next->mark1 = tempMark1;
					temp->mark2 = temp->next->mark2;
					temp->next->mark2 = tempMark2;

					temp->rollNumber = temp->next->rollNumber;
					temp->next->rollNumber = tempnum;

					strcpy(temp->name, temp->next->name);
					strcpy(temp->next->name, tempname);

					swapped = 1;
				}
				temp = temp->next;
			}
			current = temp;
		} while (swapped);

		//printf("学生记录已按成绩升序排序。\n");
	}


// 按姓名进行排序
void sortByname(struct Student** head) {
	if (*head == NULL || (*head)->next == NULL) {
		printCenter("学生记录不存在或只有一个学生。");
		return;
	}

	int swapped;
	struct Student* temp;
	struct Student* current = NULL;

	do {
		swapped = 0;
		temp = *head;

		while (temp->next != current) {
			if (strcmp(temp->name , temp->next->name)>0) {
				float tempMarks = temp->marks;
				float tempMark1 = temp->mark1;
				float tempMark2 = temp->mark2;
				char tempname[50];
				int tempnum = temp->rollNumber;
				strcpy(tempname, temp->name);

				temp->marks = temp->next->marks;
				temp->next->marks = tempMarks;
				temp->mark1 = temp->next->mark1;
				temp->next->mark1 = tempMark1;
				temp->mark2 = temp->next->mark2;
				temp->next->mark2 = tempMark2;

				temp->rollNumber = temp->next->rollNumber;
				temp->next->rollNumber = tempnum;

				strcpy(temp->name, temp->next->name);
				strcpy(temp->next->name, tempname);

				swapped = 1;
			}
			temp = temp->next;
		}
		current = temp;
	} while (swapped);

	//printCenter("学生记录已按成绩升序排序。\n");
}

void sortByMarks(struct Student** head) {
	if (*head == NULL || (*head)->next == NULL) {
		printCenter("学生记录不存在或只有一个学生。");
		return;
	}

	int swapped;
	struct Student* temp;
	struct Student* current = NULL;

	do {
		swapped = 0;
		temp = *head;

		while (temp->next != current) {
			if (temp->marks > temp->next->marks) {
				float tempMarks = temp->marks;
				float tempMark1 = temp->mark1;
				float tempMark2 = temp->mark2;
				char tempname[50];
				int tempnum = temp->rollNumber;
				strcpy(tempname, temp->name);

				temp->marks = temp->next->marks;
				temp->next->marks = tempMarks;
				temp->mark1 = temp->next->mark1;
				temp->next->mark1 = tempMark1;
				temp->mark2 = temp->next->mark2;
				temp->next->mark2 = tempMark2;

				temp->rollNumber = temp->next->rollNumber;
				temp->next->rollNumber = tempnum;

				strcpy(temp->name, temp->next->name);
				strcpy(temp->next->name, tempname);

				swapped = 1;
			}
			temp = temp->next;
		}
		current = temp;
	} while (swapped);

	//printCenter("学生记录已按成绩升序排序。\n");
}


// 按成绩降序排序
void sortByTotalMarks(struct Student **head) {

		if (*head == NULL || (*head)->next == NULL) {
			printCenter("学生记录不存在或只有一个学生。");
			return;
		}

		int swapped;
		struct Student* temp;
		struct Student* current = NULL;

		do {
			swapped = 0;
			temp = *head;

			while (temp->next != current) {
				if (temp->marks < temp->next->marks) {
					float tempMarks = temp->marks;
					float tempMark1 = temp->mark1;
					float tempMark2 = temp->mark2;
					char tempname[50];
					int tempnum = temp->rollNumber;
					strcpy(tempname, temp->name);

					temp->marks = temp->next->marks;
					temp->next->marks = tempMarks;
					temp->mark1 = temp->next->mark1;
					temp->next->mark1 = tempMark1;
					temp->mark2 = temp->next->mark2;
					temp->next->mark2 = tempMark2;

					temp->rollNumber = temp->next->rollNumber;
					temp->next->rollNumber = tempnum;

					strcpy(temp->name, temp->next->name);
					strcpy(temp->next->name, tempname);

					swapped = 1;
				}
				temp = temp->next;
			}
			current = temp;
		} while (swapped);

		//printCenter("学生记录已按成绩升序排序。\n");
	}

// 学生成绩统计信息
void calculateStatistics(struct Student *head) {
	if (head == NULL) {
		printCenter("学生记录不存在。");
		return;
	}

	int count = 0;
	float totalMarks = 0;
	float highestMarks = head->marks;
	float lowestMarks = head->marks;

	struct Student *current = head;
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

	printf("						学生总数：%d\n", count);
	//printf("总分： %.2f\n", totalMarks);
	printf("						总分平均分： %.2f\n", averageMarks);
	printf("						总分最高分： %.2f\n", highestMarks);
	printf("						总分最低分： %.2f\n", lowestMarks);
}
void save(struct Student *head) {
	FILE *fp = fopen("D:\\work\\code\\c\\studentcurd\\student.txt", "w");
	if (fp == NULL) {
		printCenter("打开文件失败");
		return;
	}
	struct Student *current = head;
	while (current != NULL) {
		fprintf(fp, "%d\n%s\n%.2f\n%.2f\n", current->rollNumber, current->name, current->mark1, current->mark2);
		current = current->next;
	}
	fclose(fp);
	//printCenter("保存结束");
}
void load(struct Student **head) {
	FILE* fp = fopen("D:\\work\\code\\c\\studentcurd\\student.txt", "r");
	if (fp == NULL) {
		printCenter("打开文件失败");
		return;
	}
	struct Student *current = *head;
	while (current != NULL) {
		struct Student *temp = current;
		current = current->next;
		free(temp);
	}
	*head = NULL;
	while (!feof(fp)) {
		struct Student *newStudent = (struct Student *)malloc(sizeof(struct Student));
		if (newStudent == NULL) {
			printCenter("内存分配失败，无法添加学生记录。");
			return;
		}
		fscanf(fp, "%d\n%s\n%f\n%f\n", &(newStudent->rollNumber), newStudent->name, &(newStudent->mark1), &(newStudent->mark2));
		newStudent->marks = newStudent->mark1 + newStudent->mark2;
		newStudent->next = NULL;
		if (*head == NULL) {
			*head = newStudent;
		} else {
			struct Student *current = *head;
			while (current->next != NULL) {
				current = current->next;
			}
			current->next = newStudent;
			current = current->next;
			current->next = NULL;
		}
	}
	fclose(fp);

}

int main() {
	struct Student *head = NULL;
	int choice;
	int rollNumber;
	char name[50];
	float marks;
	float mark1;
	float mark2;
	//FILE* fp = fopen("./stu.txt", "r+");
	//load(&head);
	
	do {
		//GotoXY(3, 3);

		printf("					■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■	\n");
		printf("					■");
		printf("	      学生成绩管理系统");
		printf("	      ■	\n");
		printf("					■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■	\n");
		printf("						1.       添加学生信息	\n");
		printf("						2.    展示所有学生记录	\n");
		printf("						3. 通过学号寻找学生记录\n");
		printf("						4. 通过姓名寻找学生记录\n");
		printf("						5. 通过学号删除学生记录\n");
		printf("						6. 通过学号更新学生记录\n");
		printf("						7.    按学号进行排序	\n");
		printf("						8.    按姓名进行排序	\n");
		printf("						9.   按成绩进行升序排序	\n");
		printf("						10. 按总成绩降序排序\n");
		printf("						11. 学生成绩统计信息\n");
		printf("						12.        退出\n");
		printf("					■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		printCenterContinue("输入你的操作：");
		
		scanf("%d", &choice);

		switch (choice) {
			case 1:
				load(&head);
				addStudent(&head);
				save(head);
				break;
			case 2:
				load(&head);
				displayStudents(head);
				break;
			case 3:
				load(&head);
				printCenterContinue("输入查找的学号：");
				scanf("%d", &rollNumber);
				searchByRollNumber(head, rollNumber);
				break;
			case 4:
				load(&head);
				printCenterContinue("输入查找的姓名：");
				scanf("%s", name);
				searchByName(head, name);
				break;
			case 5:
				load(&head);
				printCenterContinue("输入删除的学号：");
				scanf("%d", &rollNumber);
				deleteByRollNumber(&head, rollNumber);
				save(head);
				break;
			case 6:
				load(&head);
				printCenterContinue("输入更新的学号：");
				scanf("%d", &rollNumber);
				updateByRollNumber(head, rollNumber);
				save(head);
				break;
			case 7:
				load(&head);
				sortByRollNumber(&head);
				save(head);
				//load(&head);
				displayStudents(head);

				break;
			case 8:
				load(&head);
				sortByname(&head);
				save(head);
				
				displayStudents(head);

				break;
			case 9:
				load(&head);
				sortByMarks(&head);
				save(head);
				
				displayStudents(head);

				break;
			case 10:
				load(&head);
				sortByTotalMarks(&head);
				save(head);
				//load(&head);
				displayStudents(head);

				break;
			case 11:
				load(&head);
				calculateStatistics(head);
				save(head);
				break;
			case 12:
				save(head);
				freeMemory(head);
				printCenter("退出程序中...");
				//save(head);
				break;
			default:
				printCenter("无效操作，请再试一次。\n");
		}
		//save(head,fp);
	} while (choice != 12);
}