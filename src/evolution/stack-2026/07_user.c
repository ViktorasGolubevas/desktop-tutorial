#include <stdio.h>
#include "07_stack.h"

int main(void) {
    char c;

    struct Stack *pst1;

    pst1 = create();

    printf("Ivesk st1\n");
    init(pst1);
    while ( (!isFull(pst1)) && ('\n' != (c = getchar())) ) push(pst1,c);
    while (!isEmpty(pst1)) putchar(pop(pst1));
    putchar('\n');
    printf("st1 pabaiga\n");

    return 0;
}


/*
gcc 07_stack.c 07_user.c -o 07_use_stack
*/

/*
C:\Repos\Github\ViktorasGolubevas\desktop-tutorial\src\evolution\stackext>07_use_stack.exe
Ivesk st1
123456
54321
st1 pabaiga
*/