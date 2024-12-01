//Write a menu-driven program that utilizes a singly linked list to handle 
//operations such as adding, removing, and displaying books, as well as 
//searching for specific books and counting the total number of books 
//available.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Book {
    int id;
    char title[100];
    struct Book* next;
} Book;

Book* head = NULL;

Book* createBook(int id, char* title) {
    Book* newBook = (Book*)malloc(sizeof(Book));
    newBook->id = id;
    strcpy(newBook->title, title);
    newBook->next = NULL;
    return newBook;
}

void addBook(int id, char* title) {
    Book* newBook = createBook(id, title);
    if (head == NULL) {
        head = newBook;
    } else {
        Book* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newBook;
    }
    printf("Book added successfully.\n");
}

void removeBook(int id) {
    if (head == NULL) {
        printf("No books available.\n");
        return;
    }
    if (head->id == id) {
        Book* temp = head;
        head = head->next;
        free(temp);
        printf("Book removed successfully.\n");
        return;
    }
    Book* temp = head;
    while (temp->next != NULL && temp->next->id != id) {
        temp = temp->next;
    }
    if (temp->next == NULL) {
        printf("Book with ID %d not found.\n", id);
    } else {
        Book* toDelete = temp->next;
        temp->next = temp->next->next;
        free(toDelete);
        printf("Book removed successfully.\n");
    }
}

void displayBooks() {
    if (head == NULL) {
        printf("No books available.\n");
        return;
    }
    Book* temp = head;
    printf("Books in the list:\n");
    while (temp != NULL) {
        printf("ID: %d, Title: %s\n", temp->id, temp->title);
        temp = temp->next;
    }
}

void searchBook(int id) {
    Book* temp = head;
    while (temp != NULL) {
        if (temp->id == id) {
            printf("Book found: ID: %d, Title: %s\n", temp->id, temp->title);
            return;
        }
        temp = temp->next;
    }
    printf("Book with ID %d not found.\n", id);
}

void countBooks() {
    int count = 0;
    Book* temp = head;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    printf("Total number of books: %d\n", count);
}

int main() {
    int choice, id;
    char title[100];
    do {
        printf("\nMenu:\n");
        printf("1. Add Book\n");
        printf("2. Remove Book\n");
        printf("3. Display Books\n");
        printf("4. Search Book\n");
        printf("5. Count Books\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter Book ID: ");
                scanf("%d", &id);
                printf("Enter Book Title: ");
                getchar(); // To clear the newline character from input buffer
                fgets(title, 100, stdin);
                title[strcspn(title, "\n")] = '\0'; // Remove trailing newline
                addBook(id, title);
                break;
            case 2:
                printf("Enter Book ID to remove: ");
                scanf("%d", &id);
                removeBook(id);
                break;
            case 3:
                displayBooks();
                break;
            case 4:
                printf("Enter Book ID to search: ");
                scanf("%d", &id);
                searchBook(id);
                break;
            case 5:
                countBooks();
                break;
            case 6:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);
    return 0;
}
