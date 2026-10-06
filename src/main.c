#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    Matrix A = init_matrix(2, 2);
    const float fill[] = {1.0, 2.0, 3.0, 4.0};
    fill_mat_from_arr(&A, fill, sizeof(fill)/sizeof(fill[0]));
    print_matrix(&A);
    printf("\n");

    Matrix C = init_matrix(2, 2);
    mat_mult(&C, &A, &A);
    print_matrix(&C);
    printf("\n");

    free_matrix(&A);
    free_matrix(&C);

    Matrix I = init_matrix(3, 3);
    const float identity[] = {1, 0, 0, 0, 1, 0, 0, 0, 1};
    fill_mat_from_arr(&I, identity, sizeof(identity)/sizeof(identity[0]));
    Matrix N = init_matrix(3, 3);
    mat_mult(&N, &I, &I);
    print_matrix(&I);
    printf("\n");
    print_matrix(&N);
    printf("\n");
    free_matrix(&I);
    free_matrix(&N);
}