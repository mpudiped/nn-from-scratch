#include "test_helpers.h"
#include "test_grads.h"
#include "test_matlib.h"
#include "../src/loss_activations.h"
#include <stdio.h>

int main(void) {
    // Test Helper
    Counter counts = test_matlib();

    // Test Grads
    test_grads();

    printf("%d tests, %d failed\n", counts.counter, counts.fail_counter);
    return counts.fail_counter > 0;
}