#include "matrix.h"

#ifndef LAYER_H

#define LAYER_H
/*
 * Runs the forward pass of one layer of sigmoid neurons:
 * P = sigmoid(X * W + b).
 *
 * Each row of X is one example, and each column of W is one neuron.
 * If there are m examples with n inputs each, and p neurons:
 *   X is m x n, W is n x p, b is 1 x p, and P must already be m x p.
 *
 * None of the matrices may be NULL or empty, and P must not share its
 * memory with X or W. Anything else is a bug in the calling code and
 * stops the program with an assertion.
 *
 * Afterwards, every element of P has been overwritten with the
 * probability for that example and neuron, strictly between 0 and 1
 * apart from float rounding. P does not need to be zeroed first.
 *
 * The bias is added before the sigmoid. The values before the sigmoid
 * (Z) are not kept: this layer's backward_pass only needs P.
 *
 * X, W and b are not changed. No memory is allocated.
 */
void forward_pass(Matrix *P, const Matrix *X, const Matrix *W, const Matrix *b);
/*
 * Computes the gradients of the average binary cross-entropy loss with
 * respect to W and b, for a layer whose forward pass was forward_pass.
 *
 * ONLY valid when this is the output layer, its activation is the
 * sigmoid, and the loss is mean_bce. It relies on the simplified
 * gradient dL/dZ = (P - Truth) / m from mat_sigmoid_bce_grad.
 *
 * X is the same input that was given to forward_pass, P is what
 * forward_pass produced from it, and Truth holds the targets, 0 or 1.
 * With m examples, n inputs and p neurons:
 *   X is m x n, P and Truth are m x p,
 *   dW must already be n x p (the shape of W),
 *   db must already be 1 x p (the shape of b).
 *
 * None of the matrices may be NULL or empty. Anything else is a bug in
 * the calling code and stops the program with an assertion.
 *
 * Afterwards, every element of dW and db has been overwritten:
 *   dW = X^T * dZ   and   db = the column sums of dZ.
 * They do not need to be zeroed first.
 *
 * W and b are not needed and not changed. The caller applies the
 * update, for example with mat_scaled_subtract. The gradient with
 * respect to X is not computed, since nothing comes before this layer.
 *
 * X, P and Truth are not changed. Allocates a temporary m x p matrix
 * for dZ and frees it before returning.
 */
void backward_pass(Matrix *dW, Matrix *db, const Matrix *X, const Matrix *P, const Matrix *Truth);

#endif