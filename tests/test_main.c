#include "test_sum.h"
#include <stdio.h>

int main(void){
    int arr1[5] = {1, 2, 3, 4, 5};
    int ans1 = 15;
    int n1 = 5;
    char name1[30] = "five positives";

    int arr2[1] = {19};
    int ans2 = 19;
    int n2 = 1;
    char name2[30] = "single element";

    int ans3 = 0;
    int n3 = 0;
    char name3[30] = "empty array";

    int arr4[2] = {-2, 2};
    int ans4 = 0;
    int n4 = 2;
    char name4[30] = "negatives cancel out";

    int arr5[4] = {2, 3, 5, 7};
    int ans5 = 5;
    int n5 = 2;
    char name5[30] = "partial sum (first 2 of 4)";

    int fail_counter = 0;
    int counter = 5;
    fail_counter += test_array_sums(arr1, n1, ans1, name1);
    fail_counter += test_array_sums(arr2, n2, ans2, name2);
    fail_counter += test_array_sums(NULL, n3, ans3, name3);
    fail_counter += test_array_sums(arr4, n4, ans4, name4);
    fail_counter += test_array_sums(arr5, n5, ans5, name5);

    printf("%d tests, %d failed\n", counter, fail_counter);
    
    if (fail_counter > 0){
        return 1;
    }
    return 0;

}