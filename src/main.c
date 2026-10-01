#include <stdio.h>
#include "greet.h"
#include "sum.h"

int main() {
    helloWorld();
    int x[4] = {1, 2, 3, 4};
    printf("4th element in array: %d\n", x[3]);
    printf("Sum: %d\n", sum_array(&x[0], 4));
}