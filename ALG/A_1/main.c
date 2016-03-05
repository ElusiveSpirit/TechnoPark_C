//
//  main.c
//  a_1_2
//
//  Created by Konstantin on 27.02.16.
//  Copyright (c) 2016 Manyakhin. All rights reserved.
//

/*    TASK
********************************************************
    Вывести разложение натурального числа n на простые множители.
  Простые множители должны быть упорядочены
  по возрастанию и разделены пробелами.

   2 <= n <= 10 ^ 6
********************************************************
*/

#include "stdlib.h"
#include "stdio.h"
#include "errno.h"

// Возвращает массив простых множителей
int getMultiplierArray(int number, int *resultArray) {
    size_t size = 0;
    if (resultArray == NULL)
        return 0;

    int prevNumber = 2;
    // Поиск простых множителей до 1
    while (number > 1) {
        // При нахождении первого множителя число number
        // делится на найденное число
        for (int i = prevNumber; i <= number; i++) {
            if (number % i == 0) {
                prevNumber = i;
                resultArray[size] = i;

                resultArray = (int* )realloc(resultArray, (++size + 1) * sizeof(int));
                if (errno == ENOMEM || resultArray == NULL)
                    return 0;

                number /= i;
                break;
            }
        }
    }
    return size;
}

int main() {
    int number = 0;
    int size = 0;
    int *array = (int* )malloc(sizeof(int));;

    if (scanf("%d", &number) != 1)
        return 0;

    size = getMultiplierArray(number, array);
    if (array == NULL) {
        free(array);
        return 0;
    }

    for (int i = 0; i < size; i++)
        printf("%d ", array[i]);

    free(array);
    return 0;
}
