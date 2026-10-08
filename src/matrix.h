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
 * mat_free() exactly once.
 */
Matrix mat_init(int rows, int cols);

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
 * a matrix whose mat_init() failed. In both cases it does nothing.
 *
 * Any other Matrix struct that was copied from this one still points
 * at the released memory and must not be used afterwards.
 */
void mat_free(Matrix* m);

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
void mat_print(const Matrix* m);

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
 * Writes the transpose of A into At.
 *
 * A and At must not be NULL, and neither may be empty.
 * At must not share its memory with A.
 *
 * The shapes must agree: At->rows must equal A->cols, and
 * At->cols must equal A->rows. So if A is m x n, At
 * must already be an n x m matrix.
 *
 * Anything else is a bug in the calling code and stops the program
 * with an assertion.
 *
 * Afterwards, every element of At has been overwritten:
 * At[j][i] is A[i][j]. The rows of A become the columns of
 * At.
 *
 * A is not changed. No memory is allocated.
 */
void mat_transpose(Matrix* At, const Matrix* A);

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

/*
 * Adds the row vector Bias to every row of A, and stores the result in C.
 *
 * A, Bias and C must not be NULL, and none of them may be empty.
 *
 * The shapes must agree: Bias must have exactly one row, Bias->cols must
 * equal A->cols, and C must have the same number of rows and columns
 * as A. So if A is m x n, Bias must be 1 x n and C must already be an
 * m x n matrix.
 *
 * Anything else is a bug in the calling code and stops the program
 * with an assertion.
 *
 * Afterwards, every element of C has been overwritten:
 * C[i][j] is A[i][j] + Bias[0][j].
 * C does not need to be zeroed first.
 *
 * C may be the same matrix as A. In that case A is updated in place.
 * Otherwise A is not changed. Bias is never changed. No memory is
 * allocated.
 */
void mat_add_row_vec(Matrix* C, const Matrix* A, const Matrix* Bias);

/*
 * Sums each column of A, and stores the totals in B.
 *
 * A and B must not be NULL, and neither may be empty.
 *
 * The shapes must agree: B must have exactly one row, and B->cols must
 * equal A->cols. So if A is m x n, B must already be a 1 x n matrix.
 *
 * Anything else is a bug in the calling code and stops the program
 * with an assertion.
 *
 * Afterwards, every element of B has been overwritten:
 * B[0][j] is the sum over i of A[i][j].
 * B does not need to be zeroed first.
 *
 * A is not changed. No memory is allocated.
 */
void mat_sum_cols(Matrix* B, const Matrix* A);

/*
 * Multiplies A and B element by element, and stores the result in C.
 * This is not matrix multiplication: each element is multiplied only
 * by the element in the same position.
 *
 * A, B and C must not be NULL, and none of them may be empty.
 *
 * The shapes must agree: A, B and C must all have the same number of
 * rows and the same number of columns.
 *
 * Anything else is a bug in the calling code and stops the program
 * with an assertion.
 *
 * Afterwards, every element of C has been overwritten:
 * C[i][j] is A[i][j] * B[i][j].
 * C does not need to be zeroed first.
 *
 * C may be the same matrix as A or as B. In that case that input is
 * updated in place. Otherwise A and B are not changed. No memory is
 * allocated.
 */
void mat_element_mult(Matrix* C, const Matrix* A, const Matrix* B);

/*
 * Applies op to every element of A, and stores the results in B.
 *
 * A and B must not be NULL, and neither may be empty. op must not be
 * NULL. It must be a function that takes one float and returns one
 * float, such as an activation function or its derivative.
 *
 * The shapes must agree: B must have the same number of rows and
 * columns as A.
 *
 * Anything else is a bug in the calling code and stops the program
 * with an assertion.
 *
 * Afterwards, every element of B has been overwritten:
 * B[i][j] is op(A[i][j]).
 * B does not need to be zeroed first.
 *
 * op is called exactly once for each element.
 *
 * B may be the same matrix as A. In that case A is updated in place.
 * Otherwise A is not changed. No memory is allocated.
 */
void mat_apply(Matrix* B, const Matrix* A, float (*op)(float));

/*
 * Computes C = A - s * B, element by element.
 *
 * A, B and C must not be NULL, and none of them may be empty.
 *
 * The shapes must agree: A, B and C must all have the same number of
 * rows and the same number of columns.
 *
 * Anything else is a bug in the calling code and stops the program
 * with an assertion.
 *
 * Afterwards, every element of C has been overwritten:
 * C[i][j] is A[i][j] - s * B[i][j].
 * C does not need to be zeroed first.
 *
 * s may be any value. A negative s adds a multiple of B instead.
 *
 * C may be the same matrix as A or as B. In that case that input is
 * updated in place. Otherwise A and B are not changed. No memory is
 * allocated.
 *
 * Typical use is the gradient descent update, with the weights as both
 * C and A, their gradient as B, and the learning rate as s.
 */
void mat_scaled_subtract(Matrix* C, const Matrix* A, const Matrix* B, float s);
#endif