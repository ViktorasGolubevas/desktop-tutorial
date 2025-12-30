#include <stdio.h>
#include "2_stack.h"

extern char stack[];
extern int top;

int main(void) {
  int c;
 
  while ( '\n' != (c=getchar()) ) push(c);
  stack[top++] = '!';
  while ( '\n' != (c=pop()) )  putchar(c);

  return 0;
}
