#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

Matrix mat_init(int rows, int cols) {
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

void mat_free(Matrix* m) {
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

void mat_print(const Matrix* m) {
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

void mat_transpose(Matrix* At, const Matrix* A) {
    assert(At != NULL && A != NULL);
    assert(At->mat != NULL && A->mat != NULL);
    assert(At->mat != A->mat);
    assert(At->rows == A->cols && At->cols == A->rows);
    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->cols; j++) {
            At->mat[j * At->cols + i] = A->mat[i * A->cols + j];
        }
    }
}

void mat_mult_at_b(Matrix* C, const Matrix* A, const Matrix* B) {
    assert(A != NULL && B != NULL && C != NULL);
    assert(A->mat != NULL && B->mat != NULL && C->mat != NULL);
    assert(C->mat != A->mat && C->mat != B->mat);
    assert(A->rows == B->rows);
    assert(C->rows == A->cols);
    assert(C->cols == B->cols);
    for (int i = 0; i < A->cols; i++) {
        for (int j = 0; j < B->cols; j++) {
            float curr = 0.0f;
            for (int k = 0; k < A->rows; k++) {
                curr += A->mat[k * A->cols + i] * B->mat[j + k * B->cols];
            }
            C->mat[i * C->cols + j] = curr;
        }
    }
}

void mat_mult_a_bt(Matrix* C, const Matrix* A, const Matrix* B) {
    assert(A != NULL && B != NULL && C != NULL);
    assert(A->mat != NULL && B->mat != NULL && C->mat != NULL);
    assert(C->mat != A->mat && C->mat != B->mat);
    assert(A->cols == B->cols);
    assert(C->rows == A->rows);
    assert(C->cols == B->rows);
    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < B->rows; j++) {
            float curr = 0.0f;
            for (int k = 0; k < A->cols; k++) {
                curr += A->mat[i * A->cols + k] * B->mat[k + j * B->cols];
            }
            C->mat[i * C->cols + j] = curr;
        }
    }
}

void mat_add_row_vec(Matrix* C, const Matrix* A, const Matrix* Bias) {
    assert(A != NULL && Bias != NULL && C != NULL);
    assert(A->mat != NULL && Bias->mat != NULL && C->mat != NULL);
    assert(Bias->rows == 1);
    assert(A->cols == Bias->cols);
    assert(A->rows == C->rows && A->cols == C->cols);
    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->cols; j++) {
            C->mat[i * C->cols + j] = A->mat[i * A->cols + j] + Bias->mat[j];
        }
    }
}

void mat_sum_cols(Matrix* B, const Matrix* A) {
    assert(A != NULL && B != NULL);
    assert(A->mat != NULL && B->mat != NULL);
    assert(B->cols == A->cols);
    assert(B->rows == 1);
    for (int i = 0; i < A->cols; i++) {
        float curr = 0.0f;
        for (int j = 0; j < A->rows; j++) {
            curr += A->mat[j * A->cols + i];
        }
        B->mat[i] = curr;
    }
}

void mat_element_mult(Matrix* C, const Matrix* A, const Matrix* B) {
    assert(A != NULL && B != NULL && C != NULL);
    assert(A->mat != NULL && B->mat != NULL && C->mat != NULL);
    assert(A->rows == B->rows && A->cols == B->cols);
    assert(C->rows == A->rows && C->cols == A->cols);
    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->cols; j++) {
            C->mat[i * C->cols +j] = A->mat[i * A->cols + j] * B->mat[i * B->cols + j];
        }
    }
}

void mat_apply(Matrix* B, const Matrix* A, float (*op)(float)) {
    assert(A != NULL && B != NULL);
    assert(A->mat != NULL && B->mat != NULL);
    assert(A->rows == B->rows && A->cols == B->cols);
    assert(op != NULL);
    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->cols; j++) {
            B->mat[i * B->cols + j] = op(A->mat[i * A->cols + j]);
        }
    }
}

void mat_scaled_subtract(Matrix* C, const Matrix* A, const Matrix* B, float s) {
    assert(A != NULL && B != NULL && C != NULL);
    assert(A->mat != NULL && B->mat != NULL && C->mat != NULL);
    assert(A->rows == B->rows && A->cols == B->cols);
    assert(C->rows == A->rows && C->cols == A->cols);
    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->cols; j++) {
            C->mat[i * C->cols + j] = A->mat[i * A->cols + j] - B->mat[i * B->cols + j] * s;
        }
    }
}