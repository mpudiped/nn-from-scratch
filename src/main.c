#include "matrix.h"
#include "activations.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    Matrix A = mat_init(2, 2);
    const float fill[] = {1.0, 2.0, 3.0, 4.0};
    fill_mat_from_arr(&A, fill, sizeof(fill)/sizeof(fill[0]));
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
    fill_mat_from_arr(&I, identity, sizeof(identity)/sizeof(identity[0]));
    Matrix N = mat_init(3, 3);
    mat_mult(&N, &I, &I);
    mat_print(&I);
    printf("\n");
    mat_print(&N);
    printf("\n");
    mat_free(&I);
    mat_free(&N);
}