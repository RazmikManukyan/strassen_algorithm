# Strassen Matrix Multiplication Algorithm

This repository contains an implementation of the Strassen matrix multiplication algorithm in C++. The Strassen algorithm is an efficient divide-and-conquer method for multiplying two matrices, reducing the time complexity from O(n^3) to approximately O(n^2.81).

## Usage

1. Clone the repository:

   ```bash
   git clone https://github.com/your-username/strassen-matrix-multiplication.git
   cd strassen-matrix-multiplication
   ```

2. Compile the C++ code using a C++ compiler, for example, g++:

   ```bash
   g++ strassen_matrix_multiplication.cpp -o strassen_matrix_multiply
   ```

3. Run the compiled executable:

   ```bash
   ./strassen_matrix_multiply
   ```

## Implementation Details

The code provided in `strassen_matrix_multiplication.cpp` demonstrates the implementation of the Strassen matrix multiplication algorithm. The algorithm follows these steps:

1. If the matrix size is 1, perform a simple multiplication and store the result in the output matrix.
2. Divide the input matrices A and B into sub-matrices.
3. Compute seven products recursively (P1 to P7) using the divided sub-matrices.
4. Calculate the four quadrants of the result matrix C based on the products P1 to P7.

## Example

The repository includes an example in the `main` function of how to use the implemented Strassen algorithm to multiply two matrices. You can modify the input matrices and matrix size in the `main` function to see how the algorithm works with different inputs.

```cpp
    int size = 4; // Change this to the desired matrix size

    // Initialize matrices A and B
    vector<vector<int>> A = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };

    vector<vector<int>> B = {
        {16, 15, 14, 13},
        {12, 11, 10, 9},
        {8, 7, 6, 5},
        {4, 3, 2, 1}
    };

    vector<vector<int>> C(size, vector<int>(size, 0));

    strassenMatrixMultiply(A, B, C, size);

    // Print the result matrix C
    cout << "Result matrix C:" << endl;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            cout << C[i][j] << "\t";
        }
        cout << endl;
    }
```

## Contributions

Contributions to this repository are welcome! If you find any issues or have suggestions for improvements, feel free to create a pull request.

