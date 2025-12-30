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

/*
C:/mingw64/bin/../lib/gcc/x86_64-w64-mingw32/13.2.0/../../../../x86_64-w64-mingw32/bin/ld.exe: C:\Users\vikto\AppData\Local\Temp\ccYvBz4R.o:3_attack.c:(.rdata$.refptr.top[.refptr.top]+0x0): undefined reference to `top'
C:/mingw64/bin/../lib/gcc/x86_64-w64-mingw32/13.2.0/../../../../x86_64-w64-mingw32/bin/ld.exe: C:\Users\vikto\AppData\Local\Temp\ccYvBz4R.o:3_attack.c:(.rdata$.refptr.stack[.refptr.stack]+0x0): undefined reference to `stack'
collect2.exe: error: ld returned 1 exit status
*/