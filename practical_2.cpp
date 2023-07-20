#include <iostream>

// Function to allocate memory for a matrix
int** createMatrix(int rows, int cols) {
    int** matrix = new int*[rows];
    for (int i = 0; i < rows; ++i)
        matrix[i] = new int[cols];
    return matrix;
}

// Function to deallocate memory for a matrix
void destroyMatrix(int** matrix, int rows) {
    for (int i = 0; i < rows; ++i)
        delete[] matrix[i];
    delete[] matrix;
}

// Function to perform matrix multiplication
int** matrixMultiplication(int** matrix1, int** matrix2, int rows1, int cols1, int cols2) {
    int** result = createMatrix(rows1, cols2);

    for (int i = 0; i < rows1; ++i) {
        for (int j = 0; j < cols2; ++j) {
            int sum = 0;
            for (int k = 0; k < cols1; ++k) {
                sum += *(matrix1[i] + k) * *(matrix2[k] + j);
            }
            result[i][j] = sum;
        }
    }

    return result;
}

// Function to print a matrix
void printMatrix(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    int rows1, cols1, rows2, cols2;

    std::cout << "Enter the number of rows and columns for matrix 1: ";
    std::cin >> rows1 >> cols1;

    std::cout << "Enter the number of rows and columns for matrix 2: ";
    std::cin >> rows2 >> cols2;

    if (cols1 != rows2) {
        std::cout << "Matrix multiplication is not possible. The number of columns in matrix 1 must be equal to the number of rows in matrix 2." << std::endl;
        return 1;
    }

    int** matrix1 = createMatrix(rows1, cols1);
    int** matrix2 = createMatrix(rows2, cols2);

    std::cout << "Enter elements of matrix 1:" << std::endl;
    for (int i = 0; i < rows1; ++i) {
        for (int j = 0; j < cols1; ++j) {
            std::cin >> matrix1[i][j];
        }
    }

    std::cout << "Enter elements of matrix 2:" << std::endl;
    for (int i = 0; i < rows2; ++i) {
        for (int j = 0; j < cols2; ++j) {
            std::cin >> matrix2[i][j];
        }
    }

    int** resultMatrix = matrixMultiplication(matrix1, matrix2, rows1, cols1, cols2);

    std::cout << "Matrix 1:" << std::endl;
    printMatrix(matrix1, rows1, cols1);

    std::cout << "Matrix 2:" << std::endl;
    printMatrix(matrix2, rows2, cols2);

    std::cout << "Matrix multiplication result:" << std::endl;
    printMatrix(resultMatrix, rows1, cols2);

    // Free memory
    destroyMatrix(matrix1, rows1);
    destroyMatrix(matrix2, rows2);
    destroyMatrix(resultMatrix, rows1);

    return 0;
}
