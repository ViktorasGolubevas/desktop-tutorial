#include <stdio.h>
#include "2_stack.h" // no attack

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

/*
[{
	"resource": "/c:/Repos/Github/ViktorasGolubevas/desktop-tutorial/src/evolution/stack/2_driver.c",
	"owner": "C/C++: IntelliSense",
	"code": "20",
	"severity": 8,
	"message": "identifier \"stack\" is undefined",
	"source": "C/C++",
	"startLineNumber": 8,
	"startColumn": 3,
	"endLineNumber": 8,
	"endColumn": 8,
	"origin": "extHost1"
},{
	"resource": "/c:/Repos/Github/ViktorasGolubevas/desktop-tutorial/src/evolution/stack/2_driver.c",
	"owner": "C/C++: IntelliSense",
	"code": "20",
	"severity": 8,
	"message": "identifier \"top\" is undefined",
	"source": "C/C++",
	"startLineNumber": 8,
	"startColumn": 9,
	"endLineNumber": 8,
	"endColumn": 12,
	"origin": "extHost1"
}]
*/
/* 
identifier "stack" is undefined
identifier "top" is undefined
*/