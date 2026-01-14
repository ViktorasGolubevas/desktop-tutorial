#include <stdio.h>
#include "077_stack.h"

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

    destroy(pst1);

    return 0;
}


/*
gcc 077_stack.c 077_user.c -o 077_use_stack
*/

/*
C:\Repos\Github\ViktorasGolubevas\desktop-tutorial\src\evolution\stackext>077_use_stack.exe
Ivesk st1
1234567
54321
st1 pabaiga
*/