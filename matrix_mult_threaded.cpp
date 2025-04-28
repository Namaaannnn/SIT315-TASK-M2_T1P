#include <iostream>
#include <vector>
#include <pthread.h>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <iomanip>
#include <thread>

using namespace std;
using namespace std::chrono;

int matrixSize;
int totalThreads;
vector<vector<int>> matA, matB, resultMat;

// This function fills a matrix with random numbers between 0 and 99
void fillMatrix(vector<vector<int>> &mat) {
    for (auto &row : mat) {
        for (auto &val : row) {
            val = rand() % 100;
        }
    }
}

// Thread function to multiply part of the matrix
void* multiplySection(void* arg) {
    int begin = *(int*)arg;
    int finish = begin + matrixSize / totalThreads;

    for (int i = begin; i < finish; i++) {
        for (int j = 0; j < matrixSize; j++) {
            for (int k = 0; k < matrixSize; k++) {
                resultMat[i][j] += matA[i][k] * matB[k][j];
            }
        }
    }

    return nullptr;
}

// Function to perform the experiment with given matrix size and number of threads
void performTest(int size, int threads) {
    matrixSize = size;
    totalThreads = threads;

    // Resize matrices according to current size
    matA.assign(matrixSize, vector<int>(matrixSize));
    matB.assign(matrixSize, vector<int>(matrixSize));
    resultMat.assign(matrixSize, vector<int>(matrixSize));

    fillMatrix(matA);
    fillMatrix(matB);

    pthread_t threadsList[totalThreads];
    int rowStart[totalThreads];

    auto startTime = high_resolution_clock::now();

    // Create threads and assign each part
    for (int i = 0; i < totalThreads; i++) {
        rowStart[i] = i * (matrixSize / totalThreads);
        pthread_create(&threadsList[i], nullptr, multiplySection, &rowStart[i]);
    }

    // Wait for all threads to finish
    for (int i = 0; i < totalThreads; i++) {
        pthread_join(threadsList[i], nullptr);
    }

    auto endTime = high_resolution_clock::now();
    double timeTaken = duration<double>(endTime - startTime).count();

    cout << "Matrix Size: " << matrixSize
         << " | Threads: " << totalThreads
         << " | Time: " << fixed << setprecision(5)
         << timeTaken << " sec" << endl;
}

int main() {
    srand(time(0)); // Set seed for random values

    vector<int> sizes = {100, 200, 500}; // Different matrix sizes to test
    int maxThreadsAvailable = thread::hardware_concurrency(); // Number of cores
    vector<int> threadsToTry = {2, 4, 8, maxThreadsAvailable}; // Different thread counts

    // Loop over sizes and thread counts
    for (int s : sizes) {
        for (int t : threadsToTry) {
            performTest(s, t);
        }
        cout << "-------------------------------------" << endl;
    }

    return 0;
}