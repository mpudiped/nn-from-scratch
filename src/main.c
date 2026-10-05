#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    Matrix m = init_matrix(5, 5);
    m.mat[get_index(&m, 0, 0)] = 1;
    m.mat[get_index(&m, 1, 1)] = 1;
    m.mat[get_index(&m, 2, 2)] = 1;
    m.mat[get_index(&m, 3, 3)] = 1;
    m.mat[get_index(&m, 4, 4)] = 1;
    print_matrix(&m);
}