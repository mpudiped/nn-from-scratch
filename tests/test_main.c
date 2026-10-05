#include "test_matrix.h"
#include <stdio.h>

int main(void) {
    int counter = 0;
    int fail_counter = 0;
    const float tolerance = 1e-5f;
    
    // Part 1 of tests
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

    // Part 2 of tests
    Matrix t2 = init_matrix(2, 3);
    const float fill[6] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f};
    int count = sizeof(fill)/sizeof(fill[0]);
    fill_mat_from_arr(&t2, fill, count);

    fail_counter += check_val_at_index(&t2, 0, 2, 3.0f, "check at 0, 2");
    counter++;
    fail_counter += check_val_at_index(&t2, 1, 0, 4.0f, "check at 1, 0");
    counter++;
    fail_counter += check_val_at_index(&t2, 1, 2, 6.0f, "check at 1, 2");
    counter++;

    fail_counter += compare_matrix(&t2, &t2, tolerance, "compare with self");
    counter++;
    
    Matrix t3 = init_matrix(2, 3);
    fill_mat_from_arr(&t3, fill, count);
    fail_counter += compare_matrix(&t2, &t3, tolerance, "compare two equal matrices");
    counter++;
    free_matrix(&t2);
    free_matrix(&t3);
    
    printf("%d tests, %d failed\n", counter, fail_counter);
    return fail_counter > 0;
}