---
title: "ADT Stekas Evoliucija: Nuo C iki Modernaus C++ - Studentų Konspektas - 1 dalis"
author: "Office Agent"
date: "2025-01-13"
keywords: "C++, ADT, Stack, Evolution, Programming, Data Structures, Encapsulation"
file: "Progresuojame nuo C iki Modern C++, Steko pavyzdys 1-7, Copilot"
---

# ADT Stekas Evoliucija: Nuo C iki Modernaus C++

## Turinys

1. [Įvadas ir Evoliucijos Apžvalga](#įvadas-ir-evoliucijos-apžvalga)
2. [1 Etapas: Monolitinė Programa](#1-etapas-monolitinė-programa)
3. [2 Etapas: Failų Dekompozicija](#2-etapas-failų-dekompozicija)
4. [3 Etapas: Modulių Sistema](#3-etapas-modulių-sistema)
5. [4 Etapas: Informacijos Slėpimas](#4-etapas-informacijos-slėpimas)
6. [5 Etapas: Vartotojo Apibrėžiamas Tipas](#5-etapas-vartotojo-apibrėžiamas-tipas)
7. [6 Etapas: Tipas Modulyje](#6-etapas-tipas-modulyje)
8. [7 Etapas: Pilna Inkapsuliacija](#7-etapas-pilna-inkapsuliacija)
9. [Tipinės Klaidos ir Jų Sprendimas](#tipinės-klaidos-ir-jų-sprendimas)
10. [Atakų Demonstracijos](#atakų-demonstracijos)
11. [Praktiniai Patarimai](#praktiniai-patarimai)
12. [Santrauka ir Išvados](#santrauka-ir-išvados)

## Įvadas ir Evoliucijos Apžvalga

### Kas yra ADT (Abstract Data Type)?

**Abstract Data Type** - tai duomenų tipas, apibrėžiamas per jo elgesį (operacijas), o ne per vidinę struktūrą. ADT slepia implementacijos detales ir atskleidžia tik sąsają (interface).

### Kodėl Svarbu Suprasti Evoliuciją?

- **Istorinis kontekstas** - kaip vystėsi programavimo paradigmos
- **Tipinės klaidos** - kokių klaidų išvengti
- **Dizaino principai** - kodėl tam tikri sprendimai yra geresni
- **Praktiniai įgūdžiai** - kaip teisingai struktūrizuoti kodą

### Evoliucijos Kelias

*apie dvi dalis*

## I dalis: Nuo naivaus C iki brandaus C

Šis konspektas atskleidžia pirmuosius C "epochos" **7 evoliucijos etapus**, kurie parodo, kaip paprastas stekas transformuojasi į pilnai inkapsuliuotą ADT:

01 etapas: Monolitinė Programa
02 etapas: Failų Dekompozicija
03 etapas: Modulių Sistema
04 etapas: Informacijos Slėpimas
05 etapas: Vartotojo Apibrėžiamas Tipas
06 etapas: Tipas Modulyje
07 etapas: Pilna Inkapsuliacija

---

### 1 Etapas: Monolitinė Programa

#### Charakteristikos
- **Viskas vienoje vietoje** - duomenys, funkcijos ir main() funkcija
- **Globalūs kintamieji** - `stack[]` ir `top`
- **Tiesioginis prieigos** - jokių abstrakcijų

#### Kodas: `01_n_usestack.c`

```c
#include <stdio.h>

#define SIZE 5

char stack[SIZE];  // Globalus masyvas
int top = 0;       // Globalus indeksas

void init(void) {
    top = 0;
}

int isEmpty(void) {
    return 0 == top;
}

int isFull(void) {
    return SIZE == top;
}

void push(char c) {
    if (!isFull()) {
        stack[top++] = c;
    }
}

char pop(void) {
    if (!isEmpty()) {
        return stack[--top];
    }
    return '\0';
}

int main(void) {
    char c;
    init();
    
    while ((c = getchar()) != '\n') {
        push(c);
    }
    
    while (!isEmpty()) {
        putchar(pop());
    }
    
    putchar('\n');
    return 0;
}
```

### Kompiliavimas ir Vykdymas
```bash
gcc 01_n_usestack.c -o 01_n_usestack
./01_n_usestack
# Input: 123456
# Output: 54321
```

### ✅ Privalumai
- **Paprastumas** - viskas aiškiai matoma
- **Greitas prototipavimas** - lengva pradėti
- **Jokių sudėtingų konceptų** - tinka mokymosi pradžiai

### ❌ Trūkumai
- **Nelankstumas** - tik vienas stekas
- **Globalūs kintamieji** - name pollution
- **Sunku testuoti** - viskas susimaišę
- **Neperkeliamas kodas** - sunku panaudoti kitur

### 🎯 Kada Naudoti
- Labai maži projektai
- Greitai prototipai
- Mokymosi tikslai

---

## 2 Etapas: Failų Dekompozicija

### Koncepcija: Fizinis Kodo Skaidymas

Pirmasis bandymas atskirti **stekas** nuo **naudotojo kodo**. Čia susiduriame su **declarations vs definitions** koncepcija.

### 2.1 Teisingas Variantas: `02_n_stack.c` + `02_n_user.c`

#### Stekas: `02_n_stack.c`
```c
#define SIZE 5

char stack[SIZE];
int top = 0;

void init(void) {
    top = 0;
}

int isEmpty(void) {
    return 0 == top;
}

// ... kitos funkcijos
```

#### Naudotojas: `02_n_user.c`
```c
#include <stdio.h>
#include "02_n_stack.c"  // ⚠️ Įtraukiame .c failą!

int main(void) {
    char c;
    init();
    
    while ((!isFull()) && ('\n' != (c = getchar()))) 
        push(c);
    
    while (!isEmpty()) 
        putchar(pop());
    
    putchar('\n');
    return 0;
}
```

#### Kompiliavimas
```bash
gcc 02_n_user.c -o 02_n_use_stack  # Veikia!
```

### 2.2 Klaidingas Variantas: `02_nx_user.c`

```c
#include <stdio.h>
// Nėra jokių deklaracijų!

int main(void) {
    char c;
    
    init();        // ❌ Implicit declaration
    // ... kitos funkcijos
}
```

#### Kompiliavimo Klaidos
```bash
gcc 02_n_stack.c 02_nx_user.c -o 02_nx_use_stack

# GCC Warning:
02_nx_user.c:6:5: warning: implicit declaration of function 'init'

# Clang Error:
02_nx_user.c:6:5: error: call to undeclared function 'init'
```

### 🔍 Pagrindinė Pamoka

> **Implicit Function Declarations** - kai kompiliatorius nemato funkcijos deklaracijos, jis "spėja" jos prototipą. Tai pavojinga ir gali sukelti runtime klaidas!

### ✅ Privalumai
- Fizinis kodo atskyrimas
- Galima kompiliuoti atskirai

### ❌ Trūkumai
- Vis dar globalūs kintamieji
- Neaiški sąsaja (interface)
- Include .c failų yra blogas sprendimas

---

## 3 Etapas: Modulių Sistema

### Koncepcija: Header Failai ir Moduliai

Čia įvedame **header failus** (.h) ir mokamės **declarations vs definitions** skirtumo.

### 3.1 Klaidingas Variantas: `03_nx_stack.h` + `03_nx_stack.c`

#### Header: `03_nx_stack.h`
```c
#define SIZE 100

char stack[SIZE];  // ❌ Definition header faile!
int top;           // ❌ Definition header faile!

void init(void);   // ✅ Declaration
int isEmpty(void); // ✅ Declaration
// ...
```

#### Kompiliavimo Klaida
```bash
gcc 03_nx_stack.c 03_nx_user.c -o 03_nx_use_stack

# Multiple definition error:
multiple definition of `stack'
multiple definition of `top'
```

### 🔍 Pagrindinė Pamoka

> **Multiple Definition Error** - kai tas pats simbolis apibrėžiamas keliose vietose. Header failai yra įtraukiami į kiekvieną .c failą, todėl definitions dubliuojasi!

### 3.2 Kitas Klaidingas Variantas: `03_ny_stack.h`

#### Header: `03_ny_stack.h`
```c
#define SIZE 100

extern char stack[SIZE];  // ✅ Declaration
extern int top;           // ✅ Declaration

extern void init(void);   // ✅ Declaration
// ...
```

#### Implementation: `03_ny_stack.c`
```c
#include "03_ny_stack.h"

// ❌ Nėra definitions!

void init(void) {
    top = 0;  // Naudojame neapibrėžtą 'top'
}
```

#### Kompiliavimo Klaida
```bash
gcc 03_ny_stack.c 03_ny_user.c -o 03_ny_use_stack

# Undefined reference error:
undefined reference to `stack'
undefined reference to `top'
```

### 🔍 Pagrindinė Pamoka

> **Undefined Reference Error** - `extern` sako "šis simbolis egzistuoja kažkur kitur", bet jei jo niekur neapibrėžiame, linker negali jo rasti!

### 3.3 Teisingas Variantas: `03_stack.h` + `03_stack.c`

#### Header: `03_stack.h`
```c
// Tik declarations!
void init(void);
int isEmpty(void);
int isFull(void);
void push(char c);
char pop(void);
```

#### Implementation: `03_stack.c`
```c
#include "03_stack.h"

#define SIZE 5

char stack[SIZE];  // ✅ Definition implementation faile
int top;           // ✅ Definition implementation faile

void init(void) {
    top = 0;
}

// ... kitos funkcijos
```

#### Naudotojas: `03_user.c`
```c
#include <stdio.h>
#include "03_stack.h"  // ✅ Tik header

int main(void) {
    char c;
    init();
    // ...
}
```

#### Kompiliavimas
```bash
gcc 03_stack.c 03_user.c -o 03_use_stack  # ✅ Veikia!
```

### ✅ Privalumai
- Aiški sąsaja (header failas)
- Teisingas modulių skaidymas
- Galima kompiliuoti atskirai

### ❌ Trūkumai
- Vis dar globalūs kintamieji
- Galimos "atakos" (žr. `03_z_user.c`)

---

## 4 Etapas: Informacijos Slėpimas

### Koncepcija: `static` Raktažodis

Naudojame `static` raktažodį, kad **paslėptume** implementacijos detales nuo išorinio pasaulio.

### Kodas: `04_stack.c`

```c
#include "04_stack.h"

#define SIZE 5

static char stack[SIZE];    // ✅ Internal linkage
static int top;             // ✅ Internal linkage

static void reset(void) {   // ✅ Private funkcija
    top = 0;
}

void init(void) {           // ✅ Public funkcija
    top = 0;
}

// ... kitos public funkcijos
```

### Header: `04_stack.h`
```c
// Tik public interface
void init(void);
int isEmpty(void);
int isFull(void);
void push(char c);
char pop(void);
// Nėra reset() - ji private!
```

### 🔍 Pagrindinė Pamoka

> **Static Storage Class** - `static` globalūs kintamieji ir funkcijos yra matomi tik tame faile, kur apibrėžti. Tai C kalbos **information hiding** mechanizmas.

### Atakos Bandymas: `04_zx_user.c`

```c
#include "04_stack.h"

extern char stack[];     // ❌ Bandome pasiekti
extern int top;          // ❌ Bandome pasiekti
extern void reset(void); // ❌ Bandome pasiekti

int main(void) {
    // ...
    stack[top++] = '!';  // ❌ Ataka nepavyko!
    reset();             // ❌ Ataka nepavyko!
    return 0;
}
```

#### Kompiliavimo Klaida
```bash
gcc 04_stack.c 04_zx_user.c -o 04_zx_use_stack

# Undefined reference errors:
undefined reference to `stack'
undefined reference to `top'
undefined reference to `reset'
```

### ✅ Privalumai
- **Information hiding** - implementacija paslėpta
- **Saugumas** - negalima tiesiogiai keisti duomenų
- **Moduliarumas** - aiški public/private riba

### ❌ Trūkumai
- **Tik vienas stekas** - static kintamieji yra globalūs modulio viduje
- **Negalima kurti kelių egzempliorių**

---

## 5 Etapas: Vartotojo Apibrėžiamas Tipas

### Koncepcija: `struct` ir Kelių Egzempliorių Galimybė

Įvedame `struct Stack` tipą, kuris leidžia kurti **kelis stekas**.

### 5.1 Klaidingas Variantas: `05_nx_usestack.c`

```c
struct Stack {
    static char stack[SIZE];  // ❌ Negalima!
    static int top;           // ❌ Negalima!
};
```

#### Kompiliavimo Klaida
```bash
gcc 05_nx_usestack.c -o 05_nx_usestack

# GCC:
error: expected specifier-qualifier-list before 'static'

# Clang:
error: type name does not allow storage class to be specified
```

### 🔍 Pagrindinė Pamoka

> **Storage Class in Structs** - C kalba draudžia `static`, `extern`, `auto`, `register` specifikatorius struktūros nariams!

### 5.2 Kitas Klaidingas Variantas: `05_ny_usestack.c`

```c
struct Stack {
    char stack[SIZE];
    int top;
};

// ❌ Funkcijos parametrai "by value"
void init(struct Stack st) {
    st.top = 0;  // Keičia tik kopiją!
}

void push(struct Stack st, char c) {
    if (!isFull(st)) {
        st.stack[st.top++] = c;  // Keičia tik kopiją!
    }
}
```

#### Vykdymo Rezultatas
```bash
./05_ny_usestack
123
# Output: (tuščia) - duomenys nepasikeitė!
```

### 🔍 Pagrindinė Pamoka

> **Pass by Value vs Pass by Reference** - C kalboje struktūros perduodamos **by value** (kopijuojamos). Norint keisti originalą, reikia naudoti **pointers**!

### 5.3 Teisingas Variantas: `05_n_usestack.c`

```c
struct Stack {
    char stack[SIZE];
    int top;
};

// ✅ Naudojame pointers
void init(struct Stack *pst) {
    pst->top = 0;
}

void push(struct Stack *pst, char c) {
    if (!isFull(pst)) {
        pst->stack[pst->top++] = c;
    }
}

int main(void) {
    struct Stack st1, st2;  // ✅ Du atskiri stekai!
    
    printf("Ivesk st1\n");
    init(&st1);
    // ... naudojame st1
    
    printf("Ivesk st2\n");
    init(&st2);
    // ... naudojame st2
}
```

### ✅ Privalumai
- **Keli egzemplioriai** - galima kurti daug stekų
- **Type safety** - aiškus duomenų tipas
- **Lokalūs duomenys** - kiekvienas stekas turi savo duomenis

### ❌ Trūkumai
- **Atskleidžiama struktūra** - galimos atakos
- **Reikia modulio** - geriau atskirti į failus

---

## 6 Etapas: Tipas Modulyje

### Koncepcija: Struktūros Tipas Atskirame Module

Perkeliame `struct Stack` į atskirą modulį, bet **struktūros nariai vis dar matomi**.

### Header: `06_stack.h`
```c
#define SIZE 5

struct Stack {          // ✅ Public struktūra
    char stack[SIZE];   // ❌ Matomi nariai
    int top;            // ❌ Matomi nariai
};

void init(struct Stack *);
int isEmpty(struct Stack *);
// ...
```

### Implementation: `06_stack.c`
```c
#include "06_stack.h"

static void reset(struct Stack *pst) {  // ✅ Private funkcija
    pst->top = 0;
}

void init(struct Stack *pst) {
    pst->top = 0;
}

// ... kitos funkcijos
```

### Naudotojas: `06_user.c`
```c
#include <stdio.h>
#include "06_stack.h"

int main(void) {
    struct Stack st1, st2;
    
    // Naudojame per interface
    init(&st1);
    push(&st1, 'A');
    
    // Bet galime ir tiesiogiai!
    st1.stack[st1.top++] = 'B';  // ✅ Veikia, bet blogai!
}
```

### Atakos Demonstracija: `06_z_user.c`

```c
#include "06_stack.h"

int main(void) {
    struct Stack st2;
    
    init(&st2);
    push(&st2, '1');
    push(&st2, '2');
    push(&st2, '3');
    
    st2.stack[st2.top++] = '!';  // ✅ Ataka pavyko!
    
    while (!isEmpty(&st2)) 
        putchar(pop(&st2));
    // Output: !321
}
```

### ✅ Privalumai
- Modulinis dizainas
- Keli egzemplioriai
- Aiški sąsaja

### ❌ Trūkumai
- **Struktūros nariai matomi** - galimos atakos
- **Nėra tikros inkapsuliacija**

---

## 7 Etapas: Pilna Inkapsuliacija

### Koncepcija: Forward Declaration ir Opaque Pointers

Naudojame **forward declaration** ir **opaque pointers**, kad **visiškai paslėptume** struktūros implementaciją.

### 7.1 Klaidingi Variantai

#### Bandymas 1: `07_nx_user.c`
```c
#include "07_n_stack.h"

int main(void) {
    struct Stack st1, st2;  // ❌ Incomplete type!
    // ...
}
```

#### Kompiliavimo Klaida
```bash
# GCC:
error: storage size of 'st1' isn't known

# Clang:
error: variable has incomplete type 'struct Stack'
```

#### Bandymas 2: `07_ny_user.c`
```c
#include <stdlib.h>
#include "07_n_stack.h"

int main(void) {
    struct Stack *pst1;
    
    pst1 = calloc(sizeof(struct Stack), 1);  // ❌ Incomplete type!
    // ...
}
```

#### Kompiliavimo Klaida
```bash
error: invalid application of 'sizeof' to incomplete type 'struct Stack'
```

### 🔍 Pagrindinė Pamoka

> **Incomplete Types** - kai turime tik forward declaration (`struct Stack;`), negalime:
> - Kurti kintamųjų to tipo
> - Naudoti `sizeof`
> - Pasiekti narių
> 
> Bet galime kurti **pointers** į tą tipą!

### 7.2 Teisingas Variantas: `07_stack.h` + `07_stack.c`

#### Header: `07_stack.h`
```c
#define SIZE 5

struct Stack;  // ✅ Forward declaration (opaque type)

struct Stack* create(void);     // ✅ Factory funkcija
void init(struct Stack *);
int isEmpty(struct Stack *);
int isFull(struct Stack *);
void push(struct Stack *, char);
char pop(struct Stack *);
```

#### Implementation: `07_stack.c`
```c
#include <stdlib.h>
#include "07_stack.h"

struct Stack {              // ✅ Tikroji definicija (paslėpta)
    char stack[SIZE];
    int top;
};

struct Stack* create(void) {
    return (struct Stack*) calloc(sizeof(struct Stack), 1);
}

static void reset(struct Stack *pst) {  // ✅ Private
    pst->top = 0;
}

void init(struct Stack *pst) {
    pst->top = 0;
}

// ... kitos funkcijos
```

#### Naudotojas: `07_user.c`
```c
#include <stdio.h>
#include "07_stack.h"

int main(void) {
    struct Stack *pst1;
    
    pst1 = create();  // ✅ Naudojame factory
    
    init(pst1);
    push(pst1, '1');
    push(pst1, '2');
    push(pst1, '3');
    
    while (!isEmpty(pst1)) 
        putchar(pop(pst1));
    
    return 0;
}
```

### Atakos Bandymas: `07_zx_user.c`

```c
#include "07_stack.h"

int main(void) {
    struct Stack *pst1 = create();
    
    init(pst1);
    push(pst1, '1');
    
    pst1->stack[pst1->top++] = '!';  // ❌ Ataka nepavyko!
    
    return 0;
}
```

#### Kompiliavimo Klaida
```bash
# GCC:
error: invalid use of undefined type 'struct Stack'

# Clang:
error: incomplete definition of type 'struct Stack'
```

### 7.3 Pilnas Variantas su `destroy()`: `077_stack.h`

```c
#define SIZE 5

struct Stack;

struct Stack* create(void);
void destroy(struct Stack *);    // ✅ Memory management
void init(struct Stack *);
int isEmpty(struct Stack *);
int isFull(struct Stack *);
void push(struct Stack *, char);
char pop(struct Stack *);
```

### ✅ Privalumai
- **Pilna inkapsuliacija** - struktūra visiškai paslėpta
- **Saugumas** - neįmanomos atakos
- **Lankstumas** - galima keisti implementaciją
- **Memory management** - kontroliuojamas objektų gyvavimo ciklas

### ❌ Trūkumai
- **Sudėtingumas** - reikia factory funkcijų
- **Heap allocation** - dinaminis atminties valdymas
- **Performance overhead** - pointer indirection

---

## Tipinės Klaidos ir Jų Sprendimas

### 1. Implicit Function Declarations

#### ❌ Problema
```c
// Nėra #include arba deklaracijos
int main(void) {
    init();  // Compiler "spėja" prototipą
}
```

#### ✅ Sprendimas
```c
#include "stack.h"  // Arba
void init(void);    // Explicit declaration

int main(void) {
    init();  // Dabar OK
}
```

### 2. Multiple Definition Errors

#### ❌ Problema
```c
// header.h
int global_var = 42;  // Definition header faile!

// file1.c
#include "header.h"   // Įtraukia definition

// file2.c  
#include "header.h"   // Dar kartą įtraukia definition
```

#### ✅ Sprendimas
```c
// header.h
extern int global_var;  // Declaration

// implementation.c
int global_var = 42;    // Definition tik vienoje vietoje
```

### 3. Undefined Reference Errors

#### ❌ Problema
```c
// header.h
extern int global_var;  // Declaration

// Bet niekur nėra definition!
```

#### ✅ Sprendimas
```c
// header.h
extern int global_var;  // Declaration

// implementation.c
int global_var = 42;    // Definition
```

### 4. Pass by Value Klaidos

#### ❌ Problema
```c
void modify(struct Data data) {
    data.value = 100;  // Keičia tik kopiją!
}

int main(void) {
    struct Data d = {0};
    modify(d);
    printf("%d\n", d.value);  // Vis dar 0!
}
```

#### ✅ Sprendimas
```c
void modify(struct Data *data) {
    data->value = 100;  // Keičia originalą
}

int main(void) {
    struct Data d = {0};
    modify(&d);
    printf("%d\n", d.value);  // Dabar 100!
}
```

### 5. Incomplete Type Errors

#### ❌ Problema
```c
// header.h
struct Stack;  // Forward declaration

// user.c
struct Stack st;  // Negalima - incomplete type!
```

#### ✅ Sprendimas
```c
// header.h
struct Stack;
struct Stack* create(void);  // Factory funkcija

// user.c
struct Stack *pst = create();  // Pointer OK!
```

---

## Atakų Demonstracijos

### 1. Globalių Kintamųjų Ataka (3 etapas)

#### Atakos kodas: `03_z_user.c`
```c
#include "03_stack.h"

extern char stack[];  // Pasiekiame globalų kintamąjį
extern int top;

int main(void) {
    init();
    push('1'); push('2'); push('3');
    
    stack[top++] = '!';  // ✅ Ataka pavyko!
    
    while (!isEmpty()) putchar(pop());
    // Output: !321 (vietoj 321)
}
```

### 2. Struktūros Narių Ataka (6 etapas)

#### Atakos kodas: `06_z_user.c`
```c
#include "06_stack.h"

int main(void) {
    struct Stack st;
    
    init(&st);
    push(&st, '1'); push(&st, '2'); push(&st, '3');
    
    st.stack[st.top++] = '!';  // ✅ Ataka pavyko!
    
    while (!isEmpty(&st)) putchar(pop(&st));
    // Output: !321
}
```

### 3. Nepavykusi Ataka (7 etapas)

#### Atakos bandymas: `07_zx_user.c`
```c
#include "07_stack.h"

int main(void) {
    struct Stack *pst = create();
    
    init(pst);
    push(pst, '1');
    
    pst->stack[pst->top++] = '!';  // ❌ Ataka nepavyko!
    
    return 0;
}
```

#### Kompiliavimo klaida
```
error: incomplete definition of type 'struct Stack'
```

### 🔍 Pamoka

> **Inkapsuliacija veikia!** - 7 etape struktūros implementacija yra visiškai paslėpta, todėl jokie "hack'ai" neveiks.

---

## Praktiniai Patarimai

### 1. Kompiliavimo Strategijos

#### Atskirai Kompiliavimas
```bash
# Kompiliuojame į object failus
gcc -c stack.c -o stack.o
gcc -c user.c -o user.o

# Linkuojame
gcc stack.o user.o -o program
```

#### Makefile Pavyzdys
```makefile
CC = gcc
CFLAGS = -Wall -Wextra -std=c99

program: stack.o user.o
	$(CC) stack.o user.o -o program

stack.o: stack.c stack.h
	$(CC) $(CFLAGS) -c stack.c

user.o: user.c stack.h
	$(CC) $(CFLAGS) -c user.c

clean:
	rm -f *.o program
```

### 2. Header Guard'ai

```c
#ifndef STACK_H
#define STACK_H

// Header turinys

#endif /* STACK_H */
```

### 3. Const Correctness

```c
// Funkcijos, kurios nekeičia duomenų
int isEmpty(const struct Stack *pst);
int isFull(const struct Stack *pst);
char peek(const struct Stack *pst);  // Žiūri be pop
```

### 4. Error Handling

```c
typedef enum {
    STACK_OK,
    STACK_EMPTY,
    STACK_FULL,
    STACK_NULL_POINTER
} StackResult;

StackResult push(struct Stack *pst, char c) {
    if (!pst) return STACK_NULL_POINTER;
    if (isFull(pst)) return STACK_FULL;
    
    pst->stack[pst->top++] = c;
    return STACK_OK;
}
```

### 5. Memory Management

```c
// Visada poruokite create/destroy
struct Stack *pst = create();
if (pst) {
    // Naudojame...
    destroy(pst);  // Nepamirškite!
    pst = NULL;    // Apsauga nuo dangling pointer
}
```

---

## Santrauka ir Išvados

### Evoliucijos Etapų Santrauka

| Etapas | Sprendimas | Privalumai | Trūkumai | Saugumas |
|--------|------------|------------|----------|----------|
| **1** | Monolitinė programa | Paprastumas | Nelankstumas | ❌ Jokio |
| **2** | Failų dekompozicija | Fizinis skaidymas | Globalūs kintamieji | ❌ Jokio |
| **3** | Modulių sistema | Aiški sąsaja | Globalūs kintamieji | ❌ Atakos galimos |
| **4** | Information hiding | Paslėpta implementacija | Tik vienas egzempliorius | ⚠️ Dalinis |
| **5** | Vartotojo tipas | Keli egzemplioriai | Atskleidžiama struktūra | ❌ Atakos galimos |
| **6** | Tipas modulyje | Modulinis dizainas | Matomi nariai | ❌ Atakos galimos |
| **7** | Pilna inkapsuliacija | Visiškas saugumas | Sudėtingumas | ✅ Pilnas |

### Pagrindiniai Principai

#### 1. **Separation of Concerns**
- Atskirti **interface** nuo **implementation**
- Atskirti **public** nuo **private**
- Atskirti **data** nuo **behavior**

#### 2. **Information Hiding**
- Slėpti implementacijos detales
- Atskleidžiami tik būtini elementai
- Naudoti `static` ir opaque pointers

#### 3. **Type Safety**
- Naudoti struktūras vietoj primityvių tipų
- Aiškūs funkcijų prototipai
- Const correctness

#### 4. **Memory Management**
- Aiškus objektų gyvavimo ciklas
- Factory funkcijos kūrimui
- Destructor funkcijos sunaikinimui

### Kada Naudoti Kurį Etapą?

#### **Etapai 1-2: Mokymasis ir Prototipai**
- Greitai eksperimentai
- Labai maži projektai
- Algoritmo testavimas

#### **Etapai 3-4: Maži Projektai**
- Vienas programuotojas
- Paprastos duomenų struktūros
- Nereikia kelių egzempliorių

#### **Etapai 5-6: Vidutiniai Projektai**
- Reikia kelių egzempliorių
- Komandinis darbas
- Modulinis dizainas

#### **7 Etapas: Dideli Projektai**
- Bibliotekų kūrimas
- Maksimalus saugumas
- API dizainas
- Ilgalaikis palaikymas

### Kelias į C++

Šie C kalbos principai tiesiogiai veda į C++ koncepcijas:

```c
// C (7 etapas)
struct Stack* create(void);
void destroy(struct Stack*);
void push(struct Stack*, char);

// C++ (klasės)
class Stack {
public:
    Stack();           // Constructor
    ~Stack();          // Destructor
    void push(char);   // Method
private:
    char stack[SIZE];  // Private members
    int top;
};
```

### 🎯 Galutinė Išvada

> **ADT evoliucija** parodo, kaip programavimo kalbos ir paradigmos vystėsi sprendžiant realias problemas. Kiekvienas etapas atskleidžia naują problemą ir jos sprendimą, vedantį link modernių objektinio programavimo principų.

**Svarbiausias takeaway**: Suprasti **kodėl** tam tikri sprendimai yra geresni, o ne tik **kaip** juos implementuoti. Tai padės jums priimti geresnius dizaino sprendimus ateityje!

---

### Klausimų ir Užduočių Pavyzdžiai

#### 🤔 Diskusijos Klausimai
1. Kodėl `static` kintamieji 4 etape neleidžia kurti kelių stekų?
2. Kuo skiriasi "declaration" nuo "definition"?
3. Kodėl forward declaration leidžia kurti pointers, bet ne variables?
4. Kaip opaque pointers padeda užtikrinti API stabilumą?

#### 💻 Praktinės Užduotys
1. Implementuokite Queue ADT naudodami 7 etapą
2. Sukurkite Dynamic Array su automatic resizing
3. Padarykite Stack thread-safe naudodami mutex
4. Implementuokite Generic Stack naudodami void pointers

#### 🔍 Kodo Analizės Užduotys
1. Raskite klaidas pateiktuose kodo fragmentuose
2. Paaiškinkite, kodėl tam tikri kompiliavimo bandymai nepavyko
3. Pasiūlykite, kaip pagerinti duotą implementaciją

**Sėkmės mokantis! 🚀**
