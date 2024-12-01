//Write a program to manage customer support tickets. Utilize a circular queue 
//implemented using arrays to handle incoming support requests. Each ticket 
//represents a customer support request, ensuring memory-efficient 
//management. Implement features for ticket submission, processing, and 
//displaying the current queue status
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 5

typedef struct {
    int id;
    char issue[100];
} Ticket;

typedef struct {
    Ticket queue[MAX];
    int front;
    int rear;
    int size;
} CircularQueue;

void initQueue(CircularQueue* cq) {
    cq->front = 0;
    cq->rear = -1;
    cq->size = 0;
}

int isFull(CircularQueue* cq) {
    return cq->size == MAX;
}

int isEmpty(CircularQueue* cq) {
    return cq->size == 0;
}

void submitTicket(CircularQueue* cq, int id, char* issue) {
    if (isFull(cq)) {
        printf("Queue is full! Cannot accept new tickets.\n");
        return;
    }
    cq->rear = (cq->rear + 1) % MAX;
    cq->queue[cq->rear].id = id;
    strcpy(cq->queue[cq->rear].issue, issue);
    cq->size++;
    printf("Ticket ID %d submitted successfully.\n", id);
}

void processTicket(CircularQueue* cq) {
    if (isEmpty(cq)) {
        printf("No tickets to process.\n");
        return;
    }
    printf("Processing Ticket ID %d: %s\n", cq->queue[cq->front].id, cq->queue[cq->front].issue);
    cq->front = (cq->front + 1) % MAX;
    cq->size--;
}

void displayQueue(CircularQueue* cq) {
    if (isEmpty(cq)) {
        printf("Queue is empty.\n");
        return;
    }
    printf("Current Ticket Queue:\n");
    int count = 0;
    int i = cq->front;
    while (count < cq->size) {
        printf("Ticket ID %d: %s\n", cq->queue[i].id, cq->queue[i].issue);
        i = (i + 1) % MAX;
        count++;
    }
}

int main() {
    CircularQueue cq;
    initQueue(&cq);

    int choice, id;
    char issue[100];

    do {
        printf("\nMenu:\n");
        printf("1. Submit Ticket\n");
        printf("2. Process Ticket\n");
        printf("3. Display Ticket Queue\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Ticket ID: ");
                scanf("%d", &id);
                printf("Enter Issue Description: ");
                getchar(); // Clear newline from buffer
                fgets(issue, 100, stdin);
                issue[strcspn(issue, "\n")] = '\0'; // Remove trailing newline
                submitTicket(&cq, id, issue);
                break;

            case 2:
                processTicket(&cq);
                break;

            case 3:
                displayQueue(&cq);
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
