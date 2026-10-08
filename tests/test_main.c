#include "test_matrix.h"
#include "../src/matrix.h"
#include "../src/activations.h"
#include <stdio.h>

int main(void) {
    int counter = 0;
    int fail_counter = 0;
    const float tolerance = 1e-5f;
    
    // Part 1 of tests
    Matrix t1 = mat_init(3, 4);
    
    fail_counter += check_init(&t1, 3, 4, "init 3x4");
    counter++;

    fail_counter += check_index(&t1, "index check for init 3x4");
    counter++;

    mat_free(&t1);
    fail_counter += check_matrix_freed(&t1, "first free check");
    counter++;
    
    mat_free(&t1);
    fail_counter += check_matrix_freed(&t1, "second free check");
    counter++;

    // Part 2 of tests
    Matrix t2 = mat_init(2, 3);
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
    
    Matrix t3 = mat_init(2, 3);
    fill_mat_from_arr(&t3, fill, count);
    fail_counter += compare_matrix(&t2, &t3, tolerance, "compare two equal matrices");
    counter++;
    mat_free(&t2);
    mat_free(&t3);

    // Mat Mul Tests
    Matrix A = mat_init(2, 3);
    const float fill_A[] = {1, -2, 3, 4, 0, -1};
    fill_mat_from_arr(&A, fill_A, sizeof(fill_A)/sizeof(fill_A[0]));
    Matrix B = mat_init(3, 4);
    const float fill_B[] = {2, 1, 0, -1, 3, -2, 1, 4, 0, 5, -3, 2};
    fill_mat_from_arr(&B, fill_B, sizeof(fill_B)/sizeof(fill_B[0]));
    Matrix C = mat_init(2, 4);
    mat_mult(&C, &A, &B);
    Matrix expected = mat_init(2, 4);
    const float expected_vals[] = {-4, 20, -11, -3, 8, -1, 3, -6};
    fill_mat_from_arr(&expected, expected_vals, sizeof(expected_vals)/sizeof(expected_vals[0]));
    fail_counter += compare_matrix(&C, &expected, tolerance, "test mat mult");
    counter++;
    mat_free(&A);
    mat_free(&B);
    mat_free(&C);
    mat_free(&expected);

    // Test transpose
    Matrix og = mat_init(2, 3);
    fill_mat_from_arr(&og, fill, sizeof(fill)/sizeof(fill[0]));
    Matrix og_trans_expected = mat_init(3, 2);
    const float og_trans_arr[] = {1, 4, 2, 5, 3 ,6};
    fill_mat_from_arr(&og_trans_expected, og_trans_arr, sizeof(og_trans_arr)/sizeof(og_trans_arr[0]));
    
    Matrix og_trans = mat_init(3, 2);
    mat_transpose(&og_trans, &og);
    fail_counter += compare_matrix(&og_trans, &og_trans_expected, tolerance, "test transpose");
    counter++;

    Matrix double_trans = mat_init(2, 3);

    mat_transpose(&double_trans, &og_trans);
    fail_counter += compare_matrix(&double_trans, &og, tolerance, "transpose back");
    counter++;
    mat_free(&og);
    mat_free(&og_trans_expected);
    mat_free(&og_trans);
    mat_free(&double_trans);

    // Test Mat Mult with Transpose
    const float fill8[] = {1, 2, 3, 4, 5, 6, 7, 8};
    Matrix mat_og1 = mat_init(2, 3);
    fill_mat_from_arr(&mat_og1, fill, sizeof(fill)/sizeof(fill[0]));
    Matrix mat_og2 = mat_init(2, 4);
    fill_mat_from_arr(&mat_og2, fill8, sizeof(fill8)/sizeof(fill8[0]));
    Matrix mat_trans1 = mat_init(3, 2);
    mat_transpose(&mat_trans1, &mat_og1);
    Matrix at_expected = mat_init(3, 4);
    mat_mult(&at_expected, &mat_trans1, &mat_og2);
    
    Matrix trans_at = mat_init(3, 4);
    mat_mult_at_b(&trans_at, &mat_og1, &mat_og2);
    fail_counter += compare_matrix(&trans_at, &at_expected, tolerance, "mat mult at");
    counter++;  
    mat_free(&mat_og2);
    mat_free(&mat_trans1);
    mat_free(&trans_at);
    mat_free(&at_expected);

    const float fill12[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    Matrix mat_og3 = mat_init(4, 3);
    fill_mat_from_arr(&mat_og3, fill12, sizeof(fill12)/sizeof(fill12[0]));
    Matrix mat_trans3 = mat_init(3, 4);
    mat_transpose(&mat_trans3, &mat_og3);
    Matrix bt_expected = mat_init(2, 4);
    mat_mult(&bt_expected, &mat_og1, &mat_trans3);

    Matrix trans_bt = mat_init(2, 4);
    mat_mult_a_bt(&trans_bt, &mat_og1, &mat_og3);
    
    fail_counter += compare_matrix(&trans_bt, &bt_expected, tolerance, "mat mult bt");
    counter++;
    mat_free(&mat_og1);
    mat_free(&mat_og3);
    mat_free(&mat_trans3);
    mat_free(&trans_bt);
    mat_free(&bt_expected);

    // Test bias vector add
    Matrix pre_bias = mat_init(4, 3);
    const float pre_bias_vals[] = {10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21};
    fill_mat_from_arr(&pre_bias, pre_bias_vals, sizeof(pre_bias_vals)/sizeof(pre_bias_vals[0]));
    Matrix post_bias = mat_init(4, 3);
    const float post_bias_vals[] = {11, 13, 15, 14, 16, 18, 17, 19, 21, 20, 22, 24};
    fill_mat_from_arr(&post_bias, post_bias_vals, sizeof(post_bias_vals)/sizeof(post_bias_vals[0]));
    Matrix bias = mat_init(1, 3);
    const float bias_fill[] = {1, 2, 3};
    fill_mat_from_arr(&bias, bias_fill, sizeof(bias_fill)/sizeof(bias_fill[0]));
    
    Matrix bias_output = mat_init(4, 3);
    mat_add_row_vec(&bias_output, &pre_bias, &bias);
    fail_counter += compare_matrix(&bias_output, &post_bias, tolerance, "test adding bias to new mat");
    counter++;

    mat_add_row_vec(&pre_bias, &pre_bias, &bias);
    fail_counter += compare_matrix(&pre_bias, &post_bias, tolerance, "test in place adding bias");
    counter++;

    mat_free(&bias_output);
    mat_free(&pre_bias);
    mat_free(&post_bias);
    mat_free(&bias);

    // Test column add
    Matrix test_col_add = mat_init(2, 3);
    fill_mat_from_arr(&test_col_add, fill, sizeof(fill)/sizeof(fill[0]));
    Matrix expected_col_add = mat_init(1, 3);
    const float expected_add[] = {5, 7, 9};
    fill_mat_from_arr(&expected_col_add, expected_add, sizeof(expected_add)/sizeof(expected_add[0]));

    Matrix produced_add = mat_init(1, 3);
    mat_sum_cols(&produced_add, &test_col_add);

    fail_counter += compare_matrix(&produced_add, &expected_col_add, tolerance, "test column sum");
    counter++;

    mat_free(&test_col_add);
    mat_free(&expected_col_add);
    mat_free(&produced_add);

    // Test mat elementwise mult
    Matrix test_elementwise1 = mat_init(2, 3);
    Matrix test_elementwise2 = mat_init(2, 3);
    fill_mat_from_arr(&test_elementwise1, fill, sizeof(fill)/sizeof(fill[0]));
    const float elementwise_fill[] = {2, 3, 4, 5, 6, 7};
    fill_mat_from_arr(&test_elementwise2, elementwise_fill, sizeof(elementwise_fill)/sizeof(elementwise_fill[0]));
    Matrix elementwise_result = mat_init(2, 3);
    mat_element_mult(&elementwise_result, &test_elementwise1, &test_elementwise2);
    Matrix elementwise_expected = mat_init(2, 3);
    const float elementwise_ans[] = {2, 6, 12, 20, 30, 42};
    fill_mat_from_arr(&elementwise_expected, elementwise_ans, sizeof(elementwise_ans)/sizeof(elementwise_ans[0]));

    fail_counter += compare_matrix(&elementwise_result, &elementwise_expected, tolerance, "test elementwise mult");
    counter++;

    mat_free(&test_elementwise1);
    mat_free(&test_elementwise2);
    mat_free(&elementwise_result);
    mat_free(&elementwise_expected);

    // Test mat apply
    Matrix pre_apply = mat_init(2, 3);
    const float fill_pre_apply[] = {1, -2, 4, -6, 8, -3};
    fill_mat_from_arr(&pre_apply, fill_pre_apply, sizeof(fill_pre_apply)/sizeof(fill_pre_apply[0]));
    Matrix post_apply = mat_init(2, 3);
    mat_apply(&post_apply, &pre_apply, ReLU);
    Matrix expected_post_apply = mat_init(2, 3);
    const float expected_post_vals[] = {1, 0, 4, 0, 8, 0};
    fill_mat_from_arr(&expected_post_apply, expected_post_vals, sizeof(expected_post_vals)/sizeof(expected_post_vals[0]));

    fail_counter += compare_matrix(&post_apply, &expected_post_apply, tolerance, "test mat apply");
    counter++;

    mat_free(&pre_apply);
    mat_free(&post_apply);
    mat_free(&expected_post_apply);
    
    printf("%d tests, %d failed\n", counter, fail_counter);
    return fail_counter > 0;
}