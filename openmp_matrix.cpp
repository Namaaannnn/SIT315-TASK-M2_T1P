#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace std::chrono;

const int SIZE = 500;
vector<vector<int>> mat1(SIZE, vector<int>(SIZE));
vector<vector<int>> mat2(SIZE, vector<int>(SIZE));
vector<vector<int>> result(SIZE, vector<int>(SIZE));

// Fill the matrix with random values
void fillMatrix(vector<vector<int>> &mat) {
    for (auto &row : mat)
        for (auto &cell : row)
            cell = rand() % 100;
}

// Perform matrix multiplication using OpenMP
void computeProduct() {
    #pragma omp parallel for collapse(2)
    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE; c++) {
            for (int k = 0; k < SIZE; k++) {
                result[r][c] += mat1[r][k] * mat2[k][c];
            }
        }
    }
}

int main() {
    srand(time(0));

    fillMatrix(mat1);
    fillMatrix(mat2);

    auto begin = high_resolution_clock::now();
    computeProduct();
    auto finish = high_resolution_clock::now();

    double timeTaken = duration<double>(finish - begin).count();
    cout << fixed << setprecision(5) 
         << "Parallel Execution Time (OpenMP): " 
         << timeTaken << " seconds" << endl;

    return 0;
}
