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
        middle = size / 2;

    while (a[middle] == a[right] && a[middle] == a[left]) {
        if (a[middle] > a[left] && a[middle] > a[right]) {
            left = (middle - left) / 2;
            right = (middle - right) / 2;
        } else if (a[middle] <= right) {
            left = middle;
            middle = right - left / 2;
        } else {
            right = middle;
            middle = right - left / 2;
        }

    }
    return a[middle];
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
