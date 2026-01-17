#include <stdio.h>
#include "07_stack.h"

int main(void) {
    char c;

    struct Stack *pst1;

    pst1 = create();

    printf("Ivesk st1\n");
    init(pst1);
    while ( (!isFull(pst1)) && ('\n' != (c = getchar())) ) push(pst1,c);

    pst1->stack[pst1->top++] = '!';

    while (!isEmpty(pst1)) putchar(pop(pst1));
    putchar('\n');
    printf("st1 pabaiga\n");

    return 0;
}


/*
C:\Repos\Github\ViktorasGolubevas\desktop-tutorial\src\evolution\stackext>gcc 07_stack.c 07_zx_user.c -o 07_zx_use_stack
07_zx_user.c: In function 'main':
07_zx_user.c:15:9: error: invalid use of undefined type 'struct Stack'
   15 |     pst1->stack[pst1->top++] = '!';
      |         ^~
07_zx_user.c:15:21: error: invalid use of undefined type 'struct Stack'
   15 |     pst1->stack[pst1->top++] = '!';
      |                     ^~
*/

/*
C:\Repos\Github\ViktorasGolubevas\desktop-tutorial\src\evolution\stackext>clang 07_stack.c 07_zx_user.c -o 07_zx_use_stack
07_zx_user.c:15:9: error: incomplete definition of type 'struct Stack'
   15 |     pst1->stack[pst1->top++] = '!';
      |     ~~~~^
./07_stack.h:3:8: note: forward declaration of 'struct Stack'
    3 | struct Stack;
      |        ^
07_zx_user.c:15:21: error: incomplete definition of type 'struct Stack'
   15 |     pst1->stack[pst1->top++] = '!';
      |                 ~~~~^
./07_stack.h:3:8: note: forward declaration of 'struct Stack'
    3 | struct Stack;
      |        ^
2 errors generated.
*/