//Write a program to represent sparse matrix using array and perform simple 
//and fast transpose
 #include <stdio.h>

#define MAX 100

typedef struct {
    int row;
    int col;
    int value;
} Element;

typedef struct {
    int rows;
    int cols;
    int num;
    Element data[MAX];
} SparseMatrix;

void displaySparseMatrix(SparseMatrix *matrix) {
    printf("Sparse Matrix Representation (row, col, value):\n");
    for (int i = 0; i < matrix->num; i++) {
        printf("%d %d %d\n", matrix->data[i].row, matrix->data[i].col, matrix->data[i].value);
    }
}

SparseMatrix fastTranspose(SparseMatrix *matrix) {
    SparseMatrix result;
    result.rows = matrix->cols;
    result.cols = matrix->rows;
    result.num = matrix->num;

    int rowCount[MAX] = {0};
    for (int i = 0; i < matrix->num; i++) {
        rowCount[matrix->data[i].col]++;
    }

    int startPos[MAX];
    startPos[0] = 0;
    for (int i = 1; i < matrix->cols; i++) {
        startPos[i] = startPos[i - 1] + rowCount[i - 1];
    }

    for (int i = 0; i < matrix->num; i++) {
        int pos = startPos[matrix->data[i].col]++;
        result.data[pos].row = matrix->data[i].col;
        result.data[pos].col = matrix->data[i].row;
        result.data[pos].value = matrix->data[i].value;
    }

    return result;
}

int main() {
    SparseMatrix matrix;
    matrix.rows = 4;
    matrix.cols = 4;
    matrix.num = 4;

    matrix.data[0].row = 0; matrix.data[0].col = 1; matrix.data[0].value = 5;
    matrix.data[1].row = 1; matrix.data[1].col = 2; matrix.data[1].value = 8;
    matrix.data[2].row = 2; matrix.data[2].col = 0; matrix.data[2].value = 3;
    matrix.data[3].row = 3; matrix.data[3].col = 2; matrix.data[3].value = 6;

    printf("Original Matrix:\n");
    displaySparseMatrix(&matrix);

    SparseMatrix transposedMatrix = fastTranspose(&matrix);

    printf("\nTransposed Matrix:\n");
    displaySparseMatrix(&transposedMatrix);

    return 0;
}
