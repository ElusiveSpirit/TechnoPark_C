//
//  main.c
//  A4_2
//
//  Created by Konstantin on 04.03.16.
//  Copyright (c) 2016 Manyakhin. All rights reserved.
//

/*    TASK
********************************************************
        В первой строке количество команд n. n ≤ 1000000.
    Каждая команда задаётся как 2 целых числа: a b.
        a = 1 ­ push front
        a = 2 ­ pop front
        a = 3 ­ push back
        a = 4 ­ pop back
        Для очереди используются команды 2 и 3. Для дека
    используются все четыре команды. Если дана команда pop*,
    то число b ­ ожидаемое значение.Если команда pop вызвана
    для пустой структуры данных, то ожидается “-­1”.

        Формат выходных данных.
    Требуется напечатать YES ­ если все ожидаемые значения совпали.
    Иначе, если хотя бы одно ожидание не оправдалось, то напечатать NO.

    Реализовать дек с динамическим зацикленным буфером.
********************************************************
*/

#include "stdio.h"
#include "stdlib.h"
#include "errno.h"

#define PUSH_FRONT 1
#define POP_FRONT 2
#define PUSH_BACK 3
#define POP_BACK 4

#define ACTION 0
#define EXPECTED 1


// Класс Deq реализует динамически раширяющийся дек
class Deq {
public:
    Deq();
    Deq( int size );
    ~Deq() { free(buffer); };

    // Методы доступа
    void pushBack( int );
    void pushFront( int );
    int popBack();
    int popFront();

    bool isEmpty() const { return head == tail; };

private:
    // Расширяет выделенную под массив память
    // 0 - OK
    // 1 - error
    int expandBuffer();

    // Приватные переменные
    int *buffer;
    int bufferSize;
    int head;
    int tail;

#define DEFAULT_DEQ_SIZE 20
};

int main() {
    int commands_number = 0;
    if (scanf("%d\n", &commands_number) != 1) return 0;

    int commands[commands_number][2];
    for (size_t i = 0; i < commands_number; i++) {
        if (scanf("%d %d\n",
                &commands[i][ACTION],
                &commands[i][EXPECTED]) != 2)
            return 0;
    }

    Deq deq;
    for (size_t i = 0; i < commands_number; i++) {
        switch (commands[i][ACTION]) {
            case PUSH_BACK:
                deq.pushBack(commands[i][EXPECTED]);
                break;
            case PUSH_FRONT:
                deq.pushFront(commands[i][EXPECTED]);
                break;
            case POP_BACK:
                if (deq.popBack() == commands[i][EXPECTED])
                    break;
                printf("NO\n");
                return 0;
            case POP_FRONT:
                if (deq.popFront() == commands[i][EXPECTED])
                    break;
                printf("NO\n");
                return 0;
        }
    }
    printf("YES\n");
    return 0;
}

Deq::Deq() :
    bufferSize( DEFAULT_DEQ_SIZE ),
    head( 0 ),
    tail( 0 )
{
    buffer = (int *)malloc(DEFAULT_DEQ_SIZE * sizeof(int));
}

Deq::Deq( int size ) :
    bufferSize( size ),
    head( 0 ),
    tail( 0 )
{
    buffer = (int *)malloc(size * sizeof(int));
}

void Deq::pushBack( int number ) {
    if (( tail + 1 ) % bufferSize != head) {
        if (Deq::expandBuffer() == 1)
            return;
    }
    buffer[tail] = number;
    tail = ( tail + 1 ) % bufferSize;
}

void Deq::pushFront( int number ) {
    if (--head == -1) head = bufferSize - 1;
    if (head == tail) {
        if (Deq::expandBuffer() == 1)
            return;
    }
    buffer[head] = number;
}

int Deq::popBack() {
    if (head == tail) return -1;
    int result = buffer[tail];

    if (--tail == -1) tail = bufferSize - 1;

    return result;
}

int Deq::popFront() {
    if (head == tail) return -1;
    int result = buffer[head];

    head = (head + 1) % bufferSize;

    return result;
}

int Deq::expandBuffer() {
    int *buffer_temp = (int *)realloc(buffer, bufferSize * 2 * sizeof(int));
    if (errno != ENOMEM && buffer_temp != NULL) {
        buffer = buffer_temp;
        bufferSize *= 2;
        return 0;
    } else {
        printf("error in allocation memory for deq\n");
        return 1;
    }
}
