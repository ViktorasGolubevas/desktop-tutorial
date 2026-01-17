#include <stdio.h>
#include "03_stack.h"

int main(void) {
    char c;

    init();
    while ( (!isFull()) && ('\n' != (c = getchar())) ) push(c);
    while (!isEmpty()) putchar(pop());

    putchar('\n');
    return 0;
}

/*
gcc 03_stack.c 03_user.c -o 03_use_stack
*/
/*
OK 
*/