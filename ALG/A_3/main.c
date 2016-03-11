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

int findMaxInRange(int left, int right, size_t size, int a[size]);

int findMaxWithPriority(size_t size, int a[size]) {
    if (size == 0) return -1;
    if (size == 1) return 0;
    if (size == 2) {
        if (a[0] > a[1])
            return 0;
        else
            return 1;
    }

    // Основной алгоритм применим к массивам длинной больше трёх
    // size >= 3
    int first = 0,
        second = 0,
        third = 1;
    size_t i = 2;
    while (a[second] < a[third] && third < size - 1) {

        first = second;
        second = third;
        third = i;

        if (i * 2 >= size && i - 1 != size) {
            i = size - 1;
        } else {
            i *= 2;
        }
    }

    if (second == third) first = second;

    return findMaxInRange(first, third, size, a);
}


int main() {
    // Ввод массивов
    int size = 0;
    if (scanf("%d", &size) == 0)
        return 0;
    int a[size];
    for (size_t i = 0; i < size; i++) {
        if (scanf("%d", &a[i]) == 0)
            return 0;
    }

    printf("%d\n", findMaxWithPriority(size, a));

    return 0;
}


int findMaxInRange(int left, int right, size_t size, int a[size]) {
    if (size == 0)
        return -1;
    if (left == right)
        return left;

    int middle = left + ((right - left) / 2),
        lm = left + (middle - left) / 2,
        rm = middle + (right - middle) / 2;
    //printf("\n%i %i %i %i %i\n", left, lm, middle, rm, right);
    while (right - left > 2) {
        if ((a[middle] > a[lm] && a[middle] > a[rm])) {
            left = lm;
            right = rm;
        } else if (middle == rm || middle == lm) {
            if (a[middle] <= a[rm]) {
                left = middle;
                middle = rm - 1;
            } else {
                middle = lm + 1;
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
    if (middle == left)
        middle++;
    else if (middle == right)
        middle--;

    if (a[middle] < a[left])
        return left;
    if (a[middle] < a[right])
        return right;
    return middle;
}
