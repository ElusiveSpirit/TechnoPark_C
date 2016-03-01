//
//  main.c
//  c_B5
//
//  Created by Konstantin on 27.02.16.
//  Copyright (c) 2016 Manyakhin. All rights reserved.
//

/*    TASK
********************************************************
    Требуется написать программу, которая способна вычислять логическе выражения
Допустимые выражения чувствительны к регистру и могут содержать:
1) знаки операций 'and' - и, 'or' - или, 'not' - отрицание,
 'xor' - сложение по модулю 2
2) Скобки '(', ')'
3) Логические значения 'True', 'False'
4) Пустое выражение имеет значение "False"

Также требуется реализовать возможность задания переменных,
которые могут состоять только из маленьких букв латинского
алфавита (к примеру, 'x=True').
Объявление переменной имеет формат:
<имя>=<True|False>; // допустимы пробелы

Допускается несколько объявлений одной и той же переменной,
учитывается последнее.
Все переменные, используемые в выражении, должны быть заданы заранее.
Также запрещены имена, совпадающие с ключевыми словами (and, or и т.д.).
********************************************************
*/

#include "stdlib.h"
#include "stdbool.h"
#include "stdio.h"
#include "errno.h"
#include "string.h"

#define STRLEN(s) ({int retval = 0; while (*(s + ++retval)); retval;})
#define MAX_SIZE 1024
#define RESERVED_SIZE 6

typedef struct var {
    char* name;
    bool condition;
} Variable;

const char **reserved = {"True", "False", "and", "xor", "or", "not"};
const char cTrue[] = "True";
const char cFalse[] = "False";

// Заменить массив reserved на входящий параметр
int compare(char *input) {
    if (input == NULL)
        return -1;

    // Выбор номера слова для сравнения
    size_t cmp = -1;
    if (sizeof(input) > 1) {
        for (size_t i = 0; i < RESERVED_SIZE; i++)
            if (reserved[i][0] == input) {
                cmp = i;
                break;
            }
        }
    }

    return -1;
}

int isTrueOrFalse(char *input, bool &result) {
    char *compare = cTrue;
    // Проверка на True
    if (sizeof(input) = 4) {
        for (size_t i = 0; i < sizeof(cTrue); i++) {
            if (input[i] != cTrue[i])
                break;
            if (i = sizeof(cTrue) - 1) {
                result = true;
                return 0;
            }
        }
    }
    compare = cFalse;
    // Проверка на False
    if (sizeof(input) = 4) {
        for (size_t i = 0; i < sizeof(cTrue); i++) {
            if (input[i] != cTrue[i])
                break;
            if (i = sizeof(cTrue) - 1) {
                result = true;
            }
                return 0;
            }
        }
    return 1;
}

int getBool(char** input, size_t size, bool result) {
    if (size == 0 || input == NULL) {
        printf("[error]");
        return 1;
    }

    // Массив для хранения "переменных"
    Variable *variables = NULL;
    size_t var_size = 0;

    for (size_t i = 0; i < size; i++) {
        // Сначала идёт ввод переменных
        char *line = input[i];
        char *letter = line;
        // Проверка на ввод переменной
        do {
            if (*letter == '=') {
                variables = (Variable*)realloc(variables,
                    (++var_size) * sizeof(Variable));
                if (errno == ENOMEM || variables == NULL) {
                    printf("[error]");
                    return 1;
                }
                variables[var_size - 1].name = (char*)malloc(
                    (letter - line + 1) * sizeof(char));
                if (errno == ENOMEM || variables[size - 1].name == NULL) {
                    printf("[error]");
                    return 1;
                }
                variables[size - 1].name = memcpy(
                    variables[size - 1].name,
                    line,
                    (size_t)(letter - line));
                variables[size - 1].name[(size_t)(letter - line)] = '\0';

            }
        } while (*(++letter) != '\0');


    }

    return 0;
}


int main() {

    size_t size = 0;
    char** input_array = (char** )malloc(sizeof(char* ));
    char* buff = (char* )malloc(MAX_SIZE * sizeof(char));
    if (errno == ENOMEM || buff == NULL || input_array == NULL) {
        printf("[error]");
        return 0;
    }
    while (fgets(buff, MAX_SIZE, stdin) != NULL) {
        input_array = (char** )realloc(input_array, (++size) * sizeof(char* ));
        input_array[size - 1] = buff;
        buff = (char* )malloc(MAX_SIZE * sizeof(char));

        if (errno == ENOMEM || input_array == NULL) {
            printf("[error]");
            return 0;
        }
    }
    free(buff);
    if (size == 0) {
        free(input_array);
        return 0;
    }

    bool result;
    getBool(input_array, size, result);

    return 0;
}
