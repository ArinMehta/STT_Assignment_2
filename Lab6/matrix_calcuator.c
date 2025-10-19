// matrix_calculator.c
#include <stdio.h>
#include <stdlib.h>
#define MAX_DIM 10

// Function Prototypes
void print_menu();
void get_matrix(int mat[MAX_DIM][MAX_DIM], int *rows, int *cols, char name);
void print_matrix(int mat[MAX_DIM][MAX_DIM], int rows, int cols);
void add_matrices(int a[MAX_DIM][MAX_DIM], int b[MAX_DIM][MAX_DIM], int r, int c);
void multiply_matrices(int a[MAX_DIM][MAX_DIM], int b[MAX_DIM][MAX_DIM], int r1, int c1, int c2);
void transpose_matrix(int a[MAX_DIM][MAX_DIM], int r, int c);

/**
 * @brief Main function for the matrix calculator.
 *
 * Drives the user interaction through a menu loop and calls the
 * appropriate functions for matrix operations.
 */
int main() {
    int mat_a[MAX_DIM][MAX_DIM], mat_b[MAX_DIM][MAX_DIM];
    int r1, c1, r2, c2;
    int choice;

    while (1) {
        print_menu();
        scanf("%d", &choice);

        if (choice == 4) {
            printf("\nExiting calculator. Goodbye!\n");
            break;
        }

        if (choice < 1 || choice > 4) {
            printf("\nInvalid choice. Please try again.\n");
            continue;
        }

        // Get Matrix A for all operations
        get_matrix(mat_a, &r1, &c1, 'A');

        // Handle operations
        switch (choice) {
            case 1: // Addition
                get_matrix(mat_b, &r2, &c2, 'B');
                if (r1 == r2 && c1 == c2) {
                    add_matrices(mat_a, mat_b, r1, c1);
                } else {
                    printf("\nError: Matrices must have the same dimensions for addition.\n");
                }
                break;

            case 2: // Multiplication
                get_matrix(mat_b, &r2, &c2, 'B');
                if (c1 == r2) {
                    multiply_matrices(mat_a, mat_b, r1, c1, c2);
                } else {
                    printf("\nError: Columns of Matrix A must equal rows of Matrix B for multiplication.\n");
                }
                break;

            case 3: // Transpose
                transpose_matrix(mat_a, r1, c1);
                break;
        }
    }

    return 0;
}

/**
 * @brief Displays the calculator's menu options.
 */
void print_menu() {
    printf("\n--- Matrix Calculator ---\n");
    printf("1. Add two matrices\n");
    printf("2. Multiply two matrices\n");
    printf("3. Find the transpose of a matrix\n");
    printf("4. Exit\n");
    printf("-------------------------\n");
    printf("Enter your choice: ");
}

/**
 * @brief Prompts the user to enter the dimensions and elements of a matrix.
 *
 * @param mat The 2D array to store the matrix.
 * @param rows Pointer to store the number of rows.
 * @param cols Pointer to store the number of columns.
 * @param name The character name of the matrix (e.g., 'A').
 */
void get_matrix(int mat[MAX_DIM][MAX_DIM], int *rows, int *cols, char name) {
    printf("\nEnter details for Matrix %c:\n", name);

    // Get dimensions
    while (1) {
        printf("Enter number of rows (1-%d): ", MAX_DIM);
        scanf("%d", rows);
        if (*rows > 0 && *rows <= MAX_DIM) break;
        printf("Invalid input. Please enter a value between 1 and %d.\n", MAX_DIM);
    }
    while (1) {
        printf("Enter number of columns (1-%d): ", MAX_DIM);
        scanf("%d", cols);
        if (*cols > 0 && *cols <= MAX_DIM) break;
        printf("Invalid input. Please enter a value between 1 and %d.\n", MAX_DIM);
    }

    // Get elements
    printf("Enter the elements of Matrix %c (%d x %d):\n", name, *rows, *cols);
    for (int i = 0; i < *rows; i++) {
        for (int j = 0; j < *cols; j++) {
            printf("Element [%d][%d]: ", i, j);
            scanf("%d", &mat[i][j]);
        }
    }
}

/**
 * @brief Prints the elements of a matrix in a formatted way.
 *
 * @param mat The matrix to print.
 * @param rows The number of rows in the matrix.
 * @param cols The number of columns in the matrix.
 */
void print_matrix(int mat[MAX_DIM][MAX_DIM], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        printf("| ");
        for (int j = 0; j < cols; j++) {
            printf("%-4d ", mat[i][j]);
        }
        printf("|\n");
    }
}

/**
 * @brief Adds two matrices and prints the result.
 *
 * @param a The first matrix.
 * @param b The second matrix.
 * @param r The number of rows for both matrices.
 * @param c The number of columns for both matrices.
 */
void add_matrices(int a[MAX_DIM][MAX_DIM], int b[MAX_DIM][MAX_DIM], int r, int c) {
    int result[MAX_DIM][MAX_DIM];

    // Perform addition
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            result[i][j] = a[i][j] + b[i][j];
        }
    }

    // Print the result
    printf("\nResult of Matrix A + Matrix B:\n");
    print_matrix(result, r, c);
}

/**
 * @brief Multiplies two matrices and prints the result.
 *
 * @param a The first matrix.
 * @param b The second matrix.
 * @param r1 Rows in the first matrix.
 * @param c1 Columns in the first matrix (and rows in the second).
 * @param c2 Columns in the second matrix.
 */
void multiply_matrices(int a[MAX_DIM][MAX_DIM], int b[MAX_DIM][MAX_DIM], int r1, int c1, int c2) {
    int result[MAX_DIM][MAX_DIM];

    // Initialize result matrix to zero
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c2; j++) {
            result[i][j] = 0;
        }
    }

    // Perform multiplication
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c2; j++) {
            for (int k = 0; k < c1; k++) {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }

    // Print the result
    printf("\nResult of Matrix A * Matrix B:\n");
    print_matrix(result, r1, c2);
}

/**
 * @brief Calculates the transpose of a matrix and prints it.
 *
 * @param a The matrix to transpose.
 * @param r The number of rows.
 * @param c The number of columns.
 */
void transpose_matrix(int a[MAX_DIM][MAX_DIM], int r, int c) {
    int result[MAX_DIM][MAX_DIM];

    // Perform transpose
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            result[j][i] = a[i][j];
        }
    }

    // Print the result
    printf("\nTranspose of Matrix A:\n");
    // Note: The dimensions are swapped for the result
    print_matrix(result, c, r);
}