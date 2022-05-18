#include <fstream>
#include <iostream>
#include <random>
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

// Multiply two arrays
void elemwise_mul(double *arr1, double *arr2, double *arr3, int size)
{
    for (int i = 0; i < size; i++)
    {
        arr3[i] = arr1[i] * arr2[i];
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

    double t1 = funcTime(elemwise_mul, arr1, arr2, arr3, arr_size);
    write_time_to_file(t1);
    std::cout << "Time taken for " << arr_size << " elements: " << t1 << " nanoseconds" << std::endl;
}

int main()
{
    // Array of array sizes from 1000 to 100 million
    int arr_sizes[] = {1000, 10000, 100000, 1000000, 10000000, 100000000};

    for (int size : arr_sizes)
    {
        test_mul(size);
    }

    return 0;
}