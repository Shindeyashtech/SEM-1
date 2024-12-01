//Write a program to create student database. Database contains different fields 
//of student like Roll No, Name and percentage. Search a particular student 
//according to roll number using binary search.
#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 100

typedef struct {
    int rollNumber;
    char name[50];
    float percentage;
} Student;

void bubbleSort(Student students[], int n);
int binarySearch(Student students[], int n, int rollNumber);
void displayStudent(Student student);

int main() {
    int n, rollNumber, index;
    Student students[MAX_STUDENTS];

    printf("Enter the number of students: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX_STUDENTS) {
        printf("Invalid number of students. Exiting.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        printf("\nEnter details for student %d:\n", i + 1);
        printf("Roll Number: ");
        scanf("%d", &students[i].rollNumber);
        printf("Name: ");
        getchar(); // Consume newline left by previous input
        fgets(students[i].name, 50, stdin);
        students[i].name[strcspn(students[i].name, "\n")] = '\0'; // Remove trailing newline
        printf("Percentage: ");
        scanf("%f", &students[i].percentage);
    }

    bubbleSort(students, n);

    printf("\nEnter the roll number to search: ");
    scanf("%d", &rollNumber);

    index = binarySearch(students, n, rollNumber);

    if (index != -1) {
        printf("Student Found:\n");
        displayStudent(students[index]);
    } else {
        printf("Student with Roll Number %d not found.\n", rollNumber);
    }

    return 0;
}

void bubbleSort(Student students[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (students[j].rollNumber > students[j + 1].rollNumber) {
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
}

int binarySearch(Student students[], int n, int rollNumber) {
    int low = 0, high = n - 1;

    while (low <= high) {
        int mid = (low + high) / 2;

        if (students[mid].rollNumber == rollNumber) {
            return mid;
        } else if (students[mid].rollNumber < rollNumber) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return -1; // Roll number not found
}

void displayStudent(Student student) {
    printf("Roll Number: %d\n", student.rollNumber);
    printf("Name: %s\n", student.name);
    printf("Percentage: %.2f\n", student.percentage);
}
