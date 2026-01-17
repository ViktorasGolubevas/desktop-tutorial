#include <stdio.h>
#include "06_stack.h"

int main(void) {
    char c;

    struct Stack st1, st2;

    printf("Ivesk st1\n");
    init(&st1);
    while ( (!isFull(&st1)) && ('\n' != (c = getchar())) ) push(&st1,c);
    while (!isEmpty(&st1)) putchar(pop(&st1));
    putchar('\n');
    printf("st1 pabaiga\n");

    printf("Ivesk st2\n");
    init(&st2);
    while ( (!isFull(&st2)) && ('\n' != (c = getchar())) ) push(&st2,c);

    st2.stack[st2.top++] = '!';

    while (!isEmpty(&st2)) putchar(pop(&st2));
    putchar('\n');
    printf("st2 pabaiga\n");

    return 0;
}

/*
gcc 06_stack.c 06_z_user.c -o 06_z_use_stack
*/

/*
C:\Repos\Github\ViktorasGolubevas\desktop-tutorial\src\evolution\stackext>06_z_use_stack.exe
Ivesk st1
123
321
st1 pabaiga
Ivesk st2
123456
!54321
st2 pabaiga
*/