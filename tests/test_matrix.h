#include "../src/matrix.h"

#ifndef TEST_MATRIX_H

#define TEST_MATRIX_H

int check_init(const Matrix* m, int exp_rows, int exp_cols, const char* test_name);

int check_index(const Matrix* m, const char* test_name);

int check_matrix_freed(const Matrix* m, const char* test_name);
#endif