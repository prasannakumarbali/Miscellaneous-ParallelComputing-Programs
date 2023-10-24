#include <iostream>
#include <chrono>
#include <omp.h>

int main() {
    const int array_sizes[] = {100000, 500000, 1000000, 5000000, 10000000};
    omp_set_num_threads(4); // Set to the number of cores you have
    
    for (const int N : array_sizes) {
        int* arr = new int[N];
        for (int i = 0; i < N; ++i) {
            arr[i] = i + 1;
        }
        
        long long sum = 0;
        auto start_time = std::chrono::high_resolution_clock::now();
        
        #pragma omp parallel for reduction(+:sum)
        for (int i = 0; i < N; ++i) {
            sum += arr[i];
        }
        
        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration<double, std::micro>(end_time - start_time).count();

        std::cout << "Array Size: " << N << ", Parallel Sum: " << sum << ", Time taken: " << duration << " microseconds" << std::endl;
        delete[] arr;
    }

    return 0;
}
