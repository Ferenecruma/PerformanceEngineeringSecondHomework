#pragma GCC target("avx2")
#pragma GCC optimize("O3")

#include <iostream>
#include <random>
#include <x86intrin.h>
#include <bits/stdc++.h>
#include <chrono>
#include <utility>

#define duration(a) std::chrono::duration_cast<std::chrono::nanoseconds>(a).count()
#define timeNow() std::chrono::high_resolution_clock::now()

typedef std::chrono::high_resolution_clock::time_point TimeVar;

template <typename F, typename... Args>
double funcTime(F func, Args &&...args)
{
    TimeVar t1 = timeNow();
    func(std::forward<Args>(args)...);
    return duration(timeNow() - t1);
}

// Given two double arrays, multiply them elementwise using SIMD intrinsics
// and store the result in the third array
void elemwise_mul_intrinsinc(double *arr1, double *arr2, double *arr3, int size) {
    for (int i = 0; i < size; i += 8) {
        __m256d a = _mm256_loadu_pd(arr1 + i);
        __m256d b = _mm256_loadu_pd(arr2 + i);
        __m256d c = _mm256_mul_pd(a, b);
        _mm256_storeu_pd(arr3 + i, c);
    }
}

void write_time_to_file(double time){
    std::ofstream outfile;
    outfile.open("nanoseconds.txt", std::ios_base::app);
    outfile << time << std::endl;
}

void test_mul(int arr_size)
{
    double *arr1 = new double[arr_size];
    double *arr2 = new double[arr_size];
    double *arr3 = new double[arr_size];

    double t1 = funcTime(elemwise_mul_intrinsinc, arr1, arr2, arr3, arr_size);
    write_time_to_file(t1);
    std::cout << "Time taken for " << arr_size << " elements: " << t1 << " nanoseconds" << std::endl;
}

int main() {
    // Array of array sizes from 1000 to 100 million
    int arr_sizes[] = {1000, 10000, 100000, 1000000, 10000000, 100000000};

    for (int size : arr_sizes)
    {
        test_mul(size);
    }

    return 0;
}