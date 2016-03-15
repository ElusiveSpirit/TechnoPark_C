//
//  main.cpp
//  A5_1
//
//  Created by Konstantin on 11.03.16.
//  Copyright (c) 2016 Manyakhin. All rights reserved.
//

/*    TASK
********************************************************
        Дан фрагмент последовательности скобок, состоящей из символов (){}[].
    Требуется определить, возможно ли продолжить фрагмент в обе стороны,
    получив корректную последовательность.
    Длина исходной последовательности ≤ 200000.
        Формат входных данных. ​
    Строка, содержащая символы (){}[] и, возможно, перевод строки.
        Формат выходных данных. ​
    Если возможно, ­вывести минимальную корректную последовательность, иначе ­
    напечатать IMPOSSIBLE​
********************************************************
*/
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include <iostream>

#define STRLEN(s) ({int retval = 0; while (*(s + ++retval)); retval;})
#define MAX_SIZE 6


int getCharArray(char **, size_t&);
int addBrackets(char*);

class Stack {
public:
    Stack();
    Stack( char size );
    ~Stack() { free(buffer); };

    // Методы доступа
    void push( char );
    char pop();

    char *toCharArray();

    bool isEmpty() const { return top == -1; };

private:
    // Расширяет выделенную под массив память
    // 0 - OK
    // 1 - error
    int expandBuffer();

    // Приватные переменные
    char *buffer;
    char bufferSize;
    char top;

#define DEFAULT_DEQ_SIZE 8
};


int main() {

    size_t size = 0;
    char *pInputArray = NULL;

    if (getCharArray(&pInputArray, size) == 1) {
        printf("error\n");
        return 1;
    }

    if (addBrackets(pInputArray) == 1 || pInputArray == NULL) {
        printf("error\n");
        return 1;
    }

    printf("%s\n", pInputArray);

    free(pInputArray);
    return 0;
}

int addBrackets(char* pInputArray) {
    if (pInputArray == NULL)
        return 1;

    /*Stack input;
    Stack outStack;
    char *pChar = pInputArray;
    char prevChar = 0;
    while (*pChar) {
        switch (*pChar) {
            // Для открывающих скобок условий нет
            case '(':
                input.push(*pChar);
                outStack.push(*pChar);
                break;
            case '[':
                input.push(*pChar);
                outStack.push(*pChar);
                break;
            case '{':
                input.push(*pChar);
                outStack.push(*pChar);
                break;

            // Условия для закрывающих
            case ')':
                if (prevChar == '(') {
                    prevChar = input.pop();
                    outStack.push(*pChar);
                } else if (prevChar == '{' || prevChar == '[') {
                    printf("IMPOSSIBLE\n");
                    return 1;
                } else {
                    input.push(*pChar);
                    outStack.push(*pChar);
                }
                break;
            case ']':
                if (prevChar == '[') {
                    prevChar = input.pop();
                    outStack.push(*pChar);
                } else if (prevChar == '{' || prevChar == '(') {
                    printf("IMPOSSIBLE\n");
                    return 1;
                } else {
                    input.push(*pChar);
                    outStack.push(*pChar);
                }
                break;
            case '}':
                if (prevChar == '{') {
                    prevChar = input.pop();
                    outStack.push(*pChar);
                } else if (prevChar == '(' || prevChar == '[') {
                    printf("IMPOSSIBLE\n");
                    return 1;
                } else {
                    input.push(*pChar);
                    outStack.push(*pChar);
                }
                break;
        }

        prevChar = *pChar;
        pChar++;
    }*/

    Stack waitStackLeft, waitStackRight;
    char wait_for_char_r = 0;
    char  *pChar = pInputArray;
    char *pPrevChar = NULL, *pPrevCharPointer = NULL;
    while (*pChar != '\0') {
        char ch = *pChar;

        if (ch == '(' || ch == '{' || ch == '[') {
            waitStackRight.push(ch);
        } else if (ch == ')' || ch == '}' || ch == ']') {

            if (pPrevChar != NULL && (
                    (ch == ')' && *pPrevChar == '(') ||
                    (ch == '}' && *pPrevChar == '{') ||
                    (ch == ']' && *pPrevChar == '['))) {
                while (pPrevChar > pInputArray && (
                        *pPrevChar == '}' ||
                        *pPrevChar == ']' ||
                        *pPrevChar == ')'))
                    pPrevChar--;
                if (pPrevChar == pInputArray && (
                        *pPrevChar == '}' ||
                        *pPrevChar == ']' ||
                        *pPrevChar == ')')) {
                    pPrevChar == NULL;
                }
            } else {
                printf("IMPOSSIBLE\n");
                return 1;
            }

            wait_for_char_r = waitStackRight.pop();
            if (wait_for_char_r == 0 ||
                    ((ch == ')' && wait_for_char_r != '(') &&
                    (ch == '}' && wait_for_char_r != '{') &&
                    (ch == ']' && wait_for_char_r != '['))) {

                waitStackLeft.push(ch);
            }

        }
        pPrevChar = pChar;
        pChar++;
    }
    printf("OK\n" );
    // Добавление скобок сзади
    /*while (!waitStackRight.isEmpty()) {
        char ch = waitStackRight.pop();
        if (ch == '(') {
            outStack.push(')');
        } else if (ch == '{') {
            outStack.push('}');
        } else if (ch == '[') {
            outStack.push(']');
        }
    }
    // Реверсируем стек
    Stack stackTemp, leftStackTemp;
    while (!outStack.isEmpty()) stackTemp.push(outStack.pop());
    while (!waitStackLeft.isEmpty()) leftStackTemp.push(waitStackLeft.pop());
    // Добавление скобок спереди
    while (!leftStackTemp.isEmpty()) {
        char ch = leftStackTemp.pop();
        if (ch == ')') {
            stackTemp.push('(');
        } else if (ch == '}') {
            stackTemp.push('{');
        } else if (ch == ']') {
            stackTemp.push('[');
        }
    }

    free(pInputArray);
    pInputArray = stackTemp.toCharArray();*/
    return 0;
}


int getCharArray(char **pInputArray, size_t &size) {
    size = 0;
    char *pArray = NULL;
    char *pBuff = (char *)malloc(MAX_SIZE * sizeof(char));
    if (pBuff == NULL)
        return 1;

    while (fgets(pBuff, MAX_SIZE, stdin)) {
        size_t buffSize = STRLEN(pBuff);

        char *pTemp = (char *)realloc(pArray,
                (size + buffSize + 1) * sizeof(char));
        if (pTemp == NULL) {
            if (pArray != NULL)
                free(pArray);
            free(pBuff);
            return 1;
        }
        pArray = pTemp;
        pTemp = (char *)memcpy(pArray + size, pBuff, buffSize);
        size += buffSize;
        if (pTemp == NULL) {
            free(pArray);
            free(pBuff);
            return 1;
        }
        pArray[size] = '\0';
    }
    free(pBuff);

    *pInputArray = pArray;
    return 0;
}



void Stack::push( char ch ) {
    if ( top + 1 == bufferSize )
        if (expandBuffer() == 1)
            return;
    buffer[++top] = ch;
}

char Stack::pop() {
    if ( top == -1 )
        return 0;

    return buffer[top--];
}

int Stack::expandBuffer() {
    char *pTemp = (char *)realloc(buffer, bufferSize * 2 * sizeof(char));
    if (pTemp == NULL) {
        return 1;
    }
    buffer = pTemp;
    bufferSize *= 2;
    return 0;
}

char *Stack::toCharArray() {
    if (this->isEmpty())
        return NULL;


    char *result = (char *)malloc((top + 2) * sizeof(char));
    if (result == NULL) {
        printf("error in allocate memory function \'Stack::toCharArray()\'");
        return NULL;
    }

    int j = 0;
    for (int i = top; i >= 0; i--) {
        result[j++] = buffer[i];
    }

    result[top + 1] = '\0';
    return result;
}

Stack::Stack() :
    bufferSize( DEFAULT_DEQ_SIZE ),
    top( -1 )
{
    buffer = (char *)malloc(DEFAULT_DEQ_SIZE * sizeof(char));
}

Stack::Stack( char size ) :
    bufferSize( size ),
    top( -1 )
{
    buffer = (char *)malloc(size * sizeof(char));
}
