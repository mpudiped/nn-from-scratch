#include "test_matrix.h"
#include <stdio.h>

int main(void) {
    int counter = 0;
    int fail_counter = 0;

    Matrix t1 = init_matrix(3, 4);
    
    fail_counter += check_init(&t1, 3, 4, "init 3x4");
    counter++;

    fail_counter += check_index(&t1, "index check for init 3x4");
    counter++;

    free_matrix(&t1);
    fail_counter += check_matrix_freed(&t1, "first free check");
    counter++;
    
    free_matrix(&t1);
    fail_counter += check_matrix_freed(&t1, "second free check");
    counter++;

    printf("%d tests, %d failed\n", counter, fail_counter);
    
    return fail_counter > 0;
}