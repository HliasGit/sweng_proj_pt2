#include "matrix_multiplication.h"
#include <mpi.h>
#include <iostream>
#include <fstream>
#include <vector>

void readMatrixFromFile(const std::string& filename, std::vector<std::vector<int>>& matrix, int& rows, int& cols) {
    std::ifstream infile(filename);
    if (!infile) {
        std::cerr << "Error opening file: " << filename << std::endl;
        MPI_Abort(MPI_COMM_WORLD, 1);
    }
    
    infile >> rows >> cols;
    matrix.resize(rows, std::vector<int>(cols));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            infile >> matrix[i][j];
        }
    }
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size != 2) {
        if (rank == 0) {
            std::cerr << "This application is meant to be run with 2 MPI processes. Non esageriamo con le risorse. State molto calmi!" << std::endl;
        }
        MPI_Finalize();
        return -1;
    }

    int rowsA, colsA, rowsB, colsB;
    std::vector<std::vector<int>> A, B;

    if (rank == 0) {
        readMatrixFromFile("matrixA.txt", A, rowsA, colsA);
        readMatrixFromFile("matrixB.txt", B, rowsB, colsB);
    }

    
    MPI_Bcast(&rowsA, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&colsA, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&rowsB, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&colsB, 1, MPI_INT, 0, MPI_COMM_WORLD);

    
    if (rank != 0) {
        A.resize(rowsA, std::vector<int>(colsA));
    }
    for (int i = 0; i < rowsA; ++i) {
        MPI_Bcast(A[i].data(), colsA, MPI_INT, 0, MPI_COMM_WORLD);
    }

    
    if (rank != 0) {
        B.resize(rowsB, std::vector<int>(colsB));
    }
    for (int i = 0; i < rowsB; ++i) {
        MPI_Bcast(B[i].data(), colsB, MPI_INT, 0, MPI_COMM_WORLD);
    }

    std::vector<std::vector<int>> C(rowsA, std::vector<int>(colsB, 0));
    multiplyMatrices(A, B, C, rowsA, colsA, colsB);

    if (rank == 0) {
        std::cout << "Congratulations, bro. Here is your resultant matrix C:" << std::endl;
        for (const auto& row : C) {
            for (const auto& elem : row) {
                std::cout << elem << " ";
            }
            std::cout << std::endl;
        }
    }

    MPI_Finalize();
    return 0;
}
