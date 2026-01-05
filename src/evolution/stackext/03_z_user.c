#include <stdio.h>
#include "03_stack.h"

extern char stack[];
extern int top;

int main(void) {
    char c;

    init();
    while ( (!isFull()) && ('\n' != (c = getchar())) ) push(c);

    stack[top++] = '!'; // attack non-hiiden data

    while (!isEmpty()) putchar(pop());
    putchar('\n');

    return 0;
}

/*
gcc 03_stack.c 03_z_user.c -o 03_z_use_stack
*/
/*
OK 
*/

/*
03_z_use_stack.exe
*/
/*
123
!321
*/