#ifndef MATRIX_H

#define MATRIX_H
typedef struct {
    int rows;
    int cols;
    float* mat;
} Matrix;

/*
 * Creates a matrix with the given number of rows and columns.
 *
 * rows and cols must each be at least 1. Passing a smaller value is a
 * bug in the calling code and stops the program with an assertion.
 *
 * On success, every element starts at 0.0, and mat points to a block of
 * rows * cols floats stored in row-major order.
 *
 * If the memory cannot be allocated, the returned matrix has mat == NULL
 * and rows == cols == 0. Check mat before using the matrix.
 *
 * The caller owns the returned matrix and must release it with
 * free_matrix() exactly once.
 */
Matrix init_matrix(int rows, int cols);

/*
 * Releases the memory owned by a matrix and leaves it empty.
 *
 * m must not be NULL. Passing NULL is a bug in the calling code and
 * stops the program with an assertion.
 *
 * Afterwards, m->mat is NULL and m->rows and m->cols are 0. The struct
 * itself is not freed; it belongs to the caller.
 *
 * Safe to call more than once on the same matrix, and safe to call on
 * a matrix whose init_matrix() failed. In both cases it does nothing.
 *
 * Any other Matrix struct that was copied from this one still points
 * at the released memory and must not be used afterwards.
 */
void free_matrix(Matrix* m);

/*
 * Returns the position in m->mat of the element at row i, column j.
 *
 * m must not be NULL. i must be from 0 to m->rows - 1, and j from 0 to
 * m->cols - 1. Anything else is a bug in the calling code and stops
 * the program with an assertion.
 *
 * Elements are stored in row-major order: all of row 0, then all of
 * row 1, and so on. The position is therefore i * m->cols + j.
 *
 * Does not read or change the matrix's elements.
 */
int get_index(const Matrix* m, int row, int col);

/*
 * Prints the matrix to standard output, one row per line.
 *
 * m must not be NULL and must not be empty. Anything else is a bug in
 * the calling code and stops the program with an assertion.
 *
 * Each element is printed with %g and followed by a space. Each row
 * ends with a newline. Intended for debugging and for small matrices;
 * the columns are not aligned.
 *
 * Does not change the matrix.
 */
void print_matrix(const Matrix* m);

/*
 * Copies count values from arr into the matrix, in row-major order.
 *
 * m must not be NULL and must not be empty. arr must not be NULL and
 * must hold at least count floats. count must equal m->rows * m->cols.
 * Anything else is a bug in the calling code and stops the program
 * with an assertion.
 *
 * Afterwards, the first m->cols values of arr are row 0, the next
 * m->cols values are row 1, and so on. Every element of the matrix is
 * overwritten.
 *
 * The values are copied. The matrix does not keep a reference to arr,
 * so arr can be changed or released after the call.
 */
void fill_mat_from_arr(Matrix* m, const float* arr, int count);

/*
 * Computes the matrix product C = A * B.
 *
 * A, B and C must not be NULL, and none of them may be empty. C must
 * not share its memory with A or with B.
 *
 * The shapes must agree: A->cols must equal B->rows, C->rows must equal
 * A->rows, and C->cols must equal B->cols. So if A is m x k and B is
 * k x n, C must already be an m x n matrix.
 *
 * Anything else is a bug in the calling code and stops the program
 * with an assertion.
 *
 * Afterwards, every element of C has been overwritten:
 * C[i][j] is the sum over k of A[i][k] * B[k][j].
 * C does not need to be zeroed first.
 *
 * A and B are not changed. No memory is allocated.
 */
void mat_mult(Matrix* C, const Matrix* A, const Matrix* B);

/*
 * Writes the transpose of A into transposed.
 *
 * A and transposed must not be NULL, and neither may be empty.
 * transposed must not share its memory with A.
 *
 * The shapes must agree: transposed->rows must equal A->cols, and
 * transposed->cols must equal A->rows. So if A is m x n, transposed
 * must already be an n x m matrix.
 *
 * Anything else is a bug in the calling code and stops the program
 * with an assertion.
 *
 * Afterwards, every element of transposed has been overwritten:
 * transposed[j][i] is A[i][j]. The rows of A become the columns of
 * transposed.
 *
 * A is not changed. No memory is allocated.
 */
void mat_transpose(Matrix* transposed, const Matrix* A);

/*
 * Computes C = (A transposed) * B, without building the transpose of A.
 *
 * A, B and C must not be NULL, and none of them may be empty. C must
 * not share its memory with A or with B.
 *
 * The shapes must agree: A->rows must equal B->rows, C->rows must equal
 * A->cols, and C->cols must equal B->cols. So if A is k x m and B is
 * k x n, C must already be an m x n matrix.
 *
 * Anything else is a bug in the calling code and stops the program
 * with an assertion.
 *
 * Afterwards, every element of C has been overwritten:
 * C[i][j] is the sum over k of A[k][i] * B[k][j].
 * C does not need to be zeroed first.
 *
 * A and B are not changed. No memory is allocated.
 */
void mat_mult_at_b(Matrix* C, const Matrix* A, const Matrix* B);

/*
 * Computes C = A * (B transposed), without building the transpose of B.
 *
 * A, B and C must not be NULL, and none of them may be empty. C must
 * not share its memory with A or with B.
 *
 * The shapes must agree: A->cols must equal B->cols, C->rows must equal
 * A->rows, and C->cols must equal B->rows. So if A is m x k and B is
 * n x k, C must already be an m x n matrix.
 *
 * Anything else is a bug in the calling code and stops the program
 * with an assertion.
 *
 * Afterwards, every element of C has been overwritten:
 * C[i][j] is the sum over k of A[i][k] * B[j][k].
 * C does not need to be zeroed first.
 *
 * A and B are not changed. No memory is allocated.
 */
void mat_mult_a_bt(Matrix* C, const Matrix* A, const Matrix* B);
#endif