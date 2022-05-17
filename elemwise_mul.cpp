#include <random>

#define SIZE 1000000000

// Generate array of random doubles
void gen_rand_dbl(double *arr, int size) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 1);
    for (int i = 0; i < size; i++) {
        arr[i] = dis(gen);
    }
}

// Multiply two arrays
void elemwise_mul(double *arr1, double *arr2, double *arr3, int size) {
    for (int i = 0; i < size; i++) {
        arr3[i] = arr1[i] * arr2[i];
    }
}

// Function that prints array
void print_arr(double *arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%f\n", arr[i]);
    }
}


int main() {
    double *arr1 = new double[SIZE];
    double *arr2 = new double[SIZE];
    double *arr3 = new double[SIZE];

    gen_rand_dbl(arr1, SIZE);
    gen_rand_dbl(arr2, SIZE);
    elemwise_mul(arr1, arr2, arr3, SIZE);

    print_arr(arr3, SIZE);

    return 0;
}