//Write a program that reads a list of names and telephone numbers from user 
//and insert into a BST tree. Once the tree has been built, present the user with 
//a menu that allows him to search the list for a specified name, insert new 
//name, an existing name or print the entire phone list.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char name[100];
    char phone[15];
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(char* name, char* phone) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->name, name);
    strcpy(newNode->phone, phone);
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node* insert(Node* root, char* name, char* phone) {
    if (root == NULL) {
        return createNode(name, phone);
    }
    if (strcmp(name, root->name) < 0) {
        root->left = insert(root->left, name, phone);
    } else if (strcmp(name, root->name) > 0) {
        root->right = insert(root->right, name, phone);
    } else {
        printf("Name already exists. Updating phone number.\n");
        strcpy(root->phone, phone);
    }
    return root;
}

Node* search(Node* root, char* name) {
    if (root == NULL || strcmp(root->name, name) == 0) {
        return root;
    }
    if (strcmp(name, root->name) < 0) {
        return search(root->left, name);
    } else {
        return search(root->right, name);
    }
}

void inorderTraversal(Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("Name: %s, Phone: %s\n", root->name, root->phone);
        inorderTraversal(root->right);
    }
}

int main() {
    Node* root = NULL;
    int choice;
    char name[100], phone[15];

    do {
        printf("\nMenu:\n");
        printf("1. Insert a new name and phone number\n");
        printf("2. Search for a name\n");
        printf("3. Print the entire phone list\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Name: ");
                getchar(); // Clear newline from buffer
                fgets(name, 100, stdin);
                name[strcspn(name, "\n")] = '\0'; // Remove trailing newline
                printf("Enter Phone Number: ");
                fgets(phone, 15, stdin);
                phone[strcspn(phone, "\n")] = '\0'; // Remove trailing newline
                root = insert(root, name, phone);
                break;

            case 2:
                printf("Enter Name to search: ");
                getchar(); // Clear newline from buffer
                fgets(name, 100, stdin);
                name[strcspn(name, "\n")] = '\0'; // Remove trailing newline
                Node* result = search(root, name);
                if (result != NULL) {
                    printf("Found: Name: %s, Phone: %s\n", result->name, result->phone);
                } else {
                    printf("Name not found in the phone list.\n");
                }
                break;

            case 3:
                printf("Phone List:\n");
                if (root == NULL) {
                    printf("The phone list is empty.\n");
                } else {
                    inorderTraversal(root);
                }
                break;

            case 4:
                printf("Exiting program.\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}
