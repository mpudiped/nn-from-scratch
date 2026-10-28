#ifndef LAYER_H
#define LAYER_H

#include "matrix.h"

/*
 * Computes the linear part of one layer: Output = Input * Weights + Bias.
 * No activation is applied; the caller applies one afterwards if needed.
 * Used for every layer, hidden or output.
 *
 * Each row is one example, and each column of Weights is one neuron.
 * With m examples, n inputs per example and p neurons:
 *   Input is m x n, Weights is n x p, Bias is 1 x p,
 *   and Output must already be m x p.
 *
 * None of the matrices may be NULL or empty, and Output must not share
 * its memory with Input or Weights. Anything else is a bug in the
 * calling code and stops the program with an assertion.
 *
 * Afterwards, every element of Output has been overwritten:
 * Output[i][j] is the sum over k of Input[i][k] * Weights[k][j],
 * plus Bias[0][j]. Output does not need to be zeroed first.
 *
 * Input, Weights and Bias are not changed. No memory is allocated.
 */
void linear_forward(Matrix *Output, const Matrix *Input, const Matrix *Weights,
                    const Matrix *Bias);

/*
 * Computes the gradients for the linear part of one layer, given the
 * gradient arriving at its output. Used for every layer, hidden or
 * output.
 *
 * Output_Grads is dL/dZ: the gradient with respect to this layer's
 * linear output Z, BEFORE any activation. For a hidden layer, the caller
 * must first turn the gradient from the layer above (dL/dA) into dL/dZ
 * using the activation's derivative. For the sigmoid output layer with
 * mean_bce, it comes from mat_sigmoid_bce_grad.
 *
 * Input and Weights must be the same matrices this layer used in
 * linear_forward, with Weights not yet updated.
 *
 * With m examples, n inputs and p neurons:
 *   Input is m x n, Weights is n x p, Output_Grads is m x p,
 *   Weight_Grads must already be n x p (the shape of Weights),
 *   Bias_Grads must already be 1 x p (the shape of Bias),
 *   Input_Grads, if given, must already be m x n (the shape of Input).
 *
 * Input_Grads is optional: pass NULL to skip it. That is the usual
 * choice for the first layer, whose input is the data and has nothing
 * below it to pass a gradient to.
 *
 * Apart from Input_Grads, none of the matrices may be NULL or empty.
 * Weight_Grads must not share memory with Input or Output_Grads, and
 * Input_Grads must not share memory with Output_Grads or Weights.
 * Anything else is a bug in the calling code and stops the program
 * with an assertion.
 *
 * Afterwards, every element of the outputs has been overwritten:
 *   Weight_Grads = Input^T * Output_Grads
 *   Bias_Grads   = the column sums of Output_Grads
 *   Input_Grads  = Output_Grads * Weights^T   (dL/dInput, if requested)
 * For a layer above the first, Input_Grads is dL/dA for the layer
 * below it. None of the outputs need to be zeroed first.
 *
 * Input, Weights and Output_Grads are not changed. No memory is
 * allocated.
 */
void linear_backward(Matrix *Weight_Grads, Matrix *Bias_Grads, Matrix *Input_Grads,
                     const Matrix *Input, const Matrix *Weights,
                     const Matrix *Output_Grads);

/*
 * Runs the forward pass of one layer of sigmoid neurons:
 * P = sigmoid(X * W + b). This is linear_forward followed by the
 * sigmoid, applied to P in place.
 *
 * With m examples, n inputs and p neurons:
 *   X is m x n, W is n x p, b is 1 x p, and P must already be m x p.
 *
 * None of the matrices may be NULL or empty, and P must not share its
 * memory with X or W. Anything else is a bug in the calling code and
 * stops the program with an assertion.
 *
 * Afterwards, every element of P has been overwritten with the
 * probability for that example and neuron, between 0 and 1. The values
 * before the sigmoid (Z) are not kept, since backward_pass only needs P.
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
 * X and W must be the same matrices given to forward_pass, with W not
 * yet updated, P is what forward_pass produced from them, and Truth
 * holds the targets, 0 or 1. With m examples, n inputs and p neurons:
 *   X is m x n, W is n x p, P and Truth are m x p,
 *   dW must already be n x p (the shape of W),
 *   dB must already be 1 x p (the shape of b).
 *
 * None of the matrices may be NULL or empty. Anything else is a bug in
 * the calling code and stops the program with an assertion.
 *
 * Afterwards, every element of dW and dB has been overwritten with the
 * gradients for W and b. They do not need to be zeroed first. The
 * gradient with respect to X is not computed, so this function cannot
 * pass a gradient to a layer below; a network with hidden layers uses
 * mat_sigmoid_bce_grad and linear_backward directly instead.
 *
 * The caller applies the update, for example with mat_scaled_subtract.
 *
 * X, W, P and Truth are not changed. Allocates a temporary m x p matrix
 * for dL/dZ and frees it before returning.
 */
void backward_pass(Matrix *dW, Matrix *dB, const Matrix *X, const Matrix *W,
                   const Matrix *P, const Matrix *Truth);

#endif