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

		*(out_text + i) = (char*)malloc(sizeof(char));

		if (errno == ENOMEM || *(out_text + i) == NULL) {
			printf("[error]");
			return 1;
		}


		char *pCurLine = *(text + i);
		bool isSpace = false;

		size_t out_size = 0;
		char *pOutLine = *(out_text + i);
        char *pCopyFrom = NULL;
        do {
			// Increasing out_size in the end.

			if (*pCurLine == ' ' || *pCurLine == '\n') {
				if (!isSpace) { // If a first space -> copy array from the first char
					isSpace = true;
                    if (pCopyFrom == NULL) // If spaces in line are first
                        pCopyFrom = pCurLine;

                    size_t delta = pCurLine - pCopyFrom + 1;
					if (delta > 1)
                        pOutLine = (char* )realloc(pOutLine, (out_size + delta)  * sizeof(char));
					if (errno == ENOMEM || pOutLine == NULL) {
						printf("[error]");
						return 1;
					}

                    pOutLine = memcpy(pOutLine + out_size, pCopyFrom, delta);
                    pOutLine = pOutLine - out_size;
                    if (pOutLine == NULL) {
                    	printf("[error]");
                    	return 1;
                    }

                    out_size += delta;

                     if (pOutLine == NULL) {
                        printf("[error]");
                        return 1;
                    }
                    pCopyFrom = NULL;
                }
			} else {
		        if (pCopyFrom == NULL)
                    pCopyFrom = pCurLine;
                if (isSpace)
                    isSpace = false;

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
		input_array[size++] = buff;
        buff = (char* )malloc(MAX_SIZE * sizeof(char));

		input_array = (char** )realloc(input_array, (size + 1) * sizeof(char* ));
		if (errno == ENOMEM || input_array == NULL) {
			printf("[error]");
			return 0;
		}
	}
	free(buff);

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

