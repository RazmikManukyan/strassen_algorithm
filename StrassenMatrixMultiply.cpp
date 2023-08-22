#include <iostream>
#include <vector>

void addMatrices(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B, std::vector<std::vector<int>>& C, int size) {
    for(int i = 0; i < size ; ++i) {
        for(int j = 0; j < size; ++j) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

void subtractMatrices(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B, std::vector<std::vector<int>>& C, int size){
    for(int i = 0; i < size; ++i) {
        for(int j = 0; j < size; ++j) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}

void strassenMatrixMultiply(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B, std::vector<std::vector<int>>& C, int size) {
    //base case
    if(size == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int newSize = size / 2;

    std::vector<std::vector<int>> A11(newSize, std::vector<int>(newSize));
    std::vector<std::vector<int>> A12(newSize, std::vector<int>(newSize));
    std::vector<std::vector<int>> A21(newSize, std::vector<int>(newSize));
    std::vector<std::vector<int>> A22(newSize, std::vector<int>(newSize));

    std::vector<std::vector<int>> B11(newSize, std::vector<int>(newSize));
    std::vector<std::vector<int>> B12(newSize, std::vector<int>(newSize));
    std::vector<std::vector<int>> B21(newSize, std::vector<int>(newSize));
    std::vector<std::vector<int>> B22(newSize, std::vector<int>(newSize));

    std::vector<std::vector<int>> C11(newSize, std::vector<int>(newSize));
    std::vector<std::vector<int>> C12(newSize, std::vector<int>(newSize));
    std::vector<std::vector<int>> C21(newSize, std::vector<int>(newSize));
    std::vector<std::vector<int>> C22(newSize, std::vector<int>(newSize));

//dividing the matrices into sub-matrices:
    for(int i = 0; i < newSize; ++i) {
        for(int j = 0; j < newSize; ++j) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i + newSize][j];
            B22[i][j] = B[i + newSize][j + newSize];
        }
    }

    std::vector<std::vector<int>> P1(newSize, std::vector<int>(newSize));
    std::vector<std::vector<int>> P2(newSize, std::vector<int>(newSize));
    std::vector<std::vector<int>> P3(newSize, std::vector<int>(newSize));
    std::vector<std::vector<int>> P4(newSize, std::vector<int>(newSize));
    std::vector<std::vector<int>> P5(newSize, std::vector<int>(newSize));
    std::vector<std::vector<int>> P6(newSize, std::vector<int>(newSize));
    std::vector<std::vector<int>> P7(newSize, std::vector<int>(newSize));

    std::vector<std::vector<int>> aResult(newSize, std::vector<int>(newSize));
    std::vector<std::vector<int>> bResult(newSize, std::vector<int>(newSize));

// Calculating p1 to p7:
    addMatrices(A11, A22, aResult, newSize);//A11 + A22
    addMatrices(B11, B22, bResult, newSize);//B11 + B22
    strassenMatrixMultiply(aResult, bResult, P1, newSize);// p1 = (a11+a22) * (b11+b22)

    addMatrices(A21, A22, aResult, newSize);//A21 + A22
    strassenMatrixMultiply(aResult, B11, P2, newSize);// p2 = (a21+a22) * (b11)


    subtractMatrices(B12, B22, bResult, newSize);//B12 - B22
    strassenMatrixMultiply(A11, bResult, P3, newSize);//P3 = (A11)*(B12 - B22)

    subtractMatrices(B21, B11, bResult, newSize);//B21 - B11
    strassenMatrixMultiply(A22, bResult, P4, newSize);//P4 = (A22)*(B21 - B11)

    addMatrices(A11, A12, aResult, newSize);//A11 + A12
    strassenMatrixMultiply(aResult, B22, P5, newSize);//P5 = (A11+A12)*(B22)

    subtractMatrices(A21, A11, aResult, newSize);//A21 - A11
    addMatrices(B11, B12, bResult, newSize);//B11 + B12
    strassenMatrixMultiply(aResult, bResult, P6, newSize);//P6 = (A21-A11)*(B11+B12)

    subtractMatrices(A12, A22, aResult, newSize);//A12 - A22
    addMatrices(B12, B22, bResult, newSize);//B12 + B22
    strassenMatrixMultiply(aResult, bResult, P7, newSize);//P7=(A12-A22)*(B12*B22)

    addMatrices(P3, P5, C12, newSize);//C12 = P3 + P5
    addMatrices(P2, P4, C21, newSize);//C21 = P2 + P4

    addMatrices(P1, P4, aResult, newSize);//P1 + P4
    addMatrices(aResult, P7, bResult, newSize);//P1 + P4 + P7
    subtractMatrices(bResult, P5, C11, newSize);//C11 = P1 + P4 - P5 + P7

    addMatrices(P1, P3, aResult, newSize);//P1 + P3
    addMatrices(aResult, P6, bResult, newSize);//P1 + P3 + P6
    subtractMatrices(bResult, P2, C22, newSize);//C22 = P1 + P3 - P2 + P6

    // Grouping the results obtained in a single matrix:
    for(int i = 0; i < newSize; ++i) {
        for(int j = 0; j < newSize; ++j) {
            C[i][j] = C11[i][j];
            C[i][j + newSize] = C12[i][j];
            C[i + newSize][j] = C21[i][j];
            C[i +newSize][j + newSize] = C22[i][j];
        }
    }
}

