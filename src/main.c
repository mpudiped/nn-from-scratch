#include "loss_activations.h"
#include "matrix.h"
#include "layer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    const float fill_X[] = {0, 0, 0, 1, 1, 0, 1, 1};
    Matrix X = mat_from_arr(4, 2, fill_X, ARRAY_LEN(fill_X));

    const float fill_W[] = {0.5f, -0.3f};
    Matrix W = mat_from_arr(2, 1, fill_W, ARRAY_LEN(fill_W));

    const float fill_b[] = {1.3f};
    Matrix b = mat_from_arr(1, 1, fill_b, ARRAY_LEN(fill_b));

    Matrix Truth;

    char target[] = "Or";
    if (strcmp(target, "And") == 0) {
        const float fill_Truth[] = {0, 0, 0, 1};
        Truth = mat_from_arr(4, 1, fill_Truth, ARRAY_LEN(fill_Truth));
    } else if (strcmp(target, "Or") == 0) {
        const float fill_Truth[] = {0, 1, 1, 1};
        Truth = mat_from_arr(4, 1, fill_Truth, ARRAY_LEN(fill_Truth));
    } else {
        fprintf(stderr, "Error: target is neither \"And\" or \"Or\", it is %s\n", target);
        return 1;
    }

    Matrix P = mat_init(4, 1);
    Matrix dW = mat_init(2, 1);
    Matrix db = mat_init(1, 1);

    const int steps = 10000;
    const float learning_rate = 1.0f;

    forward_pass(&P, &X, &W, &b);
    printf("Starting loss is %g\n", mean_bce(&Truth, &P));
    for (int i = 0; i < steps; i++) {
        forward_pass(&P, &X, &W, &b);
        backward_pass(&dW, &db, &X, &P, &Truth);
        mat_scaled_subtract(&W, &W, &dW, learning_rate);
        mat_scaled_subtract(&b, &b, &db, learning_rate);
        if (i % 500 == 0 && i != 0) {
            printf("Loss after step %d is %g\n", i, mean_bce(&Truth, &P));
        }
    }

    forward_pass(&P, &X, &W, &b);
    printf("\n%g, %g, %g, %g\n", P.mat[0], P.mat[1], P.mat[2], P.mat[3]);

    mat_free(&X);
    mat_free(&W);
    mat_free(&b);
    mat_free(&Truth);
    mat_free(&P);
    mat_free(&dW);
    mat_free(&db);

    return 0;
}