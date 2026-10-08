#include "activations.h"

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