/* 3_attack.c
   Teaching demo: attempts to access `stack` and `top` via extern declarations.
   Because `3_stack.c` declares these variables static (file-local), linking
   will fail with unresolved externals. Compile with:
     gcc 3_attack.c 3_stack.c -Wall -std=c11 -o attack.exe
*/

#include <stdio.h>
#include "3_stack.h"

extern char stack[STACK_SIZE];
extern int top;

int main(void) {
    /* Attempt to corrupt protected internals (this should fail to link).
       This is intentionally non-destructive. */
    stack[0] = 'X';
    top = 1;
    printf("Attempted to modify protected stack\n");
    return 0;
}
