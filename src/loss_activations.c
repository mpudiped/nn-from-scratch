#include "loss_activations.h"
#include "matrix.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>

const float BCE_EPS = 1e-7f;

float ReLU(float x) {
    if (x > 0.0f) {
        return x;
    } else {
        return 0.0f;
    }
}

float ReLU_deriv(float x) {
    if (x > 0.0f) {
        return 1.0f;
    } else {
        return 0.0f;
    }
}

float sigmoid(float x) {
    return 1.0f / (1.0f + expf(-x));
}

float sigmoid_deriv(float x) {
    float sig = sigmoid(x);
    return sig * (1.0f - sig);
}

float binary_cross_entropy(float y, float p) {
    assert(!isnan(p));
    p = fmaxf(BCE_EPS, p);
    p = fminf(p, 1.0f - BCE_EPS);
    return -(y * logf(p) + (1 - y) * logf(1 - p));
}

float binary_cross_entropy_deriv(float y, float p) {
    return -(y * 1.0f / p - (1 - y) * 1.0f / (1 - p));
}

void mat_sigmoid_bce_grad(Matrix *Output, const Matrix *Truth, const Matrix *Probs) {
    assert(Output != NULL && Truth != NULL && Probs != NULL);
    assert(Output->mat != NULL && Truth->mat != NULL && Probs->mat != NULL);
    assert(Truth->rows == Probs->rows && Truth->cols == Probs->cols);
    assert(Output->rows == Truth->rows && Output->cols == Truth->cols);
    float m = (float)Truth->rows;
    for (int i = 0; i < Truth->rows; i++) {
        for (int j = 0; j < Truth->cols; j++) {
            Output->mat[i * Output->cols + j] =
                (Probs->mat[i * Probs->cols + j] - Truth->mat[i * Truth->cols + j]) / m;
        }
    }
}

float mean_bce(const Matrix *Truth, const Matrix *P) {
    assert(Truth != NULL && P != NULL);
    assert(Truth->mat != NULL && P->mat != NULL);
    assert(Truth->rows == P->rows && Truth->cols == P->cols);
    float sum = 0.0f;
    for (int i = 0; i < Truth->rows; i++) {
        for (int j = 0; j < Truth->cols; j++) {
            sum += binary_cross_entropy(Truth->mat[i * Truth->cols + j], P->mat[i * P->cols + j]);
        }
    }
    float average = sum / Truth->rows;
    return average;
}