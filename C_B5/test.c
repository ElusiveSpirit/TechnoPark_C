#include "stdio.h"
#include "stdlib.h"
#define STRLEN(s) ({size_t retval = 0; while (*(s + ++retval)); retval;})

int main() {
    char *a = (char *)malloc(20 * sizeof(char));

    char *b = (char* )realloc(a, 30 * sizeof(char));
    if (b != NULL)
        printf("b = %i\n", STRLEN(b));
    if (a != NULL)
        printf("a = %i\n",  STRLEN(a));
    char *c = NULL;
    printf("c = %i\n", c);

    free(b);
}
