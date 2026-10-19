#include "../src/matrix.h"

#ifndef TEST_HELPERS_H

#define TEST_HELPERS_H
typedef struct {
    int counter;
    int fail_counter;
} Counts;

int check_init(const Matrix *m, int exp_rows, int exp_cols, const char *test_name);

int check_index(const Matrix *m, const char *test_name);

int check_matrix_freed(const Matrix *m, const char *test_name);

int compare_matrix(const Matrix *produced, const Matrix *expected, float tolerance,
                   const char *test_name);

int check_val_at_index(const Matrix *m, int row, int col, float expected_value,
                       const char *test_name);

#endif