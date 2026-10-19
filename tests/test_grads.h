#include "../src/matrix.h"
#include "test_helpers.h"

#ifndef TEST_GRADS_H

#define TEST_GRADS_H

/*
 * Checks the gradients from backward_pass against numerical estimates.
 *
 * Sets up a single sigmoid neuron on the four AND examples, with fixed
 * starting values: weights 0.5 and -0.3, bias 0.8. Runs the forward
 * and backward passes once to get the analytic gradients dW and db.
 *
 * Then, for each weight and the bias separately, nudges that one
 * parameter by +h and -h (h = 1e-3), recomputes the average loss with
 * mean_bce each time, and estimates its gradient with the symmetric
 * difference quotient (L+ - L-) / 2h. The parameter is restored before
 * the next one is checked.
 *
 * Each estimate is compared with the matching analytic gradient using
 * the relative error |a - n| / (max(|a|, |n|) + 1e-8). A parameter
 * passes if that is below 1e-2. Correct gradients give about 1e-4 in
 * float; a wrong formula typically gives 0.1 or more.
 *
 * Prints PASS or FAIL with the relative error for each parameter, and
 * returns the number of checks run and the number that failed.
 *
 * Allocates and frees its own matrices.
 */
Counts test_grads(void);

#endif