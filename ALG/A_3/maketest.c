#include "stdio.h"
#include "stdlib.h"
#include <time.h>

int main() {
    freopen("inputTest", "w", stdout);
    srand(time(NULL));

    for (size_t i = 0; i < 100; i++) {
        int size = rand() % 20;
        if (size == 0) size = 10;
        int m = rand() % size;
        printf("%i \n%i ", m, size);
        for (int j = 0; j < m; j++)
            printf("%i ", j);
        int k = m;
        for (int j = m; j < size; j++)
            printf("%i ", k--);
        printf("\n");
    }

    return 0;
}
