#include <stdio.h>
#include "2x_stack.h" // no attack

int main(void) {
  int c;
 
  while ( '\n' != (c=getchar()) ) push(c);
  stack[top++] = '!';
  while ( '\n' != (c=pop()) )  putchar(c);

  return 0;
}

/*
2_driver.c: In function 'main':
2_driver.c:8:3: error: 'stack' undeclared (first use in this function)
    8 |   stack[top++] = '!';
      |   ^~~~~
2_driver.c:8:3: note: each undeclared identifier is reported only once for each function it appears in
2_driver.c:8:9: error: 'top' undeclared (first use in this function); did you mean 'pop'?
    8 |   stack[top++] = '!';
      |         ^~~
      |         pop

*/