#include <stdio.h>

// ===> stack dalis
#define SIZE 5

struct Stack{
  char stack[SIZE];
  int top;
};

static void reset(struct Stack st) {
    st.top = 0;
}

void init(struct Stack st) {
    st.top = 0;
}

int isEmpty(struct Stack st) {
    return 0 == st.top;
}

int isFull(struct Stack st) {
    return SIZE == st.top;
}

void push(struct Stack st, char c) {
    if (!isFull(st)) {
        st.stack[st.top++] = c;
    }
}

char pop(struct Stack st) {
    if (!isEmpty(st)) {
        return st.stack[--st.top];
    }
    return '\0';
}

// ===> user dalis
int main(void) {
    char c;

    struct Stack st1, st2;

    init(st1);

    while ( (!isFull(st1)) && ('\n' != (c = getchar())) ) push(st1,c);

    while (!isEmpty(st1)) putchar(pop(st1));

    putchar('\n');
    printf("Pabaiga\n");

    return 0;
}

/*
gcc 05_ny_usestack.c -o 05_ny_usestack
*/

/*
C:\Repos\Github\ViktorasGolubevas\desktop-tutorial\src\evolution\stackext>05_ny_usestack.exe
123

Pabaiga
*/

