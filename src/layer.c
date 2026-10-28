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
    linear_forward(P, X, W, b);
    mat_apply(P, P, sigmoid);
}

void backward_pass(Matrix *dW, Matrix *dB, const Matrix *X, const Matrix *W, const Matrix *P, const Matrix *Truth) {
    assert(dW != NULL && dB != NULL && X != NULL && W != NULL && P != NULL && Truth != NULL);
    assert(P->rows == Truth->rows && P->cols == Truth->cols);
    assert(X->rows == P->rows);
    assert(X->cols == dW->rows);
    assert(W->rows == X->cols && W->cols == P->cols);
    assert(dB->cols == dW->cols);
    Matrix dZ = mat_init(P->rows, P->cols);
    mat_sigmoid_bce_grad(&dZ, Truth, P);
    linear_backward(dW, dB, NULL, X, W, &dZ);
    mat_free(&dZ);
}

void linear_forward(Matrix *Output, const Matrix *Input, const Matrix *Weights,
                    const Matrix *Bias) {
    assert(Output != NULL && Input != NULL && Weights != NULL && Bias != NULL);
    assert(Input->rows == Output->rows);
    assert(Input->cols == Weights->rows);
    assert(Weights->cols == Bias->cols);
    assert(Output->cols == Weights->cols);
    assert(Bias->rows == 1);
    mat_mult(Output, Input, Weights);
    mat_add_row_vec(Output, Output, Bias);
}

void linear_backward(Matrix *Weight_Grads, Matrix *Bias_Grads, Matrix *Input_Grads, const Matrix *Input,
                     const Matrix *Weights, const Matrix *Output_Grads) {
    assert(Weight_Grads != NULL && Bias_Grads != NULL && Input != NULL && Weights != NULL && Output_Grads != NULL);
    assert(Input->cols == Weights->rows);
    if (Input_Grads != NULL) {
        assert(Input_Grads->rows == Input->rows && Input_Grads->cols == Input->cols);
    }
    assert(Weight_Grads->rows == Weights->rows && Weight_Grads->cols == Weights->cols);
    assert(Output_Grads->rows == Input->rows && Output_Grads->cols == Weights->cols);
    assert(Bias_Grads->cols == Weights->cols);
    mat_mult_at_b(Weight_Grads, Input, Output_Grads);
    mat_sum_cols(Bias_Grads, Output_Grads);
    if (Input_Grads != NULL) {
        mat_mult_a_bt(Input_Grads, Output_Grads, Weights);
    }
}