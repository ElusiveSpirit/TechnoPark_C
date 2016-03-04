//
//  main.c
//  A3_2
//
//  Created by Konstantin on 03.03.16.
//  Copyright (c) 2016 Manyakhin. All rights reserved.
//

/*    TASK
********************************************************
​       Дан массив целых чисел А[0..n­1]. Известно, что
    на интервале [0, m] значения массива строго
    возрастают, а на интервале [m, n­1] строго убывают.
    Найти m за O(log m).
    n ≤ 10000.
********************************************************
*/


#include "stdio.h"
#include "stdlib.h"
#include "errno.h"


int findMax(size_t size, int a[size]) {
    if (size == 0) return 0;

    int left = 0,
        right = size - 1,
        middle = size / 2,
        lm = (middle - left) / 2,
        rm = middle + (right - middle) / 2;

    while (right - left > 2) {
        if ((a[middle] > a[lm] && a[middle] > a[rm])) {
            left = lm;
            right = rm;
        } else if (middle == rm || middle == lm) {
            if (a[middle] <= a[right]) {
                left = middle;
                middle = right - 1;
            } else {
                middle = left + 1;
                right = middle;
            }
        } else if (a[middle] <= a[rm]) {
            left = middle;
            middle = rm;
        } else {
            right = middle;
            middle = lm;
        }
        lm = left + (middle - left) / 2;
        rm = middle + (right - middle) / 2;
    }
    if (a[middle] < a[left])
        return left;
    if (a[middle] < a[right])
        return right;
    return middle;
}

int main() {
    // Ввод массивов
    int size = 0;
    if (scanf("%d\n", &size) == 0)
        return 0;
    int a[size];
    for (size_t i = 0; i < size; i++) {
        if (scanf("%d", &a[i]) == 0)
            return 0;
    }

    printf("%d\n", findMax(size, a));

    return 0;
}
