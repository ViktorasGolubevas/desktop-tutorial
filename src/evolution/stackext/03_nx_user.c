#include <stdio.h>
#include "03_nx_stack.h"

int main(void) {
    char c;

    init();
    while ( (!isFull()) && ('\n' != (c = getchar())) ) push(c);
    while (!isEmpty()) putchar(pop());

    putchar('\n');
    return 0;
}

/*
gcc 03_nx_stack.c 03_nx_user.c -o 03_nx_use_stack
*/
/*
C:\Repos\Github\ViktorasGolubevas\desktop-tutorial\src\evolution\stackext>gcc 03_nx_stack.c 03_nx_user.c -o 03_nx_use_stack
C:/mingw64/bin/../lib/gcc/x86_64-w64-mingw32/13.2.0/../../../../x86_64-w64-mingw32/bin/ld.exe: C:\Users\vikto\AppData\Local\Temp\ccCCUdsd.o:03_nx_user.c:(.bss+0x0): multiple definition of `stack'; C:\Users\vikto\AppData\Local\Temp\ccQYpglU.o:03_nx_stack.c:(.bss+0x0): first defined here
C:/mingw64/bin/../lib/gcc/x86_64-w64-mingw32/13.2.0/../../../../x86_64-w64-mingw32/bin/ld.exe: C:\Users\vikto\AppData\Local\Temp\ccCCUdsd.o:03_nx_user.c:(.bss+0x64): multiple definition of `top'; C:\Users\vikto\AppData\Local\Temp\ccQYpglU.o:03_nx_stack.c:(.bss+0x64): first defined here
collect2.exe: error: ld returned 1 exit status
*/

/*
C:\Repos\Github\ViktorasGolubevas\desktop-tutorial\src\evolution\stackext>clang 03_nx_stack.c 03_nx_user.c -o 03_nx_use_stack
C:/mingw64/bin/ld: C:/Users/vikto/AppData/Local/Temp/03_nx_user-c51de3.o:03_nx_user.c:(.bss+0x0): 
multiple definition of `stack'; C:/Users/vikto/AppData/Local/Temp/03_nx_stack-8474b5.o:03_nx_stack.c:(.bss+0x10): first defined here
C:/mingw64/bin/ld: C:/Users/vikto/AppData/Local/Temp/03_nx_user-c51de3.o:03_nx_user.c:(.bss+0x64): 
multiple definition of `top'; C:/Users/vikto/AppData/Local/Temp/03_nx_stack-8474b5.o:03_nx_stack.c:(.bss+0x0): first defined here
clang: error: linker command failed with exit code 1 (use -v to see invocation)
*/

/*
gcc 03_nx_stack.c 03_nx_user.c -c
*/
/*
ok
*/

