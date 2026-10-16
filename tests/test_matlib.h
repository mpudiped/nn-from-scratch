#ifndef TEST_MATLIB_H

#define TEST_MATLIB_H
typedef struct {
    int counter;
    int fail_counter;
} Counter;

Counter test_matlib(void);
#endif