//
//  main.cpp
//  A5_1
//
//  Created by Konstantin on 11.03.16.
//  Copyright (c) 2016 Manyakhin. All rights reserved.
//

/*    TASK
********************************************************
        Дан фрагмент последовательности скобок, состоящей из символов (){}[].
    Требуется определить, возможно ли продолжить фрагмент в обе стороны,
    получив корректную последовательность.
    Длина исходной последовательности ≤ 200000.
        Формат входных данных. ​
    Строка, содержащая символы (){}[] и, возможно, перевод строки.
        Формат выходных данных. ​
    Если возможно, ­вывести минимальную корректную последовательность, иначе ­
    напечатать IMPOSSIBLE​
********************************************************
*/
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

#define STRLEN(s) ({int retval = 0; while (*(s + ++retval)); retval;})
#define MAX_SIZE 6

using namespace std;

int getCharArray(char** ppInputArray, size_t &size) {
    if (ppInputArray == NULL) return 1;

    char *pArray = NULL;
    char *pBuff = (char *)malloc(MAX_SIZE * sizeof(char));
    if (pBuff == NULL)
        return 1;

    while (fgets(pBuff, MAX_SIZE, stdin)) {
        size_t buffSize = STRLEN(pBuff);

        char *pTemp = (char *)realloc(pArray,
                (size + buffSize + 1) * sizeof(char));
        if (pTemp == NULL) {
            if (pArray != NULL)
                free(pArray);
            free(pBuff);
            return 1;
        }
        pArray = pTemp;
        pTemp = (char *)memcpy(pArray + size, pBuff, buffSize);
        size += buffSize;
        if (pTemp == NULL) {
            free(pArray);
            free(pBuff);
            return 1;
        }
        pArray[size] = '\0';
    }
    free(pBuff);

    *ppInputArray = pArray;
    return 0;
}

int main() {
    size_t size = 0;
    char **ppInputArray = (char **)malloc(sizeof(char *));

    if (getCharArray(ppInputArray, size) == 1) {
        free(ppInputArray);
        printf("error\n");
        return 1;
    }

    printf("%s", *ppInputArray);

    free(*ppInputArray);
    free(ppInputArray);

    return 0;
}
