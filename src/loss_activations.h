#include "matrix.h"

#ifndef LOSS_ACTIVATIONS_H

#define LOSS_ACTIVATIONS_H

/*
 * The ReLU activation: returns x if x is positive, and 0 otherwise.
 *
 * Works for any float x.
 */
float ReLU(float x);

/*
 * The derivative of ReLU with respect to its input.
 *
 * x is the input to ReLU (z), not its output. Returns 1 if x is
 * positive, and 0 otherwise.
 *
 * ReLU has no derivative at exactly 0. This function returns 0 there,
 * which is the usual convention.
 */
float ReLU_deriv(float x);

/*
 * The sigmoid activation: returns 1 / (1 + e^(-x)), a value between
 * 0 and 1.
 *
 * Works for any float x and never returns NaN. Because of float
 * rounding, the result is exactly 1.0 for x above about 17, and
 * exactly 0.0 for x below about -88.
 */
float sigmoid(float x);

/*
 * The derivative of sigmoid with respect to its input.
 *
 * x is the input to sigmoid (z), not its output. Returns
 * sigmoid(x) * (1 - sigmoid(x)), which is at most 0.25, at x = 0.
 *
 * Returns exactly 0 where sigmoid(x) rounds to 0 or 1, even though the
 * true derivative there is a tiny positive number.
 */
float sigmoid_deriv(float x);

/*
 * The binary cross-entropy loss for one example:
 * -(y * ln(p) + (1 - y) * ln(1 - p)).
 *
 * y is the target, 0 or 1. p is the predicted probability that the
 * target is 1, normally the output of sigmoid.
 * 
 * p must not be NaN. A NaN p means something earlier has gone wrong,
 * such as NaN in the weights, and stops the program with an assertion
 * instead of being clamped to an ordinary-looking value.
 *
 * p is clamped to [1e-7, 1 - 1e-7] before the logs are taken, so the
 * result is always finite, even when p is exactly 0 or 1.
 *
 * The result is never negative. It is close to 0 when p is close to y,
 * and grows without limit as p moves towards the wrong answer.
 *
 * This is the loss for a single example. To get the loss for a batch,
 * the caller averages it over the examples. That must match the
 * averaging in mat_sigmoid_bce_grad.
 */
float binary_cross_entropy(float y, float p);

/*
 * The derivative of binary_cross_entropy with respect to p:
 * -y / p + (1 - y) / (1 - p).
 *
 * This is NOT the gradient used in training. Training needs the
 * gradient with respect to z, the input to the sigmoid, which is
 * mat_sigmoid_bce_grad. Multiplying this function by sigmoid_deriv
 * gives the same value mathematically, but produces NaN when p rounds
 * to 0 or 1.
 *
 * Use it for gradient checking at ordinary values of p. It divides by
 * p and by 1 - p, so it is infinite or NaN when p is exactly 0 or 1.
 */
float binary_cross_entropy_deriv(float y, float p);

/*
 * Computes the gradient of the average binary cross-entropy loss with
 * respect to Z, the input to the sigmoid, for a whole batch, and stores
 * it in Output.
 *
 * ONLY valid when Probs = sigmoid(Z) and the loss is binary
 * cross-entropy. With any other activation or loss, the result is wrong
 * and no error is reported.
 *
 * Each row is one example. Probs holds the predicted probabilities and
 * Truth holds the targets, 0 or 1.
 *
 * Output, Truth and Probs must not be NULL, and none of them may be
 * empty. All three must have the same number of rows and columns.
 *
 * Anything else is a bug in the calling code and stops the program
 * with an assertion.
 *
 * Afterwards, every element of Output has been overwritten:
 * Output[i][j] is (Probs[i][j] - Truth[i][j]) / m, where m is the
 * number of rows, the batch size. Dividing by m matches a loss that is
 * the average over the batch.
 * Output does not need to be zeroed first.
 *
 * Contains no logs or divisions by p, so it is always finite, including
 * when a probability has rounded to exactly 0 or 1.
 *
 * Output may be the same matrix as Truth or Probs. Otherwise they are
 * not changed. No memory is allocated.
 */
void mat_sigmoid_bce_grad(Matrix* Output, const Matrix* Truth, const Matrix* Probs);

float mean_bce(const Matrix* Truth, const Matrix* P);
#endif