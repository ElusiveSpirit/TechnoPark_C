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

#define STRLEN(s) ({size_t retval = 0; while (*(s + ++retval)); retval;})
#define MAX_SIZE 1024
#define RESERVED_SIZE 6
#define True 0
#define False 1
#define and 2
#define xor 3
#define or 4
#define not 5

typedef struct var {
    char* name;
    bool condition;
} Variable;

char *reserved[] = {"True", "False", "and", "xor", "or", "not"};

// Output: index if find
// Else will return -1
int findInArray(char *word, char **array, size_t size) {
    if (word == NULL || array == NULL)
        return -1;

    // Выбор номера слова для сравнения
    size_t word_length = STRLEN(word) - 1;
    // Вычитаем из длинны символ переноса строки
    if (word[word_length - 1] == '\n')
        word_length--;
    int current_word_length = 0;

    for (size_t i = 0; i < size; i++) {
        char *current_word = array[i];
        current_word_length = STRLEN(current_word);

        // Сначала проверяется первый символ,
        // затем длина двух строк
        if (word[i] == current_word[i] &&
                word_length == current_word_length) {

            bool isEqual = true;
            for (size_t j = 1; j < word_length; j++) {
                if (word[j] != current_word[j]) {
                    isEqual = false;
                    break;
                }
            }
            if (isEqual) {
                // Возвращается индекс найденного слова
                return i;
            }
        }
    }
    return -1;
}

int getBool(char** input, size_t size, bool result) {
    if (size == 0 || input == NULL) {
        printf("[error]");
        return 1;
    }

    // Массив для хранения "переменных"
    Variable *variables = NULL;
    // Два массива вместо структуры
    char **var_char = NULL;
    bool *var_bool = NULL;
    size_t var_size = 0;

    for (size_t i = 0; i < size; i++) {
        // Сначала идёт ввод переменных
        char *line = input[i];
        char *letter = line;
        // Проверка на ввод переменной
        do {
            // Если найден знак '=', то это строка с переменной
            // Сохранение её значения в массив variables
            if (*letter == '=') {

                char *temp = (char*)malloc(
                    (letter - line + 1) * sizeof(char));
                if (errno == ENOMEM || temp == NULL) {
                    printf("[error]");
                    return 1;
                }
                temp = memcpy(
                    temp,
                    line,
                    (size_t)(letter - line));
                temp[(size_t)(letter - line)] = '\0';

                // Проверка на зарезервированные слова
                if (findInArray(temp, reserved, RESERVED_SIZE) != -1) {
                    printf("[error]");
                    return 1;
                }
                // Проверка на вторичный.. ввод переменной
                int find_result = findInArray(temp, var_char, var_size);
                if (find_result == -1) {
                    var_char = (char **)realloc(var_char,
                        (++var_size) * sizeof(char *));
                    var_bool = (bool *)realloc(var_bool,
                        (var_size) * sizeof(bool));
                    if (errno == ENOMEM || var_bool == NULL || var_char == NULL) {
                        printf("[error]");
                        return 1;
                    }
                    var_char[var_size - 1] = temp;
                }

                switch (findInArray(++letter, reserved, RESERVED_SIZE)) {
                    case True:
                        if (find_result == -1)
                            var_bool[size - 1] = true;
                        else
                            var_bool[find_result] = true;
                        break;
                    case False:
                        if (find_result == -1)
                            var_bool[size - 1] = false;
                        else
                            var_bool[find_result] = false;
                        break;
                    default:
                        // Освободить память
                        printf("[error]");
                        return 1;
                }
            }
            // TODO добавить проверку на пробел или знак скобки
            // написать функцию реализующую алгоритм решения выражений
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
