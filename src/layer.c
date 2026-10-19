#include "layer.h"
#include "loss_activations.h"
#include "matrix.h"
#include <assert.h>
#include <stdio.h>

void forward_pass(Matrix *P, const Matrix *X, const Matrix *W, const Matrix *b) {
    assert(P != NULL && X != NULL && W != NULL && b != NULL);
    assert(X->cols == W->rows);
    assert(b->rows == 1);
    assert(b->cols == W->cols);
    assert(P->rows == X->rows && P->cols == W->cols);
    mat_mult(P, X, W);
    mat_add_row_vec(P, P, b);
    mat_apply(P, P, sigmoid);
}

void backward_pass(Matrix *dW, Matrix *db, const Matrix *X, const Matrix *P, const Matrix *Truth) {
    assert(dW != NULL && db != NULL && X != NULL && P != NULL && Truth != NULL);
    assert(P->rows == Truth->rows && P->cols == Truth->cols);
    assert(X->rows == P->rows);
    assert(X->cols == dW->rows);
    assert(db->cols == dW->cols);
    Matrix dZ = mat_init(P->rows, P->cols);
    mat_sigmoid_bce_grad(&dZ, Truth, P);
    mat_mult_at_b(dW, X, &dZ);
    mat_sum_cols(db, &dZ);
    mat_free(&dZ);
}