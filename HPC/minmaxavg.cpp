#include <stdio.h>
#include <stdlib.h>
#include <limits.h>  // Include <limits.h> for INT_MAX and INT_MIN
#include <omp.h>

#define VECTOR_SIZE 10000
#define NUM_THREADS 4

int main() {
    int vector[VECTOR_SIZE];
    int i;
    int sum = 0;
    int min = INT_MAX;
    int max = INT_MIN;

    // Initialize the vector with random values
    for (i = 0; i < VECTOR_SIZE; i++) {
        vector[i] = rand() % 100; // Generate random numbers between 0 and 99
    }

    // Parallel region using OpenMP
    #pragma omp parallel for num_threads(NUM_THREADS) reduction(+:sum) reduction(min:min) reduction(max:max)
    for (i = 0; i < VECTOR_SIZE; i++) {
        sum += vector[i];

        if (vector[i] < min) {
            min = vector[i];
        }

        if (vector[i] > max) {
            max = vector[i];
        }
    }

    // Calculate average
    double average = (double)sum / VECTOR_SIZE;

    // Output results
    printf("Sum: %d\n", sum);
    printf("Average: %.2f\n", average);
    printf("Min: %d\n", min);
    printf("Max: %d\n", max);

    return 0;
}
