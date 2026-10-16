#include "test_grads.h"
#include "../src/matrix.h"
#include "../src/loss_activations.h"
#include <stdio.h>
#include <assert.h>

int test_grads(void) {
    Matrix weights = mat_init(2, 1);
    const float fill_weights[] = {0.5, -0.3};
    fill_mat_from_arr(&weights, fill_weights, sizeof(fill_weights)/sizeof(fill_weights[0]));

    Matrix input = mat_init(1, 2);
    const float fill_input[] = {0, 0};
    fill_mat_from_arr(&input, fill_input, sizeof(fill_input)/sizeof(fill_input[0]));

    Matrix Bias = mat_init(1, 1);
    const float fill_bias[] = {0.8};
    fill_mat_from_arr(&Bias, fill_bias, sizeof(fill_bias)/sizeof(fill_bias[0]));

    // Forward Pass
    Matrix Z = mat_init(1, 1);
    mat_mult(&Z, &input, &weights);
    mat_add_row_vec(&Z, &Z, &Bias);
    mat_apply(&Z, &Z, sigmoid);
    mat_print(&Z);
    printf("\n");


    // Backward Pass
    Matrix Truth = mat_init(1, 1);
    const float fill_truth[] = {0};
    fill_mat_from_arr(&Truth, fill_truth, sizeof(fill_truth)/sizeof(fill_truth[0]));
    Matrix dZ = mat_init(1, 1);
    mat_sigmoid_bce_grad(&dZ, &Truth, &Z);
    Matrix dW = mat_init(2, 1);
    mat_mult_at_b(&dW, &input, &dZ);
    Matrix dB = mat_init(1, 1);
    mat_sum_cols(&dB, &dZ);
    mat_print(&dW);
    printf("\n");
    mat_print(&dB);

    return 0;
}