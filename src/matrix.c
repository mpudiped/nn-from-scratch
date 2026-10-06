#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

Matrix init_matrix(int rows, int cols) {
    assert(rows > 0 && cols > 0);
    Matrix matrix = {
        .rows = rows,
        .cols = cols,
        .mat = calloc(((size_t) rows)*cols, sizeof(float))
    };
    if (matrix.mat == NULL) {
        matrix.rows = 0;
        matrix.cols = 0;
    }
    return matrix;
}

void free_matrix(Matrix* m) {
    assert(m != NULL);
    free(m->mat);
    m->mat = NULL;
    m->rows = 0;
    m->cols = 0;
}

int get_index(const Matrix* m, int row, int col) {
    assert(m != NULL);
    assert(row >= 0 && row < m->rows && col >= 0 && col < m->cols);
    return row * m->cols + col;
}

void print_matrix(const Matrix* m) {
    assert(m != NULL && m->mat != NULL);
    for(int i = 0; i < m->rows; i++) {
        for(int j = 0; j < m->cols; j++) {
            printf("%g ", m->mat[get_index(m, i, j)]);
        }
        printf("\n");
    }
}

void fill_mat_from_arr(Matrix* m, const float* arr, int count) {
    assert(m != NULL && m->mat != NULL);
    assert(arr != NULL);
    assert(count == m->rows * m->cols);
    for (int i = 0; i < count; i++) {
        m->mat[i] = arr[i];
    }
}

void mat_mult(Matrix* C, const Matrix* A, const Matrix* B) {
    assert(A != NULL && B != NULL && C != NULL);
    assert(A->mat != NULL && B->mat != NULL && C->mat != NULL);
    assert(C->mat != A->mat && C->mat != B->mat);
    assert(A->cols == B->rows);
    assert(C->rows == A->rows);
    assert(C->cols == B->cols);
    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < B->cols; j++) {
            float curr = 0.0f;
            for (int k = 0; k < A->cols; k++) {
                curr += A->mat[i * A->cols + k] * B->mat[j + k * B->cols];
            }
            C->mat[i * C->cols + j] = curr;
        }
    }
}

void mat_transpose(Matrix* transposed, const Matrix* A) {
    assert(transposed != NULL && A != NULL);
    assert(transposed->mat != NULL && A->mat != NULL);
    assert(transposed->mat != A->mat);
    assert(transposed->rows == A->cols && transposed->cols == A->rows);
    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->cols; j++) {
            transposed->mat[j * transposed->cols + i] = A->mat[i * A->cols + j];
        }
    }
}