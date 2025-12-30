#include <stdio.h>
#include "2x_stack.h"

// char stack[STACK_SIZE];
// int  top = 0;

void reset(void) {
  top = 0;
}
void push(char c) {
  if (top < STACK_SIZE) stack[top++] = c;
  else  printf("Stekas pilnas\n");
}
char pop(void) {
  if (top > 0) return stack[--top];
  printf("\nStekas tuscias");
  return '\n';
}

/* gcc 2x_driver.c 2x_stack.c -o main
C:/mingw64/bin/../lib/gcc/x86_64-w64-mingw32/13.2.0/../../../../x86_64-w64-mingw32/bin/ld.exe: C:\Users\vikto\AppData\Local\Temp\ccEohWn4.o:2x_driver.c:(.rdata$.refptr.stack[.refptr.stack]+0x0): undefined reference to `stack'
C:/mingw64/bin/../lib/gcc/x86_64-w64-mingw32/13.2.0/../../../../x86_64-w64-mingw32/bin/ld.exe: C:\Users\vikto\AppData\Local\Temp\ccEohWn4.o:2x_driver.c:(.rdata$.refptr.top[.refptr.top]+0x0): undefined reference to `top'
*/