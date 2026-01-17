#include <stdio.h>
#include <stdlib.h>
#include "07_n_stack.h"

int main(void) {
    char c;

    struct Stack *pst1;

    pst1 = calloc(sizeof(struct Stack), 1);

    printf("Ivesk st1\n");
    init(pst1);
    while ( (!isFull(pst1)) && ('\n' != (c = getchar())) ) push(pst1,c);
    while (!isEmpty(pst1)) putchar(pop(pst1));
    putchar('\n');
    printf("st1 pabaiga\n");

    return 0;
}


/*
C:\Repos\Github\ViktorasGolubevas\desktop-tutorial\src\evolution\stackext>gcc 07_n_stack.c 07_ny_user.c -o 07_ny_use_stack
07_ny_user.c: In function 'main':
07_ny_user.c:10:26: error: invalid application of 'sizeof' to incomplete type 'struct Stack'
   10 |     pst1 = calloc(sizeof(struct Stack), 1);
      |                          ^~~~~~
*/

/*
C:\Repos\Github\ViktorasGolubevas\desktop-tutorial\src\evolution\stackext>clang 07_n_stack.c 07_ny_user.c -o 07_ny_use_stack
07_ny_user.c:10:19: error: invalid application of 'sizeof' to an incomplete type 'struct Stack'
   10 |     pst1 = calloc(sizeof(struct Stack), 1);
      |                   ^     ~~~~~~~~~~~~~~
./07_stack.h:3:8: note: forward declaration of 'struct Stack'
    3 | struct Stack;
      |        ^
1 error generated.
*/