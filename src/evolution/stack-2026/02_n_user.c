#include <stdio.h>
#include "02_n_stack.c"

int main(void) {
    char c;

    init();

    /* Patobuliname: Tik jei stekas neužpildytas, skaitome simbolius iki '\n' */
    while ( (!isFull()) && ('\n' != (c = getchar())) ) push(c);

    while (!isEmpty()) putchar(pop());

    putchar('\n');
    return 0;
}

/*
gcc 02_n_user.c -o 02_n_use_stack
*/