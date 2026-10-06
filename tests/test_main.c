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
    const float fill[] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f};
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

    // Mat Mul Tests
    Matrix A = init_matrix(2, 3);
    const float fill_A[] = {1, -2, 3, 4, 0, -1};
    fill_mat_from_arr(&A, fill_A, sizeof(fill_A)/sizeof(fill_A[0]));
    Matrix B = init_matrix(3, 4);
    const float fill_B[] = {2, 1, 0, -1, 3, -2, 1, 4, 0, 5, -3, 2};
    fill_mat_from_arr(&B, fill_B, sizeof(fill_B)/sizeof(fill_B[0]));
    Matrix C = init_matrix(2, 4);
    mat_mult(&C, &A, &B);
    Matrix expected = init_matrix(2, 4);
    const float expected_vals[] = {-4, 20, -11, -3, 8, -1, 3, -6};
    fill_mat_from_arr(&expected, expected_vals, sizeof(expected_vals)/sizeof(expected_vals[0]));
    fail_counter += compare_matrix(&C, &expected, tolerance, "test mat mult");
    counter++;
    free_matrix(&A);
    free_matrix(&B);
    free_matrix(&C);

    // Test transpose
    Matrix og = init_matrix(2, 3);
    fill_mat_from_arr(&og, fill, sizeof(fill)/sizeof(fill[0]));
    Matrix og_trans_expected = init_matrix(3, 2);
    const float og_trans_arr[] = {1, 4, 2, 5, 3 ,6};
    fill_mat_from_arr(&og_trans_expected, og_trans_arr, sizeof(og_trans_arr)/sizeof(og_trans_arr[0]));
    
    Matrix og_trans = init_matrix(3, 2);
    mat_transpose(&og_trans, &og);
    fail_counter += compare_matrix(&og_trans, &og_trans_expected, tolerance, "test transpose");
    counter++;

    Matrix double_trans = init_matrix(2, 3);

    mat_transpose(&double_trans, &og_trans);
    fail_counter += compare_matrix(&double_trans, &og, tolerance, "transpose back");
    counter++;
    free_matrix(&og);
    free_matrix(&og_trans_expected);
    free_matrix(&og_trans);
    free_matrix(&double_trans);
    
    printf("%d tests, %d failed\n", counter, fail_counter);
    return fail_counter > 0;
}