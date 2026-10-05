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
#endif