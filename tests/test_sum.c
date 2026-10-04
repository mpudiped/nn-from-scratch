#include "test_sum.h"
#include "../src/sum.h"
#include <stdio.h>

int test_array_sums(const int* arr, int n, int answer, char* name){
    int sum = sum_array(arr, n);
    if (sum == answer){
        printf("PASS %s\n", name);
    } else {
        printf("FAIL %s: expected %d, got %d\n", name, answer, sum);
    }
    return sum != answer;
}