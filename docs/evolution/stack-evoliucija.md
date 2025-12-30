---
title: "Nuo C link C++: Metodinis vadovas su Stack ADT evoliucija"
author: "Programavimo metodikos specialistas"
date: "2025-12-27"
keywords: "C++, programavimas, evoliucinis metodas, Stack ADT, objektinis programavimas"
---

# Nuo C link C++: Metodinis vadovas su Stack ADT evoliucija

## Įvadas: Evoliucinis mokymo metodas

Šis metodinis vadovas skirtas studentams, pereinantiems nuo C programavimo kalbos prie C++. Naudojamas evoliucinis metodas - palaipsnis kodo tobulinimas, rodantis, kaip procedūrinis programavimas natūraliai transformuojasi į objektinį programavimą.

**Metodikos esmė:** Kiekvienas žingsnis sprendžia ankstesnės versijos problemas ir pristato naują C++ koncepciją, išlaikant funkcionalumą, bet gerinant kodo kokybę.

### Kodėl Stack (stekas) kaip pavyzdys?

Stack duomenų struktūra idealiai tinka C++ mokymui, nes:

- **Paprasta koncepcija:** LIFO (Last In, First Out) principas
- **Aiškūs metodai:** push(), pop(), top()
- **Evoliucijos galimybės:** nuo globalių kintamųjų iki šiuolaikinių C++ klasių
- **Praktinis pritaikymas:** naudojama daugelyje algoritmų

---

## 1 etapas: Stack kaip "programa" (C stilius)

### Koncepcija

Pirmasis etapas pristato klasikinį C programavimo stilių su globaliais kintamaisiais ir funkcijomis. Šis metodas, nors paprastas ir intuityvus pradedantiesiems, atskleidžia fundamentalias problemas, kurias spręs vėlesni etapai. Globalūs kintamieji ir funkcijų atskyrimas nuo duomenų formuoja pagrindą supratimui, kodėl reikalingas objektinis programavimas.

### Kodas ir analizė

```c
// stack_1.c
#include <stdio.h>
#define STACK_SIZE 10

char stack[STACK_SIZE];  // Globalus masyvas
int  top = 0;           // Globalus indeksas

void push(char c);
char pop(void);

int main(void) {
    int c;
    
    // Įvedimas ir sudėjimas į steką
    while ('\n' != (c=getchar())) push(c);
    
    // Išėmimas ir spausdinimas (atvirkščiai)
    while ('\n' != (c=pop())) putchar(c);
    
    return 0;
}

void push(char c) {
    if (top < STACK_SIZE) 
        stack[top++] = c;
    else  
        printf("Stekas pilnas\n");
}

char pop(void) {
    if (top > 0) 
        return stack[--top];
    printf("\nStekas tuscias");
    return '\n';
}
```

**Veikimo pavyzdys:**
- Įvedimas: `12345`
- Išvedimas: `54321`

### 🔍 Problemos analizė

| Problema | Paaiškinimas | Pasekmės |
|----------|--------------|----------|
| Globalūs kintamieji | stack[] ir top prieinami visur | Sunku kontroliuoti prieigą |
| Vienas stekas | Negalima sukurti kelių steků | Ribota funkcionalumas |
| Nėra inkapsuliavimo | Duomenys ir funkcijos atskirti | Sunku palaikyti kodą |
| Nėra klaidų tikrinimo | Primityvus klaidų valdymas | Nesaugus kodas |

---

## 2 etapas: Stack kaip "modulis su nepaslėpta realizacija"

### Koncepcija

Antrasis etapas pristato modulinio programavimo pradžią - kodo skaidymą į header ir implementation failus. Šis žingsnis formuoja supratimą apie kodo organizavimą ir funkcijų deklaravimą bei apibrėžimą. Tačiau duomenų globalumas išlieka, atskleidžiant modulinio dizaino ribas be tikro inkapsuliavimo.

### Kodas ir analizė

```c
// stack_2.h
#define STACK_SIZE 10

void reset(void);
void push(char);
char pop(void);

// stack_2.c
#include <stdio.h>
#include "stack_2.h"

char stack[STACK_SIZE];  // Vis dar globalus
int  top = 0;

void reset(void) {
    top = 0;
}

void push(char c) {
    if (top < STACK_SIZE) 
        stack[top++] = c;
    else  
        printf("Stekas pilnas\n");
}

char pop(void) {
    if (top > 0) 
        return stack[--top];
    printf("\nStekas tuscias");
    return '\n';
}
```

### ⚠️ Kompiliatoriaus perspėjimai

```
Linker warning:
Public symbol '_stack' defined in both module DRIVER_2.OBJ and STACK_2.OBJ
Public symbol '_top' defined in both module DRIVER_2.OBJ and STACK_2.OBJ
```

### 🔍 Problemos analizė

| Pagerėjimas | Likusios problemos |
|-------------|-------------------|
| ✅ Modulinis dizainas | ❌ Duomenys vis dar globalūs |
| ✅ Header failas | ❌ Galima tiesiogiai keisti duomenis |
| ✅ reset() funkcija | ❌ Simbolių dubliavimas |

---

## 3 etapas: Stack kaip "modulis su paslėpta realizacija"

### Koncepcija

Trečiasis etapas pristato informacijos slėpimo principą naudojant `static` raktažodį. Šis konceptualus šuolis formuoja supratimą apie duomenų apsaugą ir modulio vidinės logikos paslėpimą. Linker klaidos tampa mokymo įrankiu, demonstruojančiu, kaip kompiliatorius apsaugo nuo neleistinos prieigos.

### Kodas ir analizė

```c
// stack_3.h
#define STACK_SIZE 10

void reset(void);
void push(char);
char pop(void);

// stack_3.c
#include <stdio.h>
#include "stack_3.h"

static char stack[STACK_SIZE];  // 🔒 Paslėpta!
static int  top = 0;
static int is_empty(void) { return (0 == top); }
static int is_full(void) { return (STACK_SIZE == top); }

void reset(void) {
    top = 0;
}

void push(char c) {
    if (!is_full()) 
        stack[top++] = c;
    else  
        printf("Stekas pilnas\n");
}

char pop(void) {
    if (!is_empty()) 
        return stack[--top];
    printf("\nStekas tuscias");
    return '\n';
}
```

### ❌ Linker klaidos

```
Link error: Unresolved external '_is_full' referenced from DRIVER_3.OBJ
Link error: Unresolved external '_stack' referenced from DRIVER_3.OBJ
Link error: Unresolved external '_top' referenced from DRIVER_3.OBJ
```

### 🔍 Analizė

| Pagerėjimas | Mokymosi vertė |
|-------------|----------------|
| ✅ static - duomenų paslėpimas | Informacijos slėpimo principas |
| ✅ Pagalbinės funkcijos paslėptos | Modulio vidinė logika |
| ✅ Linker klaidos rodo apsaugą | Kompiliatoriaus apsauga |

---

## 4 etapas: Stack kaip "tipas (modulyje)"

### Koncepcija

Ketvirtasis etapas pristato duomenų struktūrų koncepciją per `typedef struct`. Šis žingsnis formuoja supratimą apie duomenų ir funkcijų sąryšį, leidžia kurti kelis objektus ir pristato rodyklių perdavimo būtinybę. Tai tiltas tarp procedūrinio ir objektinio programavimo.

### Kodas ir analizė

```c
// stack_4.h
#define STACK_SIZE 10

typedef struct {
    char stack[STACK_SIZE];
    int  top;
} stack;

void reset(stack *);
void push(stack *, char);
char pop(stack *);

// stack_4.c
#include <stdio.h>
#include "stack_4.h"

static int is_empty(stack *id) {
    return (0 == id->top);
}

static int is_full(stack *id) {
    return (STACK_SIZE == id->top);
}

void reset(stack *id) {
    id->top = 0;
}

void push(stack *id, char c) {
    if (!is_full(id)) 
        id->stack[id->top++] = c;
    else  
        printf("Stekas pilnas\n");
}

char pop(stack *id) {
    if (!is_empty(id)) 
        return id->stack[--id->top];
    printf("\nStekas tuscias\n");
    return '\n';
}
```

### 🔍 Analizė

| Pagerėjimas | Likusios problemos |
|-------------|-------------------|
| ✅ Kelių steků galimybė | ❌ Duomenys vis dar prieinami |
| ✅ typedef struct | ❌ Reikia perduoti rodykles |
| ✅ Aiškesnė sintaksė | ❌ Galimi segmentation fault |

---

## 5 etapas: Stack kaip "struktūra-klasė" (C++ pradžia)

### Koncepcija

Penktasis etapas žymi perėjimą į C++ - pristato `struct` su metodais ir `::` operatorių. Šis konceptualus šuolis formuoja supratimą apie duomenų ir funkcijų suvienijimą vienoje struktūroje. Kompiliatoriaus klaidos atskleidžia prieigos kontrolės poreikį.

### Kodas ir analizė

```cpp
// stack_5.h
const int STACK_SIZE = 10;

struct stack {
    char stackas[STACK_SIZE];
    int  top;
    void reset();
    void push(char);
    char pop();
    int  is_empty();
    int  is_full();
};

// stack_5.cpp
#include <stdio.h>
#include "stack_5.h"

int stack::is_empty() { 
    return (0 == top); 
}

int stack::is_full() { 
    return (STACK_SIZE == top); 
}

void stack::reset() { 
    top = 0; 
}

void stack::push(char c) {
    if (!is_full()) 
        stackas[top++] = c;
    else  
        printf("Stekas pilnas\n");
}

char stack::pop() {
    if (!is_empty()) 
        return stackas[--top];
    printf("\nStekas tuscias\n");
    return '\n';
}
```

### 🔍 Analizė

| C++ naujovės | Problema |
|--------------|----------|
| struct su metodais | Duomenys ir funkcijos kartu |
| :: operatorius | Aiški priklausomybė klasei |
| const vietoj #define | Tipo saugumas |
| Klaida su reset() | Rodo, kad reikia public sekcijos! |

---

## 6 etapas: Stack kaip "klasė" (Informacijos slėpimas)

### Koncepcija

Šeštasis etapas pristato tikrą objektinį programavimą - `class` su `private` ir `public` sekcijomis bei konstruktorių. Šis konceptualus proveržis formuoja supratimą apie tikrą inkapsuliavimą, automatinį objektų inicializavimą ir kompiliatoriaus apsaugą nuo neleistinos prieigos.

### Kodas ir analizė

```cpp
// stack_6.h
const int STACK_SIZE = 10;

class stack {
private:  // 🔒 Paslėpta!
    char stackas[STACK_SIZE];
    int  top;
    int  is_empty();
    int  is_full();
    
public:   // 🌐 Viešas interfeisas
    stack();           // 🎉 Konstruktorius!
    void push(char);
    char pop();
};

// stack_6.cpp
#include <stdio.h>
#include "stack_6.h"

stack::stack() { 
    top = 0; 
}

int stack::is_empty() { 
    return (0 == top); 
}

int stack::is_full() { 
    return (STACK_SIZE == top); 
}

void stack::push(char c) {
    if (!is_full()) 
        stackas[top++] = c;
    else  
        printf("Stekas pilnas\n");
}

char stack::pop() {
    if (!is_empty()) 
        return stackas[--top];
    printf("\nStekas tuscias\n");
    return '\n';
}
```

### 🔍 Analizė

| C++ naujovės | Nauda |
|--------------|-------|
| private: sekcija | Tikras duomenų paslėpimas |
| public: sekcija | Aiškus interfeisas |
| Konstruktorius | Automatinis inicializavimas |
| Kompiliatoriaus apsauga | Neleidžia pažeisti inkapsuliavimo |

---

## 7 etapas: Stack kaip "klasė su dinamiška realizacija"

### Koncepcija

Septintasis etapas pristato dinaminio atminties valdymo koncepciją su `new`/`delete` operatoriais ir destruktoriumi. Šis žingsnis formuoja supratimą apie RAII (Resource Acquisition Is Initialization) principą ir automatinį išteklių valdymą. Parametrinis konstruktorius leidžia lanksčiai inicializuoti objektus.

### Kodas ir analizė

```cpp
// stack_7.h
class stack {
private:
    char *stackas;  // 🎯 Dinaminis masyvas!
    int  top;
    int  size;
    
public:
    stack(int);      // 🎉 Parametrinis konstruktorius!
    void reset();
    void push(char);
    char pop();
    int  is_empty();
    int  is_full();
    int  get_size();
    ~stack();        // 🎉 Destruktorius!
};

// stack_7.cpp
#include <stdio.h>
#include "stack_7.h"

stack::stack(int sz) { 
    stackas = new char[size = sz]; 
    reset(); 
}

void stack::reset() {
    top = 0; 
}

int stack::is_empty() { 
    return (0 == top); 
}

int stack::is_full() { 
    return (size == top); 
}

void stack::push(char c) {
    if (!is_full()) 
        stackas[top++] = c;
    else  
        printf("Stekas pilnas\n");
}

char stack::pop() {
    if (!is_empty()) 
        return stackas[--top];
    printf("\nStekas tuscias\n");
    return '\n';
}

int stack::get_size() { 
    return size; 
}

stack::~stack() { 
    delete [] stackas; 
}
```

### 🔍 Analizė

| C++ naujovės | Nauda |
|--------------|-------|
| Parametrinis konstruktorius | Lankstus inicializavimas |
| new/delete | Dinaminis atminties valdymas |
| Destruktorius | Automatinis išvalymas |
| cout vietoj printf | C++ I/O srautai |

---

## 8 etapas: Rule of Three - Kopijavimo semantika

### Koncepcija

Aštuntasis etapas pristato vieną svarbiausių C++ koncepcijų - **Rule of Three**. Šis principas formuoja supratimą apie objektų kopijavimo problemas ir deep copy būtinybę. Koncepcija atskleidžia, kodėl dinaminio atminties valdymo atveju reikalingi specialūs kopijos konstruktorius ir priskyrimo operatorius.

**Rule of Three taisyklė:** Jei klasei reikia vieno iš trijų - destruktoriaus, kopijos konstruktoriaus ar priskyrimo operatoriaus, tai greičiausiai reikia visų trijų.

### Problema su 7 etapu

```cpp
int main() {
    stack s1(10);
    s1.push('A');
    s1.push('B');
    
    stack s2 = s1;  // ⚠️ Kopijos konstruktorius!
    // arba
    stack s3(5);
    s3 = s1;        // ⚠️ Priskyrimo operatorius!
    
    return 0;       // 💥 CRASH! Double delete!
}
```

**Problema:** Kompiliatorius automatiškai sukuria "shallow copy" - kopijuoja tik pointer reikšmę, ne duomenis!

### Rule of Three sprendimas

```cpp
// stack_8.h
class stack {
private:
    char *stackas;
    int  top;
    int  size;
    
public:
    stack(int);                        // Konstruktorius
    stack(const stack& other);         // 🎉 Kopijos konstruktorius!
    stack& operator=(const stack& other); // 🎉 Priskyrimo operatorius!
    ~stack();                          // Destruktorius
    
    void reset();
    void push(char);
    char pop();
    int  is_empty();
    int  is_full();
    int  get_size();
};

// Kopijos konstruktorius (deep copy)
stack::stack(const stack& other) {
    size = other.size;
    top = other.top;
    stackas = new char[size];  // 🎯 Naujas masyvas!
    
    // Kopijuojame duomenis
    for(int i = 0; i <= top; i++) {
        stackas[i] = other.stackas[i];
    }
}

// Priskyrimo operatorius
stack& stack::operator=(const stack& other) {
    if(this == &other) {       // 🛡️ Apsauga nuo self-assignment
        return *this;
    }
    
    delete[] stackas;          // 🗑️ Išvalome seną atmintį
    
    size = other.size;
    top = other.top;
    stackas = new char[size];  // 🎯 Naujas masyvas!
    
    // Kopijuojame duomenis
    for(int i = 0; i <= top; i++) {
        stackas[i] = other.stackas[i];
    }
    
    return *this;              // 🔄 Grąžiname nuorodą
}
```

---

## 9 etapas: Rule of Five - Move semantika

### Koncepcija

Devintasis etapas pristato **Rule of Five** ir move semantikos koncepciją iš C++11. Šis žingsnis formuoja supratimą apie efektyvų objektų perkėlimą vietoj kopijavimo, ypač su temporary objektais. Move semantika drastiškai pagerina performance, nes "pavogia" duomenis vietoj jų kopijavimo.

**Rule of Five:** Rule of Three + move konstruktorius + move assignment operatorius.

### Problema su Rule of Three

```cpp
stack create_temp_stack() {
    stack temp(1000);
    temp.push('X');
    return temp;  // 💸 Brangus kopijavimas!
}

int main() {
    stack s1 = create_temp_stack();  // Copy constructor
    stack s2(500);
    s2 = create_temp_stack();        // Assignment operator
    
    // Kiekvienas iškvietimas kopijuoja 1000 char'ų masyvą!
    return 0;
}
```

### Move semantics sprendimas

```cpp
// Rule of Five papildymai (C++11)
stack(stack&& other) noexcept;     // 🎉 Move konstruktorius!
stack& operator=(stack&& other) noexcept; // 🎉 Move assignment!

// Move konstruktorius - "pavogti" duomenis
stack::stack(stack&& other) noexcept 
    : stackas(other.stackas),    // 🏃‍♂️ Paimame pointer
      top(other.top),
      size(other.size) 
{
    // Palikti other tuščią būsenę
    other.stackas = nullptr;
    other.top = 0;
    other.size = 0;
}

// Move assignment operator
stack& stack::operator=(stack&& other) noexcept {
    if(this == &other) {         // Self-assignment check
        return *this;
    }
    
    // Išvalome savo duomenis
    delete[] stackas;
    
    // "Pavogti" other duomenis
    stackas = other.stackas;
    top = other.top;
    size = other.size;
    
    // Palikti other tuščią būsenę
    other.stackas = nullptr;
    other.top = 0;
    other.size = 0;
    
    return *this;
}
```

---

## 10 etapas: Modern C++ Stack

### Koncepcija

Dešimtasis etapas pristato šiuolaikinį C++ stilių su templates, STL konteineriais ir C++11+ funkcijomis. Šis finalinis žingsnis demonstruoja, kaip evoliucijos metu įgytos žinios leidžia suprasti ir efektyviai naudoti šiuolaikines C++ galimybes. Template sistema leidžia kurti tipo-saugius ir lankščius sprendimus.

### Modern C++ implementacija

```cpp
// modern_stack.hpp
#pragma once
#include <vector>
#include <stdexcept>
#include <iostream>

template<typename T>
class Stack {
private:
    std::vector<T> data;
    
public:
    // Konstruktoriai
    Stack() = default;
    explicit Stack(size_t initial_capacity) {
        data.reserve(initial_capacity);
    }
    
    // Rule of Five (C++11) - kompiliatorius automatiškai
    Stack(const Stack&) = default;
    Stack& operator=(const Stack&) = default;
    Stack(Stack&&) = default;
    Stack& operator=(Stack&&) = default;
    ~Stack() = default;
    
    // Pagrindinės operacijos
    void push(const T& item) {
        data.push_back(item);
    }
    
    void push(T&& item) {  // Move semantics
        data.push_back(std::move(item));
    }
    
    template<typename... Args>
    void emplace(Args&&... args) {  // Perfect forwarding
        data.emplace_back(std::forward<Args>(args)...);
    }
    
    T pop() {
        if (empty()) {
            throw std::runtime_error("Stack is empty");
        }
        T result = std::move(data.back());
        data.pop_back();
        return result;
    }
    
    const T& top() const {
        if (empty()) {
            throw std::runtime_error("Stack is empty");
        }
        return data.back();
    }
    
    // Utility funkcijos
    [[nodiscard]] bool empty() const noexcept {
        return data.empty();
    }
    
    [[nodiscard]] size_t size() const noexcept {
        return data.size();
    }
    
    void clear() noexcept {
        data.clear();
    }
    
    // Iterator support
    auto begin() { return data.begin(); }
    auto end() { return data.end(); }
    auto begin() const { return data.cbegin(); }
    auto end() const { return data.cend(); }
};
```

### 🔍 Modern C++ naujovės

| Funkcija | C++ versija | Nauda |
|----------|-------------|-------|
| template<typename T> | C++98 | Tipo saugumas ir lankstumas |
| std::vector | C++98 | Automatinis atminties valdymas |
| = default | C++11 | Aiškus intent |
| noexcept | C++11 | Optimizacijos galimybės |
| [[nodiscard]] | C++17 | Perspėjimai apie nepanaudotas reikšmes |
| auto | C++11/14 | Tipo išvedimas |
| Range-based for | C++11 | Paprastesnis iteravimas |
| Perfect forwarding | C++11 | Efektyvus argumentų perdavimas |

---

## Išvados

### Evoliucinio metodo privalumai

1. **Natūralus progresavimas:** Nuo paprastų prie sudėtingų koncepcijų
2. **Motyvacija:** Kiekvienas žingsnis sprendžia realią problemą
3. **Praktinis mokymasis:** Ta pati užduotis, skirtingi sprendimai
4. **Klaidų mokymasis:** Klaidos tampa mokymo įrankiu

### Pagrindinės C++ koncepcijos

- **Inkapsuliavimas:** private/public
- **Konstruktoriai/destruktoriai:** Automatinis valdymas
- **Rule of Three/Five:** Objektų kopijavimo ir perkėlimo valdymas
- **Templates:** Tipo saugumas ir lankstumas
- **STL:** Standartinės bibliotekos

### Tolesnio mokymosi kryptys

- **Paveldėjimas:** class Derived : public Base
- **Polimorfizmas:** Virtual funkcijos
- **Templates:** Generinis programavimas
- **STL:** Konteineriai ir algoritmai
- **Modern C++:** Smart pointers, lambdas, ranges

> **Svarbu:** Šis vadovas - tik pradžia. C++ - plati ir gili kalba, reikalaujanti nuolatinio mokymosi ir praktikos.
> 