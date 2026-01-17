#include <stdio.h>
// #include "03_stack.h"
#include "04_stack.h"

extern char stack[];
extern int top;
extern void reset(void);

int main(void) {
    char c;

    init();
    while ( (!isFull()) && ('\n' != (c = getchar())) ) push(c);

    stack[top++] = '!'; // attack non-hiiden data  // +

    while (!isEmpty()) putchar(pop());
    putchar('\n');

    reset();
    return 0;
}

/*
gcc 04_stack.c 04_zx_user.c -o 04_zx_use_stack
*/
/*
C:/mingw64/bin/../lib/gcc/x86_64-w64-mingw32/13.2.0/../../../../x86_64-w64-mingw32/bin/ld.exe: C:\Users\vikto\AppData\Local\Temp\cchySwkU.o:04_zx_user.c:(.text+0x7d): undefined reference to `reset'
C:/mingw64/bin/../lib/gcc/x86_64-w64-mingw32/13.2.0/../../../../x86_64-w64-mingw32/bin/ld.exe: C:\Users\vikto\AppData\Local\Temp\cchySwkU.o:04_zx_user.c:(.rdata$.refptr.stack[.refptr.stack]+0x0): undefined reference to `stack'
C:/mingw64/bin/../lib/gcc/x86_64-w64-mingw32/13.2.0/../../../../x86_64-w64-mingw32/bin/ld.exe: C:\Users\vikto\AppData\Local\Temp\cchySwkU.o:04_zx_user.c:(.rdata$.refptr.top[.refptr.top]+0x0): undefined reference to `top'
collect2.exe: error: ld returned 1 exit status 
*/
