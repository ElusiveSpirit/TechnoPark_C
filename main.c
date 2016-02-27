#include "stdlib.h"
#include "stdbool.h"
#include "stdio.h"
#include "errno.h"
#include "string.h"

#define MAX_SIZE 1024

// Output - int
// 	0 - ok
// 	1 - error
int trim(char **text, size_t length, char** out_text)
{
	if (text == NULL || out_text == NULL || length == 0)
		return 1;

	for (size_t i = 0; i < length; i++)
	{
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
		*(out_text + i) = (char*)malloc(sizeof(char)* currentLength);

		if (errno == ENOMEM || *(out_text + i) == NULL) {
			printf("[error]");
			return 1;
		}

		// Copy the array
		pCurLine = *(text + i);
		isSpace = false;
		char *pOutLine = *(out_text + i);
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

int main()
{
	char** input_array = (char** )malloc(sizeof(char* ));
	if (errno == ENOMEM || input_array == NULL) {
		printf("[error]");
		return 0;
	}

	size_t size = 0;
	char* buff = (char* )malloc(MAX_SIZE * sizeof(char));
	if (errno == ENOMEM || buff == NULL) {
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

	char** out_array = (char**)malloc(size * sizeof(char*));
	if (errno == ENOMEM || out_array == NULL) {
				printf("[error]");
				return 0;
			}
	// solution Function
	if (trim(input_array, size, out_array) == 1)
		return 0;

	if (out_array == NULL) {
		printf("[error]");
		return 0;
	}

	// Output
	for (size_t i = 0; i < size; i++)
		printf("%s", out_array[i]);

	// freeAll
	for (size_t i = 0; i < size; i++) {
		free(input_array[i]);
		free(out_array[i]);
	}
	free(input_array);
	free(out_array);

	return 0;
}
