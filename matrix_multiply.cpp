#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;

const int SIZE = 500; // Adjusted matrix size for multiplication

// Function to initialize the matrix with random values between 0 and 99
void fillMatrix(vector<vector<int>> &mat) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            mat[i][j] = rand() % 100; // Random number between 0 and 99
        }
    }
}

// Function to perform matrix multiplication: C = A * B
void matrixMultiply(const vector<vector<int>> &X, const vector<vector<int>> &Y, vector<vector<int>> &Z) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            Z[i][j] = 0; // Initialize element to 0 before accumulation
            for (int k = 0; k < SIZE; k++) {
                Z[i][j] += X[i][k] * Y[k][j]; // Dot product of row and column
            }
        }
    }
}

int main() {
    srand(time(0)); // Seed for random number generation
    // Declare 3 matrices: matA, matB (input matrices), and matC (output matrix)
    vector<vector<int>> matA(SIZE, vector<int>(SIZE));
    vector<vector<int>> matB(SIZE, vector<int>(SIZE));
    vector<vector<int>> matC(SIZE, vector<int>(SIZE));

    // Fill matA and matB with random values
    fillMatrix(matA);
    fillMatrix(matB);

    // Measure the time taken for matrix multiplication
    auto startTime = high_resolution_clock::now(); // Start timer
    matrixMultiply(matA, matB, matC); // Perform matrix multiplication
    auto endTime = high_resolution_clock::now(); // End timer

    // Calculate and display the elapsed time
    duration<double> duration = endTime - startTime;
    cout << "Time Taken (Sequential): " << duration.count() << " seconds" << endl;

    return 0;
}