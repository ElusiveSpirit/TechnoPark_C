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
#include "stack.h"
#include <iostream>

#define STRLEN(s) ({int retval = 0; while (*(s + ++retval)); retval;})
#define MAX_SIZE 6


int addCharArray(char**, size_t&);
int addBrackets(char*);

int main() {

    size_t size = 0;
    char **ppInputArray = (char **)malloc(sizeof(char *));

    if (addCharArray(ppInputArray, size) == 1) {
        free(ppInputArray);
        printf("error\n");
        return 1;
    }

    addBrackets(*ppInputArray);
//    printf("%s", *ppInputArray);

    free(*ppInputArray);
    free(ppInputArray);

    return 0;
}

int addBrackets(char* pInputArray) {
    if (pInputArray == NULL)
        return 1;

    Stack input;
    Stack outStack;
    char *pChar = pInputArray;
    char prevChar = 0; //*(pChar++)
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
    }

    Stack stackTemp;
    Stack waitStack;
    char wait_for_char = 0;
    while (!outStack.isEmpty()) {
        char ch = outStack.pop();

        if (ch == ')' || ch == '}' || ch == ']') {
            /*if (wait_for_char != 0) {
                waitStack.push(ch);
                /*int top = 0;
                while (!outStack.isEmpty()) {
                    stackTemp.push(outStack.pop());
                    top++;
                }
                if (ch == ')') {
                    outStack.push('(');
                } else if (ch == '}') {
                    outStack.push('{');
                } else if (ch == ']') {
                    outStack.push('[');
                }
                top++;
                while (top > 0) {
                    outStack.push(stackTemp.pop());
                    top--;
                }*/
            //}
            //wait_for_char = ch;
            waitStack.push(ch);
            stackTemp.push(ch);
        } else if (ch == '(' || ch == '{' || ch == '[') {
            // Если ожидаемая скобка совпадает, то обнуляем и закидываем
            // всё во временный стек
            wait_for_char = waitStack.pop();
            if ((ch == '(' && wait_for_char == ')') ||
                    (ch == '{' && wait_for_char == '}') ||
                    (ch == '[' && wait_for_char == ']')) {
                stackTemp.push(ch);
            } else
            // Если открывающей скобки не ждали, значит, нужно добавить
            // закрывающую в конец -> перебрасываем в первый стек всё добро
            // из временного и добавляем скобку.
            // Затем возвращаемся обратно
            if (wait_for_char == 0) {
                int top = 0;
                outStack.push(ch);
                while (!stackTemp.isEmpty()) {
                    outStack.push(stackTemp.pop());
                    top++;
                }
                if (ch == '(') {
                    stackTemp.push(')');
                } else if (ch == '{') {
                    stackTemp.push('}');
                } else if (ch == '[') {
                    stackTemp.push(']');
                }
                top++;
                while (top > 0) {
                    stackTemp.push(outStack.pop());
                    top--;
                }
            }
            
        }
    }
    printf("OK\n");
    while (!waitStack.isEmpty()) {
        char ch = waitStack.pop();
        if (ch == ')') {
            stackTemp.push('(');
        } else if (ch == '}') {
            stackTemp.push('{');
        } else if (ch == ']') {
            stackTemp.push('[');
        }
    }
    while (!stackTemp.isEmpty())
        std::cout << stackTemp.pop();

    std::cout << std::endl;
    return 0;
}

int addCharArray(char** ppInputArray, size_t &size) {
    if (ppInputArray == NULL) return 1;

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

    *ppInputArray = pArray;
    return 0;
}
