#include <iostream>
#include <vector>
#include <chrono>
#include <omp.h>
using namespace std;

double determinant(vector<vector<double>> matrix, int n) {
    double det = 0;
    #pragma omp parallel for reduction(+:det)
    for (int p = 0; p < n; p++) {
        vector<vector<double>> subMatrix(n - 1, vector<double>(n - 1));
        for (int i = 1; i < n; i++) {
            int col = 0;
            for (int j = 0; j < n; j++) {
                if (j == p) continue;
                subMatrix[i-1][col] = matrix[i][j];
                col++;
            }
        }
        det += matrix[0][p] * determinant(subMatrix, n - 1) * (p % 2 == 0 ? 1 : -1);
    }
    return det;
}

void analyzeMatrix(int n) {
    vector<vector<double>> matrix(n, vector<double>(n, 1));
    for (int i = 0; i < n; ++i) matrix[i][i] = i + 1;

    auto start = chrono::high_resolution_clock::now();
    double det = determinant(matrix, n);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, micro> duration = end - start;
    cout << "Matrix size: " << n << ", Time taken by parallel matrix inversion: " << duration.count() << " microseconds" << endl;
}

int main() {
    analyzeMatrix(3);
    analyzeMatrix(10);
  //analyzeMatrix(50); this is commented out as it takes a very high computational time ,however it can be decommented and program can be analyzed thereafter
    return 0;
}
