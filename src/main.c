#include "loss_activations.h"
#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    Matrix A = mat_init(2, 2);
    const float fill[] = {1.0, 2.0, 3.0, 4.0};
    fill_mat_from_arr(&A, fill, sizeof(fill) / sizeof(fill[0]));
    mat_print(&A);
    printf("\n");

    Matrix C = mat_init(2, 2);
    mat_mult(&C, &A, &A);
    mat_print(&C);
    printf("\n");

    mat_free(&A);
    mat_free(&C);

    Matrix I = mat_init(3, 3);
    const float identity[] = {1, 0, 0, 0, 1, 0, 0, 0, 1};
    fill_mat_from_arr(&I, identity, sizeof(identity) / sizeof(identity[0]));
    Matrix N = mat_init(3, 3);
    mat_mult(&N, &I, &I);
    mat_print(&I);
    printf("\n");
    mat_print(&N);
    printf("\n");
    mat_free(&I);
    mat_free(&N);

    Matrix And_Gate = mat_init(2, 1);
    const float And_Params[] = {0.5, 0.5};
    fill_mat_from_arr(&And_Gate, And_Params, sizeof(And_Params) / sizeof(And_Params[0]));
    Matrix input = mat_init(1, 2);
    input.mat[0] = 0;
    input.mat[1] = 1;
    Matrix output = mat_init(1, 1);
    mat_mult(&output, &input, &And_Gate);
    if (output.mat[0] <= 0.5) {
        printf("0\n");
    } else {
        printf("1\n");
    }

    Matrix pre_trans = mat_init(2, 3);
    const float pre_trans_fill[] = {1, 2, 3, 4, 5, 6};
    fill_mat_from_arr(&pre_trans, pre_trans_fill,
                      sizeof(pre_trans_fill) / sizeof(pre_trans_fill[0]));
    Matrix post_trans = mat_init(3, 2);
    mat_transpose(&post_trans, &pre_trans);
    mat_print(&pre_trans);
    printf("\n");
    mat_print(&post_trans);
}