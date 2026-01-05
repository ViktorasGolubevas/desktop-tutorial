#include <stdio.h>

#include "03_ny_stack.h"

int main(void) {
    char c;

    init();
    while ( (!isFull()) && ('\n' != (c = getchar())) ) push(c);
    while (!isEmpty()) putchar(pop());

    putchar('\n');
    return 0;
}

/*
C:\Repos\Github\ViktorasGolubevas\desktop-tutorial\src\evolution\stackext>gcc 03_ny_stack.c 03_ny_user.c -o 03_ny_use_stack
C:/mingw64/bin/../lib/gcc/x86_64-w64-mingw32/13.2.0/../../../../x86_64-w64-mingw32/bin/ld.exe:
C:\Users\vikto\AppData\Local\Temp\ccYXdb7p.o:03_ny_stack.c:(.rdata$.refptr.stack[.refptr.stack]+0x0): undefined reference to `stack'
C:/mingw64/bin/../lib/gcc/x86_64-w64-mingw32/13.2.0/../../../../x86_64-w64-mingw32/bin/ld.exe: 
C:\Users\vikto\AppData\Local\Temp\ccYXdb7p.o:03_ny_stack.c:(.rdata$.refptr.top[.refptr.top]+0x0): undefined reference to `top'
collect2.exe: error: ld returned 1 exit status
*/

/*
C:\Repos\Github\ViktorasGolubevas\desktop-tutorial\src\evolution\stackext>clang 03_ny_stack.c 03_ny_user.c -o 03_ny_use_stack
C:/mingw64/bin/ld: C:/Users/vikto/AppData/Local/Temp/03_ny_stack-338f78.o:03_ny_stack.c:(.rdata$.refptr.stack[.refptr.stack]+0x0): undefined reference to `stack'
C:/mingw64/bin/ld: C:/Users/vikto/AppData/Local/Temp/03_ny_stack-338f78.o:03_ny_stack.c:(.rdata$.refptr.top[.refptr.top]+0x0): undefined reference to `top'
clang: error: linker command failed with exit code 1 (use -v to see invocation)
*/

/*
gcc 03_ny_stack.c 03_ny_user.c -c
*/
/*
ok
*/