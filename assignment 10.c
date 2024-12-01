//Write a program to arrange list of students to find out first ten toppers from a 
//class using Bubble sort. (refer the student database given in assignment 10)
#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 100

typedef struct {
    char name[50];
    int rollNumber;
    float marks;
} Student;

void bubbleSort(Student students[], int n);
void displayTopToppers(Student students[], int n);

int main() {
    int n, i;
    Student students[MAX_STUDENTS];

    printf("Enter the number of students: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX_STUDENTS) {
        printf("Invalid number of students. Exiting.\n");
        return 1;
    }

    for (i = 0; i < n; i++) {
        printf("\nEnter details for student %d:\n", i + 1);
        printf("Name: ");
        getchar(); // To consume the newline left by previous input
        fgets(students[i].name, 50, stdin);
        students[i].name[strcspn(students[i].name, "\n")] = '\0'; // Remove trailing newline
        printf("Roll Number: ");
        scanf("%d", &students[i].rollNumber);
        printf("Marks: ");
        scanf("%f", &students[i].marks);
    }

    bubbleSort(students, n);

    printf("\nTop 10 Toppers:\n");
    displayTopToppers(students, n);

    return 0;
}

void bubbleSort(Student students[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (students[j].marks < students[j + 1].marks) {
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
}

void displayTopToppers(Student students[], int n) {
    int limit = n < 10 ? n : 10;
    for (int i = 0; i < limit; i++) {
        printf("Rank %d: %s (Roll Number: %d) - Marks: %.2f\n", 
               i + 1, students[i].name, students[i].rollNumber, students[i].marks);
    }
}
