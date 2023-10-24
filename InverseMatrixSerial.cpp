#include <iostream>
#include <vector>
#include <chrono>
using namespace std;

double determinant(vector<vector<double>> matrix, int n) {
    double det = 0;
    if (n == 1) return matrix[0][0];
    if (n == 2) return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
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
    cout << "Matrix size: " << n << ", Time taken by serial matrix inversion: " << duration.count() << " microseconds" << endl;
}

int main() {
    analyzeMatrix(3);
    analyzeMatrix(10);
  //analyzeMatrix(50); this is commented out as it takes a very high computational time ,however it can be decommented and program can be analyzed thereafter
    return 0;
}
