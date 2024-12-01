//Write a program to represent a graph of your city using adjacency matrix /adjacency list. Nodes should represent the various areas in the city and links should represent the distance between them. Find the shortest path of your college from your home using Dijkstra's algorithm
#include <stdio.h>
#include <limits.h>
#define MAX 100
#define INF INT_MAX

void dijkstra(int graph[MAX][MAX], int n, int start, int end);

int main() {
    int n, edges, u, v, w, start, end;
    int graph[MAX][MAX];

    printf("Enter the number of areas (nodes) in the city: ");
    scanf("%d", &n);

    // Initialize adjacency matrix with INF (no connection)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            graph[i][j] = (i == j) ? 0 : INF;
        }
    }

    printf("Enter the number of roads (edges): ");
    scanf("%d", &edges);

    printf("Enter the edges (source, destination, distance):\n");
    for (int i = 0; i < edges; i++) {
        scanf("%d %d %d", &u, &v, &w);
        graph[u][v] = w;
        graph[v][u] = w; // Assuming undirected graph
    }

    printf("Enter the starting node (home): ");
    scanf("%d", &start);

    printf("Enter the ending node (college): ");
    scanf("%d", &end);

    printf("Shortest Path from %d to %d:\n", start, end);
    dijkstra(graph, n, start, end);

    return 0;
}

void dijkstra(int graph[MAX][MAX], int n, int start, int end) {
    int distance[MAX], visited[MAX], parent[MAX];
    for (int i = 0; i < n; i++) {
        distance[i] = INF;
        visited[i] = 0;
        parent[i] = -1;
    }

    distance[start] = 0;

    for (int i = 0; i < n - 1; i++) {
        int min = INF, u = -1;

        // Find the unvisited node with the smallest distance
        for (int j = 0; j < n; j++) {
            if (!visited[j] && distance[j] < min) {
                min = distance[j];
                u = j;
            }
        }

        if (u == -1) break; // All reachable nodes visited

        visited[u] = 1;

        // Update distances to neighbors
        for (int v = 0; v < n; v++) {
            if (graph[u][v] != INF && !visited[v]) {
                int newDist = distance[u] + graph[u][v];
                if (newDist < distance[v]) {
                    distance[v] = newDist;
                    parent[v] = u;
                }
            }
        }
    }

    if (distance[end] == INF) {
        printf("No path from %d to %d\n", start, end);
        return;
    }

    // Print the shortest path
    printf("Distance: %d\n", distance[end]);
    printf("Path: ");
    int current = end;
    int path[MAX], pathSize = 0;

    while (current != -1) {
        path[pathSize++] = current;
        current = parent[current];
    }

    for (int i = pathSize - 1; i >= 0; i--) {
        printf("%d ", path[i]);
    }
    printf("\n");
}
//Enter the number of areas (nodes) in the city: 5
//Enter the number of roads (edges): 6
//Enter the edges (source, destination, distance):
//0 1 2
//0 2 4
//1 2 1
//1 3 7
//2 4 3
//3 4 2
//Enter the starting node (home): 0
//Enter the ending node (college): 4
