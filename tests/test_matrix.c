#include "test_matrix.h"
#include "../src/matrix.h"
#include <stdio.h>
#include <stdlib.h>

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

