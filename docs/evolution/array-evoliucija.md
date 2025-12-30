---
title: "Objektų masyvų evoliucija C++: Nuo C masyvų iki STL konteinerių"
author: "Programavimo metodikos specialistas"
date: "2025-12-27"
keywords: "objektų masyvai, STL, rodyklės, agregacija, 'Student' klasė, evoliucinis metodas"
---

# Objektų masyvų evoliucija C++: Nuo C masyvų iki STL konteinerių

## Įvadas: Kodėl objektų masyvai sudėtingi?

Objektų masyvai C++ kalboje yra viena iš sudėtingiausių temų, nes čia susipina:

- **Atminties valdymas** (stekas vs heap)
- **Objektų gyvavimo ciklas** (konstruktoriai/destruktoriai)
- **Rodyklių semantika** (rodyklė į masyvą vs rodyklių masyvas)
- **Polimorfizmas** (virtualūs metodai masyvo elementams)
- **STL abstrakcijos** (array, vector, smart_ptr)

Šis vadovas naudoja **evoliucinį metodą** - kiekvienas etapas sprendžia ankstesnio problemas ir pristato naują konceptą.

---

## 1 etapas: C stiliaus masyvai su objektais

### Koncepcija

Pradedame nuo paprasčiausio - C stiliaus masyvų su objektais. Čia iškart matome pirmąsias problemas.

### Kodas ir analizė

```cpp
// student_1.cpp - C stiliaus masyvas su objektais
#include <iostream>
#include <cstring>

class Student {
public:
    char name[50];
    int age;
    double grade;
    
    // Konstruktorius
    Student() {
        strcpy(name, "Unknown");
        age = 0;
        grade = 0.0;
        std::cout << "📚 Student konstruktorius: " << name << std::endl;
    }
    
    // Parametrinis konstruktorius
    Student(const char* n, int a, double g) {
        strcpy(name, n);
        age = a;
        grade = g;
        std::cout << "📚 Student konstruktorius: " << name << std::endl;
    }
    
    // Destruktorius
    ~Student() {
        std::cout << "🗑️ Student destruktorius: " << name << std::endl;
    }
    
    void print() const {
        std::cout << "Student: " << name << ", Age: " << age 
                  << ", Grade: " << grade << std::endl;
    }
};

int main() {
    std::cout << "=== C stiliaus masyvas su objektais ===\n";
    
    // 💥 PROBLEMA #1: Tik default konstruktorius!
    Student students[3];  // Visi objektai sukurti su default konstruktoriumi
    
    std::cout << "\n--- Pradinis masyvas ---\n";
    for (int i = 0; i < 3; i++) {
        students[i].print();
    }
    
    // Reikia rankiniu būdu keisti duomenis
    strcpy(students[0].name, "Jonas");
    students[0].age = 20;
    students[0].grade = 8.5;
    
    strcpy(students[1].name, "Petras");
    students[1].age = 21;
    students[1].grade = 9.0;
    
    strcpy(students[2].name, "Marija");
    students[2].age = 19;
    students[2].grade = 8.8;
    
    std::cout << "\n--- Po duomenų keitimo ---\n";
    for (int i = 0; i < 3; i++) {
        students[i].print();
    }
    
    // 💥 PROBLEMA #2: Negalima perduoti į funkciją kaip objekto
    // void process_students(Student students[3]) - neteisingas tipas!
    
    std::cout << "\n--- Destruktoriai ---\n";
    return 0;  // Čia iškviečiami destruktoriai
}
```

**Rezultatas:**
```
=== C stiliaus masyvas su objektais ===
📚 Student konstruktorius: Unknown
📚 Student konstruktorius: Unknown
📚 Student konstruktorius: Unknown

--- Pradinis masyvas ---
Student: Unknown, Age: 0, Grade: 0
Student: Unknown, Age: 0, Grade: 0
Student: Unknown, Age: 0, Grade: 0

--- Po duomenų keitimo ---
Student: Jonas, Age: 20, Grade: 8.5
Student: Petras, Age: 21, Grade: 9
Student: Marija, Age: 19, Grade: 8.8

--- Destruktoriai ---
🗑️ Student destruktorius: Marija
🗑️ Student destruktorius: Petras
🗑️ Student destruktorius: Jonas
```

### 🔍 Problemos analizė

| Problema | Paaiškkinimas | Pasekmės |
|----------|---------------|----------|
| **Tik default konstruktorius** | `Student arr[3]` kviečia tik default konstruktorių | Reikia rankiniu būdu keisti duomenis |
| **Masyvo tipo painiava** | `Student arr[3]` vs `Student* arr` | Neteisingas funkcijų parametrų tipas |
| **Nėra inicializacijos kontrolės** | Negalima sukurti su konkrečiais duomenimis | Dvigubas darbas: sukurti + keisti |
| **C stiliaus stringai** | `char name[50]` + `strcpy` | Nesaugus, riboto dydžio |

### 💡 Mokymosi tikslai

- Suprasti, kad objektų masyvas kviečia konstruktorius
- Matyti C stiliaus masyvų apribojimus
- Pažinti destruktorių iškvietimo tvarką (atvirkščiai)

---

## 2 etapas: Inicializacijos sąrašas (C++11)

### Koncepcija

C++11 įvedė inicializacijos sąrašus, kurie leidžia sukurti masyvą su konkrečiais duomenimis.

### Kodas ir analizė

```cpp
// student_2.cpp - Inicializacijos sąrašas
#include <iostream>
#include <string>

class Student {
private:
    std::string name;
    int age;
    double grade;
    
public:
    // Default konstruktorius
    Student() : name("Unknown"), age(0), grade(0.0) {
        std::cout << "📚 Default konstruktorius: " << name << std::endl;
    }
    
    // Parametrinis konstruktorius
    Student(const std::string& n, int a, double g) 
        : name(n), age(a), grade(g) {
        std::cout << "📚 Parametrinis konstruktorius: " << name << std::endl;
    }
    
    // Copy konstruktorius
    Student(const Student& other) 
        : name(other.name), age(other.age), grade(other.grade) {
        std::cout << "📋 Copy konstruktorius: " << name << std::endl;
    }
    
    // Destruktorius
    ~Student() {
        std::cout << "🗑️ Destruktorius: " << name << std::endl;
    }
    
    void print() const {
        std::cout << "Student: " << name << ", Age: " << age 
                  << ", Grade: " << grade << std::endl;
    }
    
    const std::string& get_name() const { return name; }
};

// Funkcija, kuri priima masyvą
void print_students(const Student students[], int count) {
    std::cout << "\n--- Funkcijoje print_students ---\n";
    for (int i = 0; i < count; i++) {
        students[i].print();
    }
}

// 💥 PROBLEMA: Neteisingas masyvo perdavimas
void wrong_function(Student students[3]) {  // Iš tikrųjų Student*
    std::cout << "sizeof(students) = " << sizeof(students) << std::endl;  // 8 bytes (pointer)
    std::cout << "Tikrasis sizeof(Student[3]) = " << sizeof(Student) * 3 << std::endl;
}

int main() {
    std::cout << "=== Inicializacijos sąrašas ===\n";
    
    // ✅ C++11 inicializacijos sąrašas
    Student students[] = {
        Student("Jonas", 20, 8.5),
        Student("Petras", 21, 9.0),
        Student("Marija", 19, 8.8)
    };
    
    const int count = sizeof(students) / sizeof(students[0]);
    std::cout << "Masyvo dydis: " << count << std::endl;
    
    std::cout << "\n--- Pradinis masyvas ---\n";
    for (int i = 0; i < count; i++) {
        students[i].print();
    }
    
    // Funkcijos iškvietimas
    print_students(students, count);
    
    // Masyvo tipo demonstracija
    std::cout << "\n--- Masyvo tipo problema ---\n";
    std::cout << "sizeof(students) main'e = " << sizeof(students) << std::endl;
    wrong_function(students);
    
    // 💥 PROBLEMA: Negalima keisti masyvo dydžio
    // students[3] = Student("Ona", 22, 7.5);  // KLAIDA!
    
    std::cout << "\n--- Destruktoriai ---\n";
    return 0;
}
```

**Rezultatas:**
```
=== Inicializacijos sąrašas ===
📚 Parametrinis konstruktorius: Jonas
📚 Parametrinis konstruktorius: Petras
📚 Parametrinis konstruktorius: Marija
Masyvo dydis: 3

--- Pradinis masyvas ---
Student: Jonas, Age: 20, Grade: 8.5
Student: Petras, Age: 21, Grade: 9
Student: Marija, Age: 19, Grade: 8.8

--- Funkcijoje print_students ---
Student: Jonas, Age: 20, Grade: 8.5
Student: Petras, Age: 21, Grade: 9
Student: Marija, Age: 19, Grade: 8.8

--- Masyvo tipo problema ---
sizeof(students) main'e = 96
sizeof(students) = 8
Tikrasis sizeof(Student[3]) = 96

--- Destruktoriai ---
🗑️ Destruktorius: Marija
🗑️ Destruktorius: Petras
🗑️ Destruktorius: Jonas
```

### 🔍 Pagerėjimai ir likusios problemos

| Pagerėjimas | Likusios problemos |
|-------------|-------------------|
| ✅ Inicializacija su parametrais | ❌ Fiksuotas dydis compile time |
| ✅ std::string vietoj char[] | ❌ Masyvas "virsta" rodykle funkcijose |
| ✅ Automatinis dydžio skaičiavimas | ❌ Negalima keisti dydžio runtime |

### 💡 Mokymosi tikslai

- Suprasti inicializacijos sąrašų sintaksę
- Matyti masyvo "virsmo" rodykle problemą
- Pažinti sizeof trikį masyvo dydžiui skaičiuoti

---

## 3 etapas: Dinaminiai masyvai (new/delete)

### Koncepcija

Kai reikia keisti masyvo dydį runtime, naudojame dinaminį atminties paskirstymą.

### Kodas ir analizė

```cpp
// student_3.cpp - Dinaminiai masyvai
#include <iostream>
#include <string>

class Student {
private:
    std::string name;
    int age;
    double grade;
    
public:
    Student() : name("Unknown"), age(0), grade(0.0) {
        std::cout << "📚 Default konstruktorius: " << name << std::endl;
    }
    
    Student(const std::string& n, int a, double g) 
        : name(n), age(a), grade(g) {
        std::cout << "📚 Parametrinis konstruktorius: " << name << std::endl;
    }
    
    ~Student() {
        std::cout << "🗑️ Destruktorius: " << name << std::endl;
    }
    
    void print() const {
        std::cout << "Student: " << name << ", Age: " << age 
                  << ", Grade: " << grade << std::endl;
    }
    
    // Setter metodai dinaminiam užpildymui
    void set_data(const std::string& n, int a, double g) {
        name = n;
        age = a;
        grade = g;
    }
};

class StudentManager {
private:
    Student* students;  // Rodyklė į dinaminį masyvą
    int capacity;
    int count;
    
public:
    StudentManager(int initial_capacity) 
        : capacity(initial_capacity), count(0) {
        std::cout << "🏗️ Kuriamas StudentManager su capacity: " << capacity << std::endl;
        students = new Student[capacity];  // 💥 Tik default konstruktoriai!
    }
    
    ~StudentManager() {
        std::cout << "🗑️ StudentManager destruktorius\n";
        delete[] students;  // ✅ Automatiškai iškviečia visų objektų destruktorius
    }
    
    void add_student(const std::string& name, int age, double grade) {
        if (count >= capacity) {
            std::cout << "❌ Masyvas pilnas!\n";
            return;
        }
        
        students[count].set_data(name, age, grade);
        count++;
    }
    
    void print_all() const {
        std::cout << "\n--- Visi studentai (" << count << "/" << capacity << ") ---\n";
        for (int i = 0; i < count; i++) {
            students[i].print();
        }
    }
    
    // 💥 PROBLEMA: Nėra copy konstruktoriaus ir assignment operatoriaus
    // Shallow copy problema!
};

// Demonstracija su funkcija
void test_dynamic_array() {
    std::cout << "\n=== Funkcijos scope testas ===\n";
    
    StudentManager manager(2);
    manager.add_student("Tomas", 22, 7.8);
    manager.add_student("Ona", 20, 9.2);
    manager.print_all();
    
    // manager sunaikinamas čia
}

int main() {
    std::cout << "=== Dinaminiai masyvai ===\n";
    
    // Paprastas dinaminis masyvas
    int size;
    std::cout << "Įveskite studentų skaičių: ";
    std::cin >> size;
    
    Student* students = new Student[size];  // Default konstruktoriai
    
    // Užpildymas duomenimis
    for (int i = 0; i < size; i++) {
        std::string name = "Student" + std::to_string(i + 1);
        students[i].set_data(name, 20 + i, 7.0 + i * 0.5);
    }
    
    std::cout << "\n--- Dinaminis masyvas ---\n";
    for (int i = 0; i < size; i++) {
        students[i].print();
    }
    
    delete[] students;  // ✅ Destruktoriai iškviečiami
    
    // Objekto su dinaminiu masyvu testas
    test_dynamic_array();
    
    // 💥 SHALLOW COPY PROBLEMA
    std::cout << "\n=== Shallow copy problema ===\n";
    {
        StudentManager manager1(2);
        manager1.add_student("Originalus", 25, 8.0);
        
        // StudentManager manager2 = manager1;  // 💥 CRASH! Double delete
        // Ši eilutė sukeltų crash'ą, nes abu objektai bandytų ištrinti tą patį masyvą
    }
    
    return 0;
}
```

**Rezultatas:**
```
=== Dinaminiai masyvai ===
Įveskite studentų skaičių: 3
📚 Default konstruktorius: Unknown
📚 Default konstruktorius: Unknown
📚 Default konstruktorius: Unknown

--- Dinaminis masyvas ---
Student: Student1, Age: 20, Grade: 7
Student: Student2, Age: 21, Grade: 7.5
Student: Student3, Age: 22, Grade: 8

🗑️ Destruktorius: Student3
🗑️ Destruktorius: Student2
🗑️ Destruktorius: Student1

=== Funkcijos scope testas ===
🏗️ Kuriamas StudentManager su capacity: 2
📚 Default konstruktorius: Unknown
📚 Default konstruktorius: Unknown

--- Visi studentai (2/2) ---
Student: Tomas, Age: 22, Grade: 7.8
Student: Ona, Age: 20, Grade: 9.2

🗑️ StudentManager destruktorius
🗑️ Destruktorius: Ona
🗑️ Destruktorius: Tomas

=== Shallow copy problema ===
🏗️ Kuriamas StudentManager su capacity: 2
📚 Default konstruktorius: Unknown
📚 Default konstruktorius: Unknown
🗑️ StudentManager destruktorius
🗑️ Destruktorius: Originalus
🗑️ Destruktorius: Unknown
```

### 🔍 Problemos analizė

| Problema | Paaiškkinimas | Sprendimas |
|----------|---------------|------------|
| **Tik default konstruktoriai** | `new Student[n]` kviečia tik default | Naudoti placement new arba vector |
| **Shallow copy** | Kompiliatorius sukuria shallow copy | Implementuoti Rule of Three |
| **Memory leak rizika** | Pamiršus `delete[]` - memory leak | Naudoti RAII arba smart pointers |
| **Double delete** | Kopijavimas sukelia double delete | Rule of Three arba delete copy |

### 💡 Mokymosi tikslai

- Suprasti new[] ir delete[] sintaksę
- Matyti shallow copy problemą
- Pažinti RAII principą su dinaminiais masyvais

---

## 4 etapas: Rule of Three implementacija

### Koncepcija

Kai klasė valdo dinaminius išteklius, reikia implementuoti Rule of Three: destruktorių, copy konstruktorių ir assignment operatorių.

### Kodas ir analizė

```cpp
// student_4.cpp - Rule of Three
#include <iostream>
#include <string>

class Student {
private:
    std::string name;
    int age;
    double grade;
    
public:
    Student() : name("Unknown"), age(0), grade(0.0) {
        std::cout << "📚 Default konstruktorius: " << name << std::endl;
    }
    
    Student(const std::string& n, int a, double g) 
        : name(n), age(a), grade(g) {
        std::cout << "📚 Parametrinis konstruktorius: " << name << std::endl;
    }
    
    ~Student() {
        std::cout << "🗑️ Destruktorius: " << name << std::endl;
    }
    
    void print() const {
        std::cout << "Student: " << name << ", Age: " << age 
                  << ", Grade: " << grade << std::endl;
    }
    
    void set_data(const std::string& n, int a, double g) {
        name = n; age = a; grade = g;
    }
};

class StudentManager {
private:
    Student* students;
    int capacity;
    int count;
    
public:
    // Konstruktorius
    StudentManager(int initial_capacity) 
        : capacity(initial_capacity), count(0) {
        std::cout << "🏗️ StudentManager konstruktorius (capacity: " << capacity << ")\n";
        students = new Student[capacity];
    }
    
    // 1. Destruktorius
    ~StudentManager() {
        std::cout << "🗑️ StudentManager destruktorius\n";
        delete[] students;
    }
    
    // 2. Copy konstruktorius (deep copy)
    StudentManager(const StudentManager& other) 
        : capacity(other.capacity), count(other.count) {
        std::cout << "📋 StudentManager copy konstruktorius\n";
        
        students = new Student[capacity];  // Naujas masyvas
        
        // Kopijuojame duomenis
        for (int i = 0; i < count; i++) {
            students[i] = other.students[i];  // Student assignment
        }
    }
    
    // 3. Assignment operatorius
    StudentManager& operator=(const StudentManager& other) {
        std::cout << "📝 StudentManager assignment operatorius\n";
        
        if (this == &other) {  // Self-assignment apsauga
            return *this;
        }
        
        // Išvalome seną atmintį
        delete[] students;
        
        // Kopijuojame naują
        capacity = other.capacity;
        count = other.count;
        students = new Student[capacity];
        
        for (int i = 0; i < count; i++) {
            students[i] = other.students[i];
        }
        
        return *this;
    }
    
    void add_student(const std::string& name, int age, double grade) {
        if (count >= capacity) {
            std::cout << "❌ Masyvas pilnas!\n";
            return;
        }
        
        students[count].set_data(name, age, grade);
        count++;
    }
    
    void print_all() const {
        std::cout << "\n--- StudentManager (" << count << "/" << capacity << ") ---\n";
        for (int i = 0; i < count; i++) {
            students[i].print();
        }
    }
    
    int get_count() const { return count; }
};

// Funkcija, kuri testuoja kopijavimą
StudentManager create_test_manager() {
    std::cout << "\n=== Funkcijoje create_test_manager ===\n";
    StudentManager manager(3);
    manager.add_student("Funkcijos studentas", 23, 8.5);
    return manager;  // Copy konstruktorius arba move (C++11)
}

int main() {
    std::cout << "=== Rule of Three ===\n";
    
    // Originalus objektas
    StudentManager manager1(2);
    manager1.add_student("Jonas", 20, 8.5);
    manager1.add_student("Petras", 21, 9.0);
    manager1.print_all();
    
    // Copy konstruktorius testas
    std::cout << "\n=== Copy konstruktorius ===\n";
    StudentManager manager2 = manager1;  // Copy konstruktorius
    manager2.print_all();
    
    // Assignment operatorius testas
    std::cout << "\n=== Assignment operatorius ===\n";
    StudentManager manager3(1);
    manager3.add_student("Marija", 19, 8.8);
    manager3.print_all();
    
    manager3 = manager1;  // Assignment operatorius
    manager3.print_all();
    
    // Self-assignment testas
    std::cout << "\n=== Self-assignment testas ===\n";
    manager1 = manager1;  // Turi būti saugus
    manager1.print_all();
    
    // Return by value testas
    std::cout << "\n=== Return by value testas ===\n";
    StudentManager manager4 = create_test_manager();
    manager4.print_all();
    
    std::cout << "\n=== Destruktoriai ===\n";
    return 0;
}
```

**Rezultatas:**
```
=== Rule of Three ===
🏗️ StudentManager konstruktorius (capacity: 2)
📚 Default konstruktorius: Unknown
📚 Default konstruktorius: Unknown

--- StudentManager (2/2) ---
Student: Jonas, Age: 20, Grade: 8.5
Student: Petras, Age: 21, Grade: 9

=== Copy konstruktorius ===
📋 StudentManager copy konstruktorius
📚 Default konstruktorius: Unknown
📚 Default konstruktorius: Unknown

--- StudentManager (2/2) ---
Student: Jonas, Age: 20, Grade: 8.5
Student: Petras, Age: 21, Grade: 9

=== Assignment operatorius ===
🏗️ StudentManager konstruktorius (capacity: 1)
📚 Default konstruktorius: Unknown

--- StudentManager (1/1) ---
Student: Marija, Age: 19, Grade: 8.8

📝 StudentManager assignment operatorius
🗑️ Destruktorius: Marija
📚 Default konstruktorius: Unknown
📚 Default konstruktorius: Unknown

--- StudentManager (2/2) ---
Student: Jonas, Age: 20, Grade: 8.5
Student: Petras, Age: 21, Grade: 9

=== Self-assignment testas ===
📝 StudentManager assignment operatorius

--- StudentManager (2/2) ---
Student: Jonas, Age: 20, Grade: 8.5
Student: Petras, Age: 21, Grade: 9

=== Return by value testas ===

=== Funkcijoje create_test_manager ===
🏗️ StudentManager konstruktorius (capacity: 3)
📚 Default konstruktorius: Unknown
📚 Default konstruktorius: Unknown
📚 Default konstruktorius: Unknown

--- StudentManager (1/3) ---
Student: Funkcijos studentas, Age: 23, Grade: 8.5

=== Destruktoriai ===
🗑️ StudentManager destruktorius
🗑️ Destruktorius: Funkcijos studentas
🗑️ Destruktorius: Unknown
🗑️ Destruktorius: Unknown
🗑️ StudentManager destruktorius
🗑️ Destruktorius: Jonas
🗑️ Destruktorius: Petras
🗑️ StudentManager destruktorius
🗑️ Destruktorius: Jonas
🗑️ Destruktorius: Petras
🗑️ StudentManager destruktorius
🗑️ Destruktorius: Jonas
🗑️ Destruktorius: Petras
🗑️ StudentManager destruktorius
🗑️ Destruktorius: Jonas
🗑️ Destruktorius: Petras
```

### 🔍 Rule of Three analizė

| Komponentas | Paskirtis | Kada iškviečiamas |
|-------------|-----------|-------------------|
| **Destruktorius** | Atlaisvina dinaminę atmintį | Objekto sunaikinimas |
| **Copy konstruktorius** | Deep copy sukūrimas | `Type obj2 = obj1;` |
| **Assignment operatorius** | Deep copy priskyrimas | `obj2 = obj1;` |

### 💡 Mokymosi tikslai

- Implementuoti Rule of Three
- Suprasti deep copy vs shallow copy
- Matyti self-assignment apsaugos poreikį

---

## 5 etapas: Rodyklių masyvas vs masyvo rodyklė

### Koncepcija

Viena iš didžiausių painiavų - skirtumas tarp "rodyklės į masyvą" ir "rodyklių masyvo". Ypač svarbu polimorfiniams objektams.

### Kodas ir analizė

```cpp
// student_5.cpp - Rodyklių semantika
#include <iostream>
#include <string>

class Student {
protected:
    std::string name;
    int age;
    
public:
    Student(const std::string& n, int a) : name(n), age(a) {
        std::cout << "📚 Student konstruktorius: " << name << std::endl;
    }
    
    virtual ~Student() {
        std::cout << "🗑️ Student destruktorius: " << name << std::endl;
    }
    
    virtual void print() const {
        std::cout << "Student: " << name << ", Age: " << age << std::endl;
    }
    
    virtual std::string get_type() const { return "Student"; }
};

class GraduateStudent : public Student {
private:
    std::string thesis_topic;
    
public:
    GraduateStudent(const std::string& n, int a, const std::string& topic) 
        : Student(n, a), thesis_topic(topic) {
        std::cout << "🎓 GraduateStudent konstruktorius: " << name << std::endl;
    }
    
    ~GraduateStudent() override {
        std::cout << "🗑️ GraduateStudent destruktorius: " << name << std::endl;
    }
    
    void print() const override {
        std::cout << "Graduate Student: " << name << ", Age: " << age 
                  << ", Thesis: " << thesis_topic << std::endl;
    }
    
    std::string get_type() const override { return "GraduateStudent"; }
};

void demonstrate_array_types() {
    std::cout << "\n=== 1. Objektų masyvas (stekas) ===\n";
    
    // Objektų masyvas - visi objektai sukurti steke
    Student students_array[3] = {
        Student("Jonas", 20),
        Student("Petras", 21),
        Student("Marija", 19)
    };
    
    std::cout << "Masyvo dydis: " << sizeof(students_array) << " bytes\n";
    std::cout << "Vieno objekto dydis: " << sizeof(Student) << " bytes\n";
    
    for (int i = 0; i < 3; i++) {
        students_array[i].print();
    }
    
    std::cout << "\n=== 2. Rodyklė į masyvą ===\n";
    
    // Rodyklė į masyvą - rodo į visą masyvą
    Student (*ptr_to_array)[3] = &students_array;
    
    std::cout << "ptr_to_array dydis: " << sizeof(ptr_to_array) << " bytes (rodyklė)\n";
    std::cout << "(*ptr_to_array) dydis: " << sizeof(*ptr_to_array) << " bytes (masyvas)\n";
    
    // Prieiga per rodyklę į masyvą
    for (int i = 0; i < 3; i++) {
        (*ptr_to_array)[i].print();
    }
    
    std::cout << "\n=== 3. Rodyklių masyvas (stekas) ===\n";
    
    // Rodyklių masyvas - masyvas rodyklių
    Student* ptr_array[3];
    ptr_array[0] = &students_array[0];
    ptr_array[1] = &students_array[1];
    ptr_array[2] = &students_array[2];
    
    std::cout << "ptr_array dydis: " << sizeof(ptr_array) << " bytes (3 rodyklės)\n";
    std::cout << "Vienos rodyklės dydis: " << sizeof(Student*) << " bytes\n";
    
    for (int i = 0; i < 3; i++) {
        ptr_array[i]->print();
    }
    
    std::cout << "\n=== 4. Dinaminis rodyklių masyvas ===\n";
    
    // Dinaminis rodyklių masyvas
    Student** dynamic_ptr_array = new Student*[3];
    dynamic_ptr_array[0] = new Student("Tomas", 22);
    dynamic_ptr_array[1] = new Student("Ona", 20);
    dynamic_ptr_array[2] = new Student("Lukas", 23);
    
    std::cout << "dynamic_ptr_array dydis: " << sizeof(dynamic_ptr_array) << " bytes (rodyklė)\n";
    
    for (int i = 0; i < 3; i++) {
        dynamic_ptr_array[i]->print();
    }
    
    // Išvalymas
    for (int i = 0; i < 3; i++) {
        delete dynamic_ptr_array[i];
    }
    delete[] dynamic_ptr_array;
}

void demonstrate_polymorphism() {
    std::cout << "\n=== POLIMORFIZMAS ===\n";
    
    // 💥 PROBLEMA: Objektų masyvas su polimorfizmu
    std::cout << "\n--- Objektų masyvas (object slicing!) ---\n";
    Student mixed_array[3] = {
        Student("Jonas", 20),
        GraduateStudent("Petras", 25, "AI Research"),  // 💥 Object slicing!
        Student("Marija", 19)
    };
    
    for (int i = 0; i < 3; i++) {
        std::cout << "Tipas: " << mixed_array[i].get_type() << " - ";
        mixed_array[i].print();  // Neteisingas polimorfizmas!
    }
    
    // ✅ SPRENDIMAS: Rodyklių masyvas
    std::cout << "\n--- Rodyklių masyvas (teisingas polimorfizmas) ---\n";
    Student* polymorphic_array[3];
    polymorphic_array[0] = new Student("Jonas", 20);
    polymorphic_array[1] = new GraduateStudent("Petras", 25, "AI Research");
    polymorphic_array[2] = new Student("Marija", 19);
    
    for (int i = 0; i < 3; i++) {
        std::cout << "Tipas: " << polymorphic_array[i]->get_type() << " - ";
        polymorphic_array[i]->print();  // ✅ Teisingas polimorfizmas!
    }
    
    // Išvalymas
    for (int i = 0; i < 3; i++) {
        delete polymorphic_array[i];
    }
}

int main() {
    std::cout << "=== Rodyklių semantika ===\n";
    
    demonstrate_array_types();
    demonstrate_polymorphism();
    
    std::cout << "\n=== Destruktoriai ===\n";
    return 0;
}
```

**Rezultatas:**
```
=== Rodyklių semantika ===

=== 1. Objektų masyvas (stekas) ===
📚 Student konstruktorius: Jonas
📚 Student konstruktorius: Petras
📚 Student konstruktorius: Marija
Masyvo dydis: 96 bytes
Vieno objekto dydis: 32 bytes

Student: Jonas, Age: 20
Student: Petras, Age: 21
Student: Marija, Age: 19

=== 2. Rodyklė į masyvą ===
ptr_to_array dydis: 8 bytes (rodyklė)
(*ptr_to_array) dydis: 96 bytes (masyvas)

Student: Jonas, Age: 20
Student: Petras, Age: 21
Student: Marija, Age: 19

=== 3. Rodyklių masyvas (stekas) ===
ptr_array dydis: 24 bytes (3 rodyklės)
Vienos rodyklės dydis: 8 bytes

Student: Jonas, Age: 20
Student: Petras, Age: 21
Student: Marija, Age: 19

=== 4. Dinaminis rodyklių masyvas ===
📚 Student konstruktorius: Tomas
📚 Student konstruktorius: Ona
📚 Student konstruktorius: Lukas
dynamic_ptr_array dydis: 8 bytes (rodyklė)

Student: Tomas, Age: 22
Student: Ona, Age: 20
Student: Lukas, Age: 23

🗑️ Student destruktorius: Lukas
🗑️ Student destruktorius: Ona
🗑️ Student destruktorius: Tomas

=== POLIMORFIZMAS ===

--- Objektų masyvas (object slicing!) ---
📚 Student konstruktorius: Jonas
📚 Student konstruktorius: Petras
🎓 GraduateStudent konstruktorius: Petras
🗑️ GraduateStudent destruktorius: Petras
📚 Student konstruktorius: Marija

Tipas: Student - Student: Jonas, Age: 20
Tipas: Student - Student: Petras, Age: 25
Tipas: Student - Student: Marija, Age: 19

--- Rodyklių masyvas (teisingas polimorfizmas) ---
📚 Student konstruktorius: Jonas
📚 Student konstruktorius: Petras
🎓 GraduateStudent konstruktorius: Petras
📚 Student konstruktorius: Marija

Tipas: Student - Student: Jonas, Age: 20
Tipas: GraduateStudent - Graduate Student: Petras, Age: 25, Thesis: AI Research
Tipas: Student - Student: Marija, Age: 19

🗑️ Student destruktorius: Marija
🗑️ GraduateStudent destruktorius: Petras
🗑️ Student destruktorius: Petras
🗑️ Student destruktorius: Jonas

=== Destruktoriai ===
🗑️ Student destruktorius: Marija
🗑️ Student destruktorius: Petras
🗑️ Student destruktorius: Jonas
```

### 🔍 Rodyklių semantikos analizė

| Tipas | Sintaksė | Atminties vieta | Polimorfizmas | Naudojimas |
|-------|----------|-----------------|---------------|------------|
| **Objektų masyvas** | `Student arr[3]` | Stekas | ❌ Object slicing | Vienodo tipo objektai |
| **Rodyklė į masyvą** | `Student (*ptr)[3]` | Stekas | ❌ Object slicing | Retai naudojama |
| **Rodyklių masyvas** | `Student* arr[3]` | Stekas/Heap | ✅ Veikia | Polimorfizmas |
| **Dinaminis rodyklių masyvas** | `Student** arr` | Heap | ✅ Veikia | Dinaminis polimorfizmas |

### 💡 Mokymosi tikslai

- Atskirti rodyklę į masyvą nuo rodyklių masyvo
- Suprasti object slicing problemą
- Matyti polimorfizmo poreikį rodyklių masyvams

---

## 6 etapas: STL std::array

### Koncepcija

C++11 įvedė `std::array` - saugų C masyvų pakaitalą su STL funkcionalumu.

### Kodas ir analizė

```cpp
// student_6.cpp - std::array
#include <iostream>
#include <string>
#include <array>
#include <algorithm>

class Student {
private:
    std::string name;
    int age;
    double grade;
    
public:
    Student() : name("Unknown"), age(0), grade(0.0) {
        std::cout << "📚 Default konstruktorius: " << name << std::endl;
    }
    
    Student(const std::string& n, int a, double g) 
        : name(n), age(a), grade(g) {
        std::cout << "📚 Parametrinis konstruktorius: " << name << std::endl;
    }
    
    ~Student() {
        std::cout << "🗑️ Destruktorius: " << name << std::endl;
    }
    
    void print() const {
        std::cout << "Student: " << name << ", Age: " << age 
                  << ", Grade: " << grade << std::endl;
    }
    
    double get_grade() const { return grade; }
    const std::string& get_name() const { return name; }
    
    // Operatoriai palyginimui
    bool operator<(const Student& other) const {
        return grade < other.grade;
    }
    
    bool operator>(const Student& other) const {
        return grade > other.grade;
    }
};

void demonstrate_std_array() {
    std::cout << "\n=== std::array demonstracija ===\n";
    
    // ✅ std::array su inicializacijos sąrašu
    std::array<Student, 4> students = {{
        Student("Jonas", 20, 8.5),
        Student("Petras", 21, 9.0),
        Student("Marija", 19, 8.8),
        Student("Tomas", 22, 7.5)
    }};
    
    std::cout << "\n--- Pradinis masyvas ---\n";
    for (const auto& student : students) {  // Range-based for loop
        student.print();
    }
    
    // STL algoritmai
    std::cout << "\n--- Rūšiavimas pagal pažymį ---\n";
    std::sort(students.begin(), students.end());  // Rūšiuoja pagal operator<
    
    for (size_t i = 0; i < students.size(); i++) {
        std::cout << i + 1 << ". ";
        students[i].print();
    }
    
    // Paieška
    std::cout << "\n--- Paieška ---\n";
    auto it = std::find_if(students.begin(), students.end(), 
        [](const Student& s) { return s.get_grade() > 8.7; });
    
    if (it != students.end()) {
        std::cout << "Rastas studentas su pažymiu > 8.7: ";
        it->print();
    }
    
    // Saugus prieigos metodas
    std::cout << "\n--- Saugi prieiga ---\n";
    try {
        std::cout << "students.at(2): ";
        students.at(2).print();
        
        // std::cout << "students.at(10): ";
        // students.at(10).print();  // Mestų std::out_of_range
    } catch (const std::out_of_range& e) {
        std::cout << "Klaida: " << e.what() << std::endl;
    }
    
    // Array informacija
    std::cout << "\n--- Array informacija ---\n";
    std::cout << "Dydis: " << students.size() << std::endl;
    std::cout << "Maksimalus dydis: " << students.max_size() << std::endl;
    std::cout << "Tuščias: " << (students.empty() ? "Taip" : "Ne") << std::endl;
    std::cout << "Duomenų rodyklė: " << students.data() << std::endl;
}

// Funkcija, kuri priima std::array
void process_students(const std::array<Student, 4>& students) {
    std::cout << "\n--- Funkcijoje process_students ---\n";
    std::cout << "Gauto masyvo dydis: " << students.size() << std::endl;
    
    double total_grade = 0.0;
    for (const auto& student : students) {
        total_grade += student.get_grade();
    }
    
    std::cout << "Vidutinis pažymys: " << total_grade / students.size() << std::endl;
}

// Template funkcija bet kokio dydžio array
template<size_t N>
void print_array_info(const std::array<Student, N>& arr) {
    std::cout << "\n--- Template funkcija (dydis: " << N << ") ---\n";
    std::cout << "Array dydis: " << arr.size() << std::endl;
    std::cout << "Pirmasis studentas: ";
    if (!arr.empty()) {
        arr.front().print();
    }
    std::cout << "Paskutinis studentas: ";
    if (!arr.empty()) {
        arr.back().print();
    }
}

int main() {
    std::cout << "=== STL std::array ===\n";
    
    demonstrate_std_array();
    
    // Funkcijos iškvietimas
    std::array<Student, 4> test_students = {{
        Student("A", 20, 8.0),
        Student("B", 21, 9.0),
        Student("C", 19, 7.0),
        Student("D", 22, 8.5)
    }};
    
    process_students(test_students);
    
    // Template funkcijos testas
    std::array<Student, 2> small_array = {{
        Student("X", 25, 9.5),
        Student("Y", 24, 8.9)
    }};
    
    print_array_info(test_students);  // N = 4
    print_array_info(small_array);   // N = 2
    
    std::cout << "\n=== Destruktoriai ===\n";
    return 0;
}
```

**Rezultatas:**
```
=== STL std::array ===

=== std::array demonstracija ===
📚 Parametrinis konstruktorius: Jonas
📚 Parametrinis konstruktorius: Petras
📚 Parametrinis konstruktorius: Marija
📚 Parametrinis konstruktorius: Tomas

--- Pradinis masyvas ---
Student: Jonas, Age: 20, Grade: 8.5
Student: Petras, Age: 21, Grade: 9
Student: Marija, Age: 19, Grade: 8.8
Student: Tomas, Age: 22, Grade: 7.5

--- Rūšiavimas pagal pažymį ---
1. Student: Tomas, Age: 22, Grade: 7.5
2. Student: Jonas, Age: 20, Grade: 8.5
3. Student: Marija, Age: 19, Grade: 8.8
4. Student: Petras, Age: 21, Grade: 9

--- Paieška ---
Rastas studentas su pažymiu > 8.7: Student: Marija, Age: 19, Grade: 8.8

--- Saugi prieiga ---
students.at(2): Student: Marija, Age: 19, Grade: 8.8

--- Array informacija ---
Dydis: 4
Maksimalus dydis: 4
Tuščias: Ne
Duomenų rodyklė: 0x7fff5fbff040

📚 Parametrinis konstruktorius: A
📚 Parametrinis konstruktorius: B
📚 Parametrinis konstruktorius: C
📚 Parametrinis konstruktorius: D

--- Funkcijoje process_students ---
Gauto masyvo dydis: 4
Vidutinis pažymys: 8.125

📚 Parametrinis konstruktorius: X
📚 Parametrinis konstruktorius: Y

--- Template funkcija (dydis: 4) ---
Array dydis: 4
Pirmasis studentas: Student: A, Age: 20, Grade: 8
Paskutinis studentas: Student: D, Age: 22, Grade: 8.5

--- Template funkcija (dydis: 2) ---
Array dydis: 2
Pirmasis studentas: Student: X, Age: 25, Grade: 9.5
Paskutinis studentas: Student: Y, Age: 24, Grade: 8.9

=== Destruktoriai ===
[Destruktorių seka...]
```

### 🔍 std::array privalumai

| Funkcija | C masyvas | std::array |
|----------|-----------|------------|
| **Dydžio žinojimas** | `sizeof(arr)/sizeof(arr[0])` | `arr.size()` |
| **Saugi prieiga** | ❌ Nėra | ✅ `at()` metodas |
| **STL algoritmai** | ❌ Reikia rodyklių | ✅ `begin()/end()` |
| **Range-based for** | ❌ Neveikia | ✅ Veikia |
| **Funkcijų parametrai** | Virsta rodykle | Išlaiko tipą |
| **Template palaikymas** | ❌ Sudėtinga | ✅ Natūralus |

### 💡 Mokymosi tikslai

- Naudoti std::array vietoj C masyvų
- Taikyti STL algoritmus
- Suprasti template funkcijų privalumus

---

## 7 etapas: STL std::vector

### Koncepcija

`std::vector` - dinaminis masyvas su automatišku dydžio valdymu ir RAII principais.

### Kodas ir analizė

```cpp
// student_7.cpp - std::vector
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>

class Student {
private:
    std::string name;
    int age;
    double grade;
    
public:
    Student() : name("Unknown"), age(0), grade(0.0) {
        std::cout << "📚 Default konstruktorius: " << name << std::endl;
    }
    
    Student(const std::string& n, int a, double g) 
        : name(n), age(a), grade(g) {
        std::cout << "📚 Parametrinis konstruktorius: " << name << std::endl;
    }
    
    // Copy konstruktorius
    Student(const Student& other) 
        : name(other.name), age(other.age), grade(other.grade) {
        std::cout << "📋 Copy konstruktorius: " << name << std::endl;
    }
    
    // Move konstruktorius (C++11)
    Student(Student&& other) noexcept
        : name(std::move(other.name)), age(other.age), grade(other.grade) {
        std::cout << "🚚 Move konstruktorius: " << name << std::endl;
        other.name = "Moved";
        other.age = 0;
        other.grade = 0.0;
    }
    
    ~Student() {
        std::cout << "🗑️ Destruktorius: " << name << std::endl;
    }
    
    void print() const {
        std::cout << "Student: " << name << ", Age: " << age 
                  << ", Grade: " << grade << std::endl;
    }
    
    double get_grade() const { return grade; }
    const std::string& get_name() const { return name; }
    
    bool operator<(const Student& other) const {
        return grade < other.grade;
    }
};

void demonstrate_vector_basics() {
    std::cout << "\n=== Vector pagrindai ===\n";
    
    // Tuščias vector
    std::vector<Student> students;
    std::cout << "Pradinis dydis: " << students.size() << std::endl;
    std::cout << "Pradinis capacity: " << students.capacity() << std::endl;
    
    // Pridėjimas su emplace_back (C++11)
    std::cout << "\n--- emplace_back ---\n";
    students.emplace_back("Jonas", 20, 8.5);    // Konstruojama vietoje
    students.emplace_back("Petras", 21, 9.0);
    students.emplace_back("Marija", 19, 8.8);
    
    std::cout << "Po pridėjimo - dydis: " << students.size() 
              << ", capacity: " << students.capacity() << std::endl;
    
    // Pridėjimas su push_back
    std::cout << "\n--- push_back ---\n";
    Student temp_student("Tomas", 22, 7.5);
    students.push_back(temp_student);  // Copy
    students.push_back(Student("Ona", 20, 9.2));  // Move
    
    std::cout << "Po push_back - dydis: " << students.size() 
              << ", capacity: " << students.capacity() << std::endl;
    
    // Spausdinimas
    std::cout << "\n--- Visi studentai ---\n";
    for (size_t i = 0; i < students.size(); i++) {
        std::cout << i + 1 << ". ";
        students[i].print();
    }
}

void demonstrate_vector_operations() {
    std::cout << "\n=== Vector operacijos ===\n";
    
    // Inicializacija su dydžiu
    std::vector<Student> students(3);  // 3 default objektai
    std::cout << "Vector su 3 default objektais sukurtas\n";
    
    // Užpildymas duomenimis
    students[0] = Student("A", 20, 8.0);  // Assignment
    students[1] = Student("B", 21, 9.0);
    students[2] = Student("C", 19, 7.0);
    
    std::cout << "\n--- Po assignment ---\n";
    for (const auto& student : students) {
        student.print();
    }
    
    // Įterpimas
    std::cout << "\n--- Insert operacija ---\n";
    auto it = students.begin() + 1;  // Antra pozicija
    students.insert(it, Student("Inserted", 23, 8.7));
    
    std::cout << "Po insert:\n";
    for (size_t i = 0; i < students.size(); i++) {
        std::cout << i << ". ";
        students[i].print();
    }
    
    // Šalinimas
    std::cout << "\n--- Erase operacija ---\n";
    students.erase(students.begin() + 2);  // Šaliname trečią elementą
    
    std::cout << "Po erase:\n";
    for (const auto& student : students) {
        student.print();
    }
    
    // Dydžio keitimas
    std::cout << "\n--- Resize operacija ---\n";
    std::cout << "Prieš resize: " << students.size() << std::endl;
    students.resize(6);  // Pridės 3 default objektus
    std::cout << "Po resize(6): " << students.size() << std::endl;
    
    students.resize(2);  // Pašalins 4 objektus
    std::cout << "Po resize(2): " << students.size() << std::endl;
}

void demonstrate_vector_memory() {
    std::cout << "\n=== Vector atminties valdymas ===\n";
    
    std::vector<Student> students;
    students.reserve(10);  // Rezervuojame vietą 10 objektų
    
    std::cout << "Po reserve(10) - size: " << students.size() 
              << ", capacity: " << students.capacity() << std::endl;
    
    // Stebime capacity pokyčius
    for (int i = 0; i < 15; i++) {
        size_t old_capacity = students.capacity();
        students.emplace_back("Student" + std::to_string(i), 20 + i, 7.0 + i * 0.1);
        
        if (students.capacity() != old_capacity) {
            std::cout << "Capacity pakito: " << old_capacity 
                      << " -> " << students.capacity() 
                      << " (size: " << students.size() << ")\n";
        }
    }
    
    // Atminties optimizacija
    std::cout << "\n--- Atminties optimizacija ---\n";
    std::cout << "Prieš shrink_to_fit - capacity: " << students.capacity() << std::endl;
    students.shrink_to_fit();
    std::cout << "Po shrink_to_fit - capacity: " << students.capacity() << std::endl;
}

// Vector su polimorfizmu
void demonstrate_polymorphic_vector() {
    std::cout << "\n=== Polimorfinis vector ===\n";
    
    // Vector su smart pointers polimorfizmui
    std::vector<std::unique_ptr<Student>> polymorphic_students;
    
    polymorphic_students.push_back(std::make_unique<Student>("Jonas", 20, 8.5));
    polymorphic_students.push_back(std::make_unique<Student>("Petras", 21, 9.0));
    
    std::cout << "Polimorfinis vector su smart pointers:\n";
    for (const auto& student_ptr : polymorphic_students) {
        student_ptr->print();
    }
    
    // Automatinis cleanup su unique_ptr
    std::cout << "Smart pointers automatiškai išvalys atmintį\n";
}

int main() {
    std::cout << "=== STL std::vector ===\n";
    
    demonstrate_vector_basics();
    demonstrate_vector_operations();
    demonstrate_vector_memory();
    demonstrate_polymorphic_vector();
    
    std::cout << "\n=== Destruktoriai ===\n";
    return 0;
}
```

**Rezultatas (sutrumpinta):**
```
=== STL std::vector ===

=== Vector pagrindai ===
Pradinis dydis: 0
Pradinis capacity: 0

--- emplace_back ---
📚 Parametrinis konstruktorius: Jonas
📚 Parametrinis konstruktorius: Petras
📚 Parametrinis konstruktorius: Marija
Po pridėjimo - dydis: 3, capacity: 4

--- push_back ---
📚 Parametrinis konstruktorius: Tomas
📋 Copy konstruktorius: Tomas
📚 Parametrinis konstruktorius: Ona
🚚 Move konstruktorius: Ona
Po push_back - dydis: 5, capacity: 8

=== Vector atminties valdymas ===
Po reserve(10) - size: 0, capacity: 10
Capacity pakito: 10 -> 20 (size: 11)

--- Atminties optimizacija ---
Prieš shrink_to_fit - capacity: 20
Po shrink_to_fit - capacity: 15

=== Polimorfinis vector ===
📚 Parametrinis konstruktorius: Jonas
📚 Parametrinis konstruktorius: Petras
Polimorfinis vector su smart pointers:
Student: Jonas, Age: 20, Grade: 8.5
Student: Petras, Age: 21, Grade: 9
Smart pointers automatiškai išvalys atmintį
🗑️ Destruktorius: Petras
🗑️ Destruktorius: Jonas
```

### 🔍 std::vector privalumai

| Funkcija | Dinaminis masyvas (new[]) | std::vector |
|----------|---------------------------|-------------|
| **Atminties valdymas** | Rankinis new[]/delete[] | Automatinis RAII |
| **Dydžio keitimas** | Reikia perkurti | `resize()`, `push_back()` |
| **Saugi prieiga** | ❌ Nėra | ✅ `at()` metodas |
| **STL algoritmai** | ❌ Reikia rodyklių | ✅ Pilnas palaikymas |
| **Exception safety** | ❌ Memory leaks | ✅ RAII apsauga |
| **Performance** | Greičiausias | Beveik toks pat |

### 💡 Mokymosi tikslai

- Naudoti std::vector vietoj dinaminių masyvų
- Suprasti capacity vs size skirtumus
- Taikyti smart pointers polimorfizmui

---

## 8 etapas: Smart pointers su objektų masyvais

### Koncepcija

Modern C++ (C++11+) rekomenduoja naudoti smart pointers vietoj raw pointers, ypač objektų masyvams su polimorfizmu.

### Kodas ir analizė

```cpp
// student_8.cpp - Smart pointers
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <array>

class Student {
protected:
    std::string name;
    int age;
    double grade;
    
public:
    Student(const std::string& n, int a, double g) 
        : name(n), age(a), grade(g) {
        std::cout << "📚 Student konstruktorius: " << name << std::endl;
    }
    
    virtual ~Student() {
        std::cout << "🗑️ Student destruktorius: " << name << std::endl;
    }
    
    virtual void print() const {
        std::cout << "Student: " << name << ", Age: " << age 
                  << ", Grade: " << grade << std::endl;
    }
    
    virtual std::string get_type() const { return "Student"; }
    double get_grade() const { return grade; }
    const std::string& get_name() const { return name; }
};

class GraduateStudent : public Student {
private:
    std::string thesis_topic;
    
public:
    GraduateStudent(const std::string& n, int a, double g, const std::string& topic) 
        : Student(n, a, g), thesis_topic(topic) {
        std::cout << "🎓 GraduateStudent konstruktorius: " << name << std::endl;
    }
    
    ~GraduateStudent() override {
        std::cout << "🗑️ GraduateStudent destruktorius: " << name << std::endl;
    }
    
    void print() const override {
        std::cout << "Graduate Student: " << name << ", Age: " << age 
                  << ", Grade: " << grade << ", Thesis: " << thesis_topic << std::endl;
    }
    
    std::string get_type() const override { return "GraduateStudent"; }
};

class StudentManager {
private:
    std::vector<std::unique_ptr<Student>> students;
    
public:
    StudentManager() {
        std::cout << "🏗️ StudentManager konstruktorius\n";
    }
    
    ~StudentManager() {
        std::cout << "🗑️ StudentManager destruktorius\n";
        // unique_ptr automatiškai išvalo objektus
    }
    
    // Move-only semantics (unique_ptr negalima kopijuoti)
    StudentManager(const StudentManager&) = delete;
    StudentManager& operator=(const StudentManager&) = delete;
    
    // Move konstruktorius ir assignment
    StudentManager(StudentManager&&) = default;
    StudentManager& operator=(StudentManager&&) = default;
    
    void add_student(std::unique_ptr<Student> student) {
        students.push_back(std::move(student));
    }
    
    template<typename StudentType, typename... Args>
    void emplace_student(Args&&... args) {
        students.push_back(std::make_unique<StudentType>(std::forward<Args>(args)...));
    }
    
    void print_all() const {
        std::cout << "\n--- StudentManager (" << students.size() << " studentų) ---\n";
        for (const auto& student : students) {
            std::cout << "Tipas: " << student->get_type() << " - ";
            student->print();
        }
    }
    
    void remove_student(size_t index) {
        if (index < students.size()) {
            std::cout << "Šalinamas studentas: " << students[index]->get_name() << std::endl;
            students.erase(students.begin() + index);
        }
    }
    
    size_t size() const { return students.size(); }
};

void demonstrate_unique_ptr() {
    std::cout << "\n=== unique_ptr demonstracija ===\n";
    
    // Sukuriame unique_ptr objektus
    auto student1 = std::make_unique<Student>("Jonas", 20, 8.5);
    auto grad_student = std::make_unique<GraduateStudent>("Petras", 25, 9.0, "AI Research");
    
    std::cout << "\n--- Objektai sukurti ---\n";
    student1->print();
    grad_student->print();
    
    // Perduodame ownership į vector
    std::vector<std::unique_ptr<Student>> students;
    students.push_back(std::move(student1));  // student1 dabar nullptr
    students.push_back(std::move(grad_student));
    
    std::cout << "\n--- Po move į vector ---\n";
    std::cout << "student1 yra nullptr: " << (student1 == nullptr ? "Taip" : "Ne") << std::endl;
    
    for (const auto& student : students) {
        student->print();
    }
    
    // Automatinis cleanup
    std::cout << "\n--- Vector sunaikinamas ---\n";
}

void demonstrate_shared_ptr() {
    std::cout << "\n=== shared_ptr demonstracija ===\n";
    
    // Sukuriame shared_ptr objektus
    auto student1 = std::make_shared<Student>("Marija", 19, 8.8);
    auto student2 = std::make_shared<GraduateStudent>("Tomas", 24, 9.2, "Machine Learning");
    
    std::cout << "student1 use_count: " << student1.use_count() << std::endl;
    std::cout << "student2 use_count: " << student2.use_count() << std::endl;
    
    // Dalijamės ownership
    {
        std::vector<std::shared_ptr<Student>> group1;
        std::vector<std::shared_ptr<Student>> group2;
        
        group1.push_back(student1);
        group1.push_back(student2);
        
        group2.push_back(student1);  // Tas pats objektas dviejuose vector'iuose
        
        std::cout << "\nPo pridėjimo į vector'ius:\n";
        std::cout << "student1 use_count: " << student1.use_count() << std::endl;  // 2
        std::cout << "student2 use_count: " << student2.use_count() << std::endl;  // 1
        
        std::cout << "\n--- group1 ---\n";
        for (const auto& student : group1) {
            student->print();
        }
        
        std::cout << "\n--- group2 ---\n";
        for (const auto& student : group2) {
            student->print();
        }
        
        std::cout << "\n--- Vector'iai sunaikinami ---\n";
    }
    
    std::cout << "\nPo vector'ių sunaikinimo:\n";
    std::cout << "student1 use_count: " << student1.use_count() << std::endl;  // 1
    std::cout << "student2 use_count: " << student2.use_count() << std::endl;  // 1
}

void demonstrate_student_manager() {
    std::cout << "\n=== StudentManager su smart pointers ===\n";
    
    StudentManager manager;
    
    // Pridėjimas su make_unique
    manager.add_student(std::make_unique<Student>("A", 20, 8.0));
    manager.add_student(std::make_unique<GraduateStudent>("B", 25, 9.0, "Data Science"));
    
    // Pridėjimas su emplace
    manager.emplace_student<Student>("C", 21, 7.5);
    manager.emplace_student<GraduateStudent>("D", 26, 8.8, "Robotics");
    
    manager.print_all();
    
    // Šalinimas
    std::cout << "\n--- Šalinamas studentas ---\n";
    manager.remove_student(1);  // Šaliname "B"
    
    manager.print_all();
    
    // Move semantics testas
    std::cout << "\n--- Move semantics ---\n";
    StudentManager manager2 = std::move(manager);  // Move constructor
    
    std::cout << "Originalus manager dydis: " << manager.size() << std::endl;  // 0
    std::cout << "Naujas manager2 dydis: " << manager2.size() << std::endl;    // 3
    
    manager2.print_all();
}

int main() {
    std::cout << "=== Smart pointers su objektų masyvais ===\n";
    
    demonstrate_unique_ptr();
    demonstrate_shared_ptr();
    demonstrate_student_manager();
    
    std::cout << "\n=== Destruktoriai ===\n";
    return 0;
}
```

**Rezultatas (sutrumpinta):**
```
=== Smart pointers su objektų masyvais ===

=== unique_ptr demonstracija ===
📚 Student konstruktorius: Jonas
📚 Student konstruktorius: Petras
🎓 GraduateStudent konstruktorius: Petras

--- Objektai sukurti ---
Student: Jonas, Age: 20, Grade: 8.5
Graduate Student: Petras, Age: 25, Grade: 9, Thesis: AI Research

--- Po move į vector ---
student1 yra nullptr: Taip
Student: Jonas, Age: 20, Grade: 8.5
Graduate Student: Petras, Age: 25, Grade: 9, Thesis: AI Research

--- Vector sunaikinamas ---
🗑️ GraduateStudent destruktorius: Petras
🗑️ Student destruktorius: Petras
🗑️ Student destruktorius: Jonas

=== shared_ptr demonstracija ===
📚 Student konstruktorius: Marija
📚 Student konstruktorius: Tomas
🎓 GraduateStudent konstruktorius: Tomas
student1 use_count: 1
student2 use_count: 1

Po pridėjimo į vector'ius:
student1 use_count: 2
student2 use_count: 1

Po vector'ių sunaikinimo:
student1 use_count: 1
student2 use_count: 1

=== StudentManager su smart pointers ===
🏗️ StudentManager konstruktorius
📚 Student konstruktorius: A
📚 Student konstruktorius: B
🎓 GraduateStudent konstruktorius: B
📚 Student konstruktorius: C
📚 Student konstruktorius: D
🎓 GraduateStudent konstruktorius: D

--- StudentManager (4 studentų) ---
Tipas: Student - Student: A, Age: 20, Grade: 8
Tipas: GraduateStudent - Graduate Student: B, Age: 25, Grade: 9, Thesis: Data Science
Tipas: Student - Student: C, Age: 21, Grade: 7.5
Tipas: GraduateStudent - Graduate Student: D, Age: 26, Grade: 8.8, Thesis: Robotics

--- Šalinamas studentas ---
Šalinamas studentas: B
🗑️ GraduateStudent destruktorius: B
🗑️ Student destruktorius: B

--- Move semantics ---
Originalus manager dydis: 0
Naujas manager2 dydis: 3
```

### 🔍 Smart pointers palyginimas

| Tipas | Ownership | Kopijavimas | Naudojimas |
|-------|-----------|-------------|------------|
| **unique_ptr** | Vienasmenė | ❌ Tik move | Objektų masyvai, RAII |
| **shared_ptr** | Bendras | ✅ Reference counting | Dalijamasi objektais |
| **weak_ptr** | Nestiprus | ✅ Nepadidina count | Ciklų vengimas |

### 💡 Mokymosi tikslai

- Naudoti smart pointers vietoj raw pointers
- Suprasti unique_ptr vs shared_ptr skirtumus
- Taikyti move semantics objektų masyvams

---

## Išvados ir rekomendacijos

### Evoliucijos santrauka

| Etapas | Metodas | Privalumai | Trūkumai | Kada naudoti |
|--------|---------|------------|----------|--------------|
| **1. C masyvai** | `Student arr[3]` | Paprastas | Fiksuotas dydis, tik default konstruktorius | Mokymosi tikslais |
| **2. Inicializacijos sąrašas** | `Student arr[] = {...}` | Parametriniai konstruktoriai | Fiksuotas dydis | Žinomas dydis compile time |
| **3. Dinaminiai masyvai** | `new Student[n]` | Dinaminis dydis | Manual memory management | Legacy kodas |
| **4. Rule of Three** | Su copy/assignment | Saugus kopijavimas | Sudėtinga implementacija | Kai reikia kopijuoti |
| **5. Rodyklių masyvai** | `Student* arr[]` | Polimorfizmas | Manual cleanup | Polimorfizmas be STL |
| **6. std::array** | `std::array<Student, N>` | STL funkcionalumas, saugumas | Fiksuotas dydis | Žinomas dydis, STL algoritmai |
| **7. std::vector** | `std::vector<Student>` | Dinaminis, RAII, STL | Šiek tiek overhead | Dažniausiai naudojamas |
| **8. Smart pointers** | `vector<unique_ptr<Student>>` | Polimorfizmas, RAII | Sudėtingesnė sintaksė | Modern C++ polimorfizmas |

### Praktinės rekomendacijos

#### Kada naudoti kurį metodą:

1. **std::vector<Student>** - dažniausiai naudojamas pasirinkimas
   - Vienodo tipo objektai
   - Dinaminis dydis
   - STL algoritmai

2. **std::vector<std::unique_ptr<Student>>** - polimorfizmui
   - Skirtingų tipų objektai
   - Virtualūs metodai
   - Modern C++ stilius

3. **std::array<Student, N>** - fiksuotam dydžiui
   - Žinomas dydis compile time
   - Maksimalus performance
   - STL funkcionalumas

4. **C masyvai** - vengti, išskyrus:
   - Legacy kodas
   - Embedded systems
   - Mokymosi tikslais

### Dažniausios klaidos ir jų vengimas

#### 1. Object Slicing
```cpp
// ❌ Blogai
Student arr[3] = {
    Student("A", 20, 8.0),
    GraduateStudent("B", 25, 9.0, "AI"),  // Object slicing!
    Student("C", 19, 7.5)
};

// ✅ Gerai
std::vector<std::unique_ptr<Student>> students;
students.push_back(std::make_unique<Student>("A", 20, 8.0));
students.push_back(std::make_unique<GraduateStudent>("B", 25, 9.0, "AI"));
```

#### 2. Memory Leaks
```cpp
// ❌ Blogai
Student** students = new Student*[3];
students[0] = new Student("A", 20, 8.0);
// Pamirštas delete[] ir delete

// ✅ Gerai
std::vector<std::unique_ptr<Student>> students;
students.push_back(std::make_unique<Student>("A", 20, 8.0));
// Automatinis cleanup
```

#### 3. Shallow Copy
```cpp
// ❌ Blogai - be Rule of Three
class StudentManager {
    Student* students;
    int count;
    // Trūksta copy constructor ir assignment operator
};

// ✅ Gerai - su std::vector
class StudentManager {
    std::vector<Student> students;  // Automatinis deep copy
};
```

### Mokymosi kelias

1. **Pradėkite nuo C masyvų** - suprasite problemas
2. **Pereikite prie std::array** - saugumas + STL
3. **Išmokite std::vector** - dažniausiai naudojamas
4. **Pridėkite smart pointers** - polimorfizmui
5. **Praktikuokite su realiais projektais** - įtvirtinsite žinias

**Pagrindinė žinutė**: Modern C++ suteikia galingus įrankius objektų masyvų valdymui. Naudokite STL konteinerius ir smart pointers - jie sprendžia daugumą problemų automatiškai ir saugiai.
