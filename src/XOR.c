#include "matrix.h"
#include "layer.h"

void xor_forward_pass(void) {
    Matrix X = mat_init(4, 2);
    
    Matrix W1 = mat_init(2, 2);
    Matrix B1 = mat_init(1, 2);

    Matrix W2 = mat_init(2, 2);
    Matrix B2 = mat_init(1, 1);

    Matrix Probabilities = mat_init(4, 1);
    Matrix Truth = mat_init(4, 1);
    // // forward_pass(&, const Matrix *X, const Matrix *W, const Matrix *b)
}