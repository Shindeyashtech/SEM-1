 //Write a program to sort a list of sales data for a retail company. Each record 
//represents a sale and contains the following information: sales ID, customer 
//name, product name, quantity sold, and total sale amount. sort the sales data 
//based on the total sale amount in descending order using the Merge Sort 
//algorithm. / Quick sort method
#include <stdio.h>
#include <string.h>

#define MAX 100

typedef struct {
    int salesID;
    char customerName[50];
    char productName[50];
    int quantitySold;
    float totalSaleAmount;
} Sale;

void mergeSort(Sale sales[], int left, int right);
void merge(Sale sales[], int left, int mid, int right);
void displaySales(Sale sales[], int n);

int main() {
    int n;
    Sale sales[MAX];

    printf("Enter the number of sales records: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX) {
        printf("Invalid number of sales records. Exiting.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        printf("\nEnter details for sale %d:\n", i + 1);
        printf("Sales ID: ");
        scanf("%d", &sales[i].salesID);
        printf("Customer Name: ");
        getchar(); // Consume newline left by previous input
        fgets(sales[i].customerName, 50, stdin);
        sales[i].customerName[strcspn(sales[i].customerName, "\n")] = '\0'; // Remove trailing newline
        printf("Product Name: ");
        fgets(sales[i].productName, 50, stdin);
        sales[i].productName[strcspn(sales[i].productName, "\n")] = '\0'; // Remove trailing newline
        printf("Quantity Sold: ");
        scanf("%d", &sales[i].quantitySold);
        printf("Total Sale Amount: ");
        scanf("%f", &sales[i].totalSaleAmount);
    }

    mergeSort(sales, 0, n - 1);

    printf("\nSales Data Sorted by Total Sale Amount (Descending Order):\n");
    displaySales(sales, n);

    return 0;
}

void mergeSort(Sale sales[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Sort the left and right halves
        mergeSort(sales, left, mid);
        mergeSort(sales, mid + 1, right);

        // Merge the sorted halves
        merge(sales, left, mid, right);
    }
}

void merge(Sale sales[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Sale L[MAX], R[MAX];

    // Copy data to temporary arrays
    for (int i = 0; i < n1; i++) {
        L[i] = sales[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = sales[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;

    // Merge the arrays back into sales[]
    while (i < n1 && j < n2) {
        if (L[i].totalSaleAmount >= R[j].totalSaleAmount) {
            sales[k++] = L[i++];
        } else {
            sales[k++] = R[j++];
        }
    }

    // Copy remaining elements of L[] if any
    while (i < n1) {
        sales[k++] = L[i++];
    }

    // Copy remaining elements of R[] if any
    while (j < n2) {
        sales[k++] = R[j++];
    }
}

void displaySales(Sale sales[], int n) {
    for (int i = 0; i < n; i++) {
        printf("Sales ID: %d, Customer: %s, Product: %s, Quantity: %d, Total Sale Amount: %.2f\n",
               sales[i].salesID, sales[i].customerName, sales[i].productName,
               sales[i].quantitySold, sales[i].totalSaleAmount);
    }
}
