#include "matrix.h"
#include "loss_activations.h"
#include <stdio.h>
#include <assert.h>

void forward_pass(Matrix* P, const Matrix* X, const Matrix* W, const Matrix* b) {
    assert(P != NULL && X != NULL && W != NULL && b != NULL);
    assert(X->cols == W->rows);
    assert(b->rows == 1);
    assert(b->cols == W->cols);
    assert(P->rows == X->rows && P->cols == W->cols);
    mat_mult(P, X, W);
    mat_add_row_vec(P, P, b);
    mat_apply(P, P, sigmoid);
}