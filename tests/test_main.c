#include "../src/loss_activations.h"
#include "test_grads.h"
#include "test_helpers.h"
#include "test_matlib.h"
#include <stdio.h>

int main(void) {
    // Test Helper
    Counts final_counters = {
        .counter = 0,
        .fail_counter = 0
    };

    // Test Matrix Library
    Counts matlib = test_matlib();
    final_counters.counter += matlib.counter;
    final_counters.fail_counter += matlib.fail_counter;

    // Test Grads
    Counts grads = test_grads();
    final_counters.counter += grads.counter;
    final_counters.fail_counter += grads.fail_counter;

    return final_counters.fail_counter > 0;
}