#include <iostream>
#include <chrono>

long long serial_sum(int* arr, int size) {
    long long sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += arr[i];
    }
    return sum;
}

int main() {
    const int array_sizes[] = {100000, 500000, 1000000, 5000000, 10000000};
    for (const int N : array_sizes) {
        int* arr = new int[N];
        for (int i = 0; i < N; ++i) {
            arr[i] = i + 1;
        }
        
        auto start_time = std::chrono::high_resolution_clock::now();
        long long sum = serial_sum(arr, N);
        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration<double, std::micro>(end_time - start_time).count();

        std::cout << "Array Size: " << N << ", Serial Sum: " << sum << ", Time taken: " << duration << " microseconds" << std::endl;
        delete[] arr;
    }
    return 0;
}
