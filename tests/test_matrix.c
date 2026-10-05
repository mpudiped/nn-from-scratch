#include "test_matrix.h"
#include "../src/matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int check_init(const Matrix* m, int exp_rows, int exp_cols, const char* test_name) {
  if (m == NULL) {
    printf("FAIL %s: struct pointer is NULL\n", test_name);
    return 1;
  }
  if (m->mat == NULL) {
    printf("FAIL %s: matrix pointer is NULL\n", test_name);
    return 1;  
  }
  if (exp_rows != m->rows || exp_cols != m->cols) {
    printf("FAIL %s: expected shape %dx%d, got %dx%d\n", test_name, exp_rows, exp_cols, m->rows, m->cols);
    return 1;
  }

  for (int i = 0; i < m->rows; i++) {
    for (int j = 0; j < m->cols; j++) {
      float curr = m->mat[get_index(m, i, j)];
      if (curr != 0.0f) {
        printf("FAIL %s: element at row %d, column %d is %g, expected 0\n", test_name, i, j, curr);
        return 1;
      }
    }
  }
  printf("PASS %s\n", test_name);
  return 0;
}

int check_index(const Matrix* m, const char* test_name) {
  if (m == NULL) {
    printf("FAIL %s: struct pointer is NULL\n", test_name);
    return 1;
  }
  if (m->mat == NULL) {
    printf("FAIL %s: matrix pointer is NULL\n", test_name);
    return 1;
  }
  int counter = 0;
  for (int i = 0; i < m->rows; i++) {
    for (int j = 0; j < m->cols; j++) {
      int curr = get_index(m, i, j);
      if (curr != counter) {
        printf("FAIL %s: expected element index %d from row %d col %d, got element index %d\n", test_name, counter, i, j, curr);
        return 1;
      }
      counter++;
    }
  }
  printf("PASS %s\n", test_name);
  return 0;
}

int check_matrix_freed(const Matrix* m, const char* test_name) {
  if (m == NULL) {
    printf("FAIL %s: struct pointer is NULL\n", test_name);
    return 1;
  }
  if (m->mat != NULL) {
    printf("FAIL %s: matrix pointer is not NULL\n", test_name);
    return 1;
  }
  if (m->rows != 0 || m->cols != 0) {
    printf("FAIL %s: expected 0 for rows and 0 for cols, got %d for rows and %d for cols\n", test_name, m->rows, m->cols);
    return 1;
  }
  printf("PASS %s\n", test_name);
  return 0;
}

int compare_matrix(const Matrix* produced, const Matrix* expected, float tolerance, const char* test_name) {
  if (produced == NULL || produced->mat == NULL) {
    printf("FAIL %s: produced matrix pointer is NULL\n", test_name);
    return 1;
  }
  if (expected == NULL || expected->mat == NULL) {
    printf("FAIL %s: expected matrix pointer is NULL\n", test_name);
    return 1;
  }
  if (produced->rows != expected->rows || produced->cols != expected->cols) {
    printf("FAIL %s: matrix should be of size %dx%d, instead got %dx%d\n", test_name, expected->rows, expected->cols, produced->rows, produced->cols);
    return 1;
  }
  for (int i = 0; i < produced->rows * produced->cols; i++) {
    if (!(fabsf(produced->mat[i] - expected->mat[i]) <= tolerance)) {
      printf("FAIL %s: expected value is %g, differing from produced value of %g, on row %d, col %d\n",
        test_name, expected->mat[i], produced->mat[i], i / produced->cols, i % produced->cols);
      return 1;
    }
  }
  printf("PASS %s\n", test_name);
  return 0;
}

int check_val_at_index(const Matrix* m, int row, int col, float expected_value, const char* test_name) {
  if (m == NULL || m->mat == NULL) {
    printf("FAIL %s: matrix pointer is NULL\n", test_name);
    return 1;
  }
  float val_at_ind = m->mat[get_index(m, row, col)];
  if (val_at_ind != expected_value) {
    printf("FAIL %s: expected value %g at row %d, col %d, instead got %g\n", test_name, expected_value, row, col, val_at_ind);
    return 1;
  }
  printf("PASS %s\n", test_name);
  return 0;
}

