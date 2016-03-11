//
//  main.c
//  c_A8
//
//  Created by Konstantin on 26.02.16.
//  Copyright (c) 2016 Manyakhin. All rights reserved.
//

/*    TASK
********************************************************
    Составить программу построчной обработки текста,
  в результате которой каждая группа повторяющихся пробелов
  заменяется на один пробел.
********************************************************
*/

#include "stdlib.h"
#include "stdbool.h"
#include "stdio.h"

#define MAX_SIZE 1024

// Output - int
// 	0 - ok
// 	1 - error
int trim(char **text, size_t length, char*** out_text) {
	if (text == NULL || out_text == NULL || length == 0)
		return 1;

	*out_text = (char **)malloc(length * sizeof(char *));
	if (*out_text == NULL)
		return 1;

	for (size_t i = 0; i < length; i++) {
		size_t currentLength = 0;
		char *pCurLine = *(text + i);
		bool isSpace = false;

		// Count the length of further array
		do  {
			if (*pCurLine == ' ') {
				if (!isSpace)
					isSpace = true;
			} else {
				currentLength++;
				if (isSpace) {
					currentLength++;
					isSpace = false;
				}
			}
		} while (*(pCurLine++) != '\0');
		currentLength++;
		*(*out_text + i) = (char*)malloc(sizeof(char)* currentLength);

		if (*(*out_text + i) == NULL) {
			for (size_t j = 0; j < i; j++)
				free(*(*out_text + j));
			free(*out_text);
			return 1;
		}

		// Copy the array
		pCurLine = *(text + i);
		isSpace = false;
		char *pOutLine = *(*out_text + i);
		do {
			if (*pCurLine == ' ') {
				if (!isSpace)
					isSpace = true;
			} else {
				if (isSpace) {
					*(pOutLine++) = ' ';
					isSpace = false;
				}
				*(pOutLine++) = *pCurLine;
			}
		} while (*(pCurLine++) != '\0');
	}
	return 0;
}

int main() {
	char** input_array = (char** )malloc(sizeof(char* ));
	if (input_array == NULL) {
		printf("[error]");
		return 0;
	}

	size_t size = 0;
	char* buff = (char* )malloc(MAX_SIZE * sizeof(char));
	if (buff == NULL) {
		printf("[error]");
		free(input_array);
		return 0;
	}
	while (fgets(buff, MAX_SIZE, stdin) != NULL) {
		char **pTemp = (char** )realloc(input_array, (++size) * sizeof(char* ));
		if (pTemp == NULL) {
			printf("[error]");
			free(buff);
			size_t i = 0;
			while (input_array[i] != NULL) {
				free(input_array[i++]);
			}
			free(input_array);
		}
		input_array = pTemp;
		input_array[size - 1] = buff;

		buff = (char* )malloc(MAX_SIZE * sizeof(char));

		if (buff == NULL) {
			printf("[error]");
			size_t i = 0;
			while (input_array[i] != NULL) {
				free(input_array[i++]);
			}
			free(input_array);
			return 0;
		}
	}
	free(buff);
	if (size == 0) {
		free(input_array);
		return 0;
	}

	char*** out_array = (char ***)malloc(sizeof(char **));
	if (out_array == NULL) {
		for (size_t i = 0; i < size; i++)
			free(input_array[i]);
		free(input_array);
		return 0;
	}
	// solution Function
	if (trim(input_array, size, out_array) == 1 || out_array == NULL) {
		printf("[error]");
		for (size_t i = 0; i < size; i++)
			free(input_array[i]);
		free(input_array);

		// Чтобы не дублировать код очищения
		if (out_array != NULL)
			free(out_array);
		return 0;
	}

	// Output
	for (size_t i = 0; i < size; i++)
		printf("%s", (*out_array)[i]);

	// freeAll
	for (size_t i = 0; i < size; i++) {
		free(input_array[i]);
		free((*out_array)[i]);
	}
	free(input_array);
	free(*out_array);
	free(out_array);

	return 0;
}
