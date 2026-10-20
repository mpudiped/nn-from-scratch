#include "test_grads.h"
#include "../src/layer.h"
#include "../src/loss_activations.h"
#include "../src/matrix.h"
#include "test_helpers.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>

Counts test_grads(void) {
    int counter = 0;
    int fail_counter = 0;

    Matrix Weights = mat_init(2, 1);
    const float fill_weights[] = {0.5f, -0.3f};
    fill_mat_from_arr(&Weights, fill_weights, sizeof(fill_weights) / sizeof(fill_weights[0]));

    Matrix Input = mat_init(4, 2);
    const float fill_input[] = {0, 0, 0, 1, 1, 0, 1, 1};
    fill_mat_from_arr(&Input, fill_input, sizeof(fill_input) / sizeof(fill_input[0]));

    Matrix Bias = mat_init(1, 1);
    const float fill_bias[] = {0.8f};
    fill_mat_from_arr(&Bias, fill_bias, sizeof(fill_bias) / sizeof(fill_bias[0]));

    Matrix Truth = mat_init(4, 1);
    const float fill_truth[] = {0, 0, 0, 1};
    fill_mat_from_arr(&Truth, fill_truth, sizeof(fill_truth) / sizeof(fill_truth[0]));

    // Forward Pass
    Matrix Probs = mat_init(4, 1);
    forward_pass(&Probs, &Input, &Weights, &Bias);
    float loss = mean_bce(&Truth, &Probs);
    printf("Loss after forward pass: %g\n", loss);
    // Backward Pass
    Matrix dW = mat_init(2, 1);
    Matrix dB = mat_init(1, 1);
    backward_pass(&dW, &dB, &Input, &Probs, &Truth);

    // Calculate symmetric difference quotient for small h and compare to
    // backward_pass calculated gradients
    const float h = 1e-3f;
    const float threshold = 1e-2f;
    const float add_den = 1e-8f;
    for (int i = 0; i < Weights.rows; i++) {
        for (int j = 0; j < Weights.cols; j++) {
            counter++;
            float saved_weight = Weights.mat[i * Weights.cols + j];
            Weights.mat[i * Weights.cols + j] += h;
            forward_pass(&Probs, &Input, &Weights, &Bias);
            float loss_plus_h = mean_bce(&Truth, &Probs);
            Weights.mat[i * Weights.cols + j] = saved_weight;
            Weights.mat[i * Weights.cols + j] -= h;
            forward_pass(&Probs, &Input, &Weights, &Bias);
            float loss_minus_h = mean_bce(&Truth, &Probs);
            Weights.mat[i * Weights.cols + j] = saved_weight;

            float symmetric_grad = (loss_plus_h - loss_minus_h) / (2 * h);
            float relative_error =
                fabsf(symmetric_grad - dW.mat[i * dW.cols + j]) /
                (fmaxf(fabsf(symmetric_grad), fabsf(dW.mat[i * dW.cols + j])) + add_den);
            if (relative_error < threshold) {
                printf("PASS Relative gradient error (%g) is within tolerance for weight at row "
                       "%d, col %d\n",
                       relative_error, i, j);
            } else {
                fail_counter++;
                printf("FAIL Relative gradient error (%g) is greater than tolerance for weight "
                       "at row %d, col %d\n",
                       relative_error, i, j);
            }
        }
    }
    for (int i = 0; i < Bias.rows; i++) {
        for (int j = 0; j < Bias.cols; j++) {
            counter++;
            float saved_bias = Bias.mat[i * Bias.cols + j];
            Bias.mat[i * Bias.cols + j] += h;
            forward_pass(&Probs, &Input, &Weights, &Bias);
            float loss_plus_h = mean_bce(&Truth, &Probs);
            Bias.mat[i * Bias.cols + j] = saved_bias;
            Bias.mat[i * Bias.cols + j] -= h;
            forward_pass(&Probs, &Input, &Weights, &Bias);
            float loss_minus_h = mean_bce(&Truth, &Probs);
            Bias.mat[i * Bias.cols + j] = saved_bias;

            float symmetric_grad = (loss_plus_h - loss_minus_h) / (2 * h);
            float relative_error =
                fabsf(symmetric_grad - dB.mat[i * dB.cols + j]) /
                (fmaxf(fabsf(symmetric_grad), fabsf(dB.mat[i * dB.cols + j])) + add_den);
            if (relative_error < threshold) {
                printf("PASS Relative gradient error (%g) is within tolerance for bias at row "
                       "%d, col %d\n",
                       relative_error, i, j);
            } else {
                fail_counter++;
                printf("FAIL Relative gradient error (%g) is greater than tolerance for bias at "
                       "row %d, col %d\n",
                       relative_error, i, j);
            }
        }
    }

    mat_free(&Weights);
    mat_free(&Input);
    mat_free(&Bias);
    mat_free(&Truth);
    mat_free(&Probs);
    mat_free(&dW);
    mat_free(&dB);

    printf("%d tests, %d failed\n", counter, fail_counter);

    Counts counts = {.counter = counter, .fail_counter = fail_counter};

    return counts;
}