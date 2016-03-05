//
//  main.c
//  A2_3
//
//  Created by Konstantin on 04.03.16.
//  Copyright (c) 2016 Manyakhin. All rights reserved.
//

/*    TASK
********************************************************
        Даны два строго возрастающих массива целых
    чисел A[0..n) и B[0..m) и число fi. Найти количество
    таких пар индексов (i, j), что A[i] + B[j] = k.
    Время работы O(n + m).
    n, m ≤ 100000.
********************************************************
*/

#include "stdio.h"
#include "stdlib.h"
#include "errno.h"

// Возвращает количество элементов, сумма которых = k
int findSumElements(int *a, size_t size_a, int *b, size_t size_b, int k) {
    if (a == NULL || b == NULL || size_a == 0 || size_b == 0)
        return 0;

    int counter = 0;
    size_t i = 0;
    int j = size_b - 1;

    while (i < size_a && j >= 0) {
        if (a[i] + b[j] == k) {
            i++;
            j--;
            counter++;
        } else if (a[i] + b[j] > k) {
            j--;
        } else {
            i++;
        }
    }
    return counter;
}


int main() {
    // Ввод массивов
    int size_a = 0;
    int size_b = 0;
    if (scanf("%d\n", &size_a) == 0)
        return 0;
    int *a = (int *)malloc(size_a * sizeof(int));
    if (errno == ENOMEM || a == NULL)
        return 0;
    for (size_t i = 0; i < size_a; i++) {
        if (scanf("%d", &a[i]) == 0)
            return 0;
    }

    if (scanf("%d\n", &size_b) == 0)
        return 0;
    int *b = (int *)malloc(size_b * sizeof(int));
    for (size_t i = 0; i < size_b; i++) {
        if (scanf("%d", &b[i]) == 0)
            return 0;
    }
    if (errno == ENOMEM || a == NULL) {
        free(a);
        return 0;
    }
    int k = 0;
    if (scanf("%d\n", &k) == 0)
        return 0;

    printf("%d\n", findSumElements(a, size_a, b, size_b, k));

    return 0;
}
