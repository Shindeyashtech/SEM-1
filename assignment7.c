//Write a program to create graph, use the map of your city as the graph. 
//Represent graph using adjacency list/adjacency matrix and perform Depth 
//First Search and Breadth First Search
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

typedef struct Graph {
    int numVertices;
    Node** adjLists;
    int* visited;
} Graph;

typedef struct Queue {
    int items[MAX];
    int front;
    int rear;
} Queue;

Graph* createGraph(int vertices);
void addEdge(Graph* graph, int src, int dest);
void printGraph(Graph* graph);
void DFS(Graph* graph, int startVertex);
void BFS(Graph* graph, int startVertex);

Queue* createQueue();
void enqueue(Queue* q, int value);
int dequeue(Queue* q);
int isEmpty(Queue* q);

int main() {
    int vertices, edges, i, src, dest, choice, startVertex;
    printf("Enter the number of locations (vertices): ");
    scanf("%d", &vertices);

    Graph* graph = createGraph(vertices);

    printf("Enter the number of roads (edges): ");
    scanf("%d", &edges);

    for (i = 0; i < edges; i++) {
        printf("Enter edge (source and destination): ");
        scanf("%d %d", &src, &dest);
        addEdge(graph, src, dest);
    }

    do {
        printf("\nMenu:\n");
        printf("1. Print Graph\n");
        printf("2. Depth First Search (DFS)\n");
        printf("3. Breadth First Search (BFS)\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printGraph(graph);
                break;

            case 2:
                printf("Enter starting vertex for DFS: ");
                scanf("%d", &startVertex);
                printf("DFS Traversal:\n");
                for (i = 0; i < vertices; i++) {
                    graph->visited[i] = 0;
                }
                DFS(graph, startVertex);
                printf("\n");
                break;

            case 3:
                printf("Enter starting vertex for BFS: ");
                scanf("%d", &startVertex);
                printf("BFS Traversal:\n");
                BFS(graph, startVertex);
                printf("\n");
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

Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = vertices;
    graph->adjLists = (Node**)malloc(vertices * sizeof(Node*));
    graph->visited = (int*)malloc(vertices * sizeof(int));

    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0;
    }

    return graph;
}

Node* createNode(int vertex) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

void printGraph(Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        Node* temp = graph->adjLists[i];
        printf("Vertex %d:\n", i);
        while (temp) {
            printf(" -> %d", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}

void DFS(Graph* graph, int startVertex) {
    graph->visited[startVertex] = 1;
    printf("%d ", startVertex);

    Node* adjList = graph->adjLists[startVertex];
    while (adjList != NULL) {
        int connectedVertex = adjList->vertex;

        if (!graph->visited[connectedVertex]) {
            DFS(graph, connectedVertex);
        }
        adjList = adjList->next;
    }
}

Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = -1;
    q->rear = -1;
    return q;
}

int isEmpty(Queue* q) {
    return q->rear == -1;
}

void enqueue(Queue* q, int value) {
    if (q->rear == MAX - 1) {
        printf("Queue is full\n");
        return;
    }
    if (q->front == -1)
        q->front = 0;
    q->rear++;
    q->items[q->rear] = value;
}

int dequeue(Queue* q) {
    int item;
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        return -1;
    }
    item = q->items[q->front];
    q->front++;
    if (q->front > q->rear) {
        q->front = q->rear = -1;
    }
    return item;
}

void BFS(Graph* graph, int startVertex) {
    Queue* q = createQueue();
    graph->visited[startVertex] = 1;
    enqueue(q, startVertex);

    while (!isEmpty(q)) {
        int currentVertex = dequeue(q);
        printf("%d ", currentVertex);

        Node* adjList = graph->adjLists[currentVertex];
        while (adjList != NULL) {
            int connectedVertex = adjList->vertex;

            if (!graph->visited[connectedVertex]) {
                graph->visited[connectedVertex] = 1;
                enqueue(q, connectedVertex);
            }
            adjList = adjList->next;
        }
    }
}
//Enter the number of locations (vertices): 5
//Enter the number of roads (edges): 6
//Enter edge (source and destination): 0 1
//Enter edge (source and destination): 0 4
//Enter edge (source and destination): 1 2
//Enter edge (source and destination): 1 3
//Enter edge (source and destination): 1 4
//Enter edge (source and destination): 3 4

 
