//
//  main.c
//  A6_1
//
//  Created by Konstantin on 04.03.16.
//  Copyright (c) 2016 Manyakhin. All rights reserved.
//

/*    TASK
********************************************************
        Дано N кубиков. Требуется определить каким количеством способов
    можно выстроить из этих кубиков пирамиду.

    Каждый вышележащий слой пирамиды должен быть не больше нижележащего.
    N ≤ 200
********************************************************
*/

#include "stdio.h"

int calculate(int n, int max_ground) {
    if (n == 0) return 0;
    if (n == 1) return 1;

    int result = 0;

    int i_start = n;
    if (n > max_ground)
        i_start = max_ground;

    for (int i = i_start; i > 0; --i) {
        int res_temp = calculate(n - i, i);
        if (res_temp > 0)
            --res_temp;
        result += 1 + res_temp;

    }

    return result;
}


int main() {
    int n = 0;
    if (scanf("%i", &n) != 1) {
        return 0;
    }

    printf("%i\n", calculate(n, n));

    return 0;
}
