#include "stdio.h"
#include "stdlib.h"
#define STRLEN(s) ({int retval = 0; while (*(s + ++retval)); retval;})

int main() {
    char *a = (char *)malloc(20 * sizeof(char));
    scanf("%s", a);
    printf("%d\n", STRLEN(a));
    int s = 0;
    while (*(a + ++s));
    printf("%d\n", s);
    return 0;
}
