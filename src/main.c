#include "greet.h"
#include "sum.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    hello_world();
    int x[4] = {-1, -2, -3, -4};
    int new_arr_size = 5;
    int* new_arr = malloc(new_arr_size*sizeof(int));
    if (new_arr == NULL) return 1;
    for(int i = 0; i < new_arr_size; i++){
        new_arr[i] = i;
    }
    printf("4th element in array: %d\n", x[3]);
    printf("Sum: %d\n", sum_array(x, 4));
    printf("Malloced arr sum: %d\n", sum_array(new_arr, 6));
}