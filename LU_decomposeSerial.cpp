#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

void lu_decomposition_serial(vector<vector<double>>& A, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            A[j][i] /= A[i][i];
            for (int k = i + 1; k < n; ++k) {
                A[j][k] -= A[j][i] * A[i][k];
            }
        }
    }
}

int main() {
    vector<int> sizes = {100, 200, 500, 1000};
    for (int n : sizes) {
        vector<vector<double>> A(n, vector<double>(n, 1.0)); // Initialize the matrix

        auto start = chrono::high_resolution_clock::now();
        lu_decomposition_serial(A, n);
        auto stop = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);

        cout << "Matrix size: " << n << ", Time taken by serial LU decomposition: " << duration.count() << " microseconds" << endl;
    }

    return 0;
}
