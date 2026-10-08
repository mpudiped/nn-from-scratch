#include "activations.h"
#include "math.h"

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