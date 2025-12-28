---
title: "Praktiniai encapsulation mokymo pavyzdžiai: Nuo globalių kintamųjų prie private/public"
author: "Programavimo metodikos specialistas"
date: "2025-12-27"
keywords: "C++, encapsulation, globalūs kintamieji, private, public, mokymo metodika"
---

# Praktiniai encapsulation mokymo pavyzdžiai: Nuo globalių kintamųjų prie private/public

## Įvadas

Studentai dažnai klausia: "Kodėl reikia slėpti duomenis? C veikia puikiai su globaliais kintamaisiais!" Šis dokumentas pateikia dramatiškus, praktinių situacijų pavyzdžius, kurie atskleidžia globalių kintamųjų problemas ir motyvuoja encapsulation poreikį.

---

## 1. "Bank Account Disaster" - Klasės demonstracija

### Situacija: Banko sąskaitos valdymas

**Pradžia:** Paprastas C kodas su globaliais kintamaisiais

```c
// bank_account_global.c - "Veikiantis" C kodas
#include <stdio.h>

// Globalūs kintamieji - "paprasta ir aiški"
double account_balance = 1000.0;
char account_owner[50] = "Jonas Jonaitis";
int account_number = 12345;

void deposit(double amount) {
    account_balance += amount;
    printf("Įnešta: %.2f. Balansas: %.2f\n", amount, account_balance);
}

void withdraw(double amount) {
    if (account_balance >= amount) {
        account_balance -= amount;
        printf("Išimta: %.2f. Balansas: %.2f\n", amount, account_balance);
    } else {
        printf("Nepakanka lėšų!\n");
    }
}

void print_balance() {
    printf("Sąskaita %d (%s): %.2f EUR\n", 
           account_number, account_owner, account_balance);
}

int main() {
    print_balance();
    deposit(500.0);
    withdraw(200.0);
    print_balance();
    return 0;
}
```

**Studentų reakcija:** "Veikia puikiai! Kodėl reikia komplikuoti?"

### Demonstracija 1: "Hacker Attack" scenarijai

```c
// bank_account_hacked.c - Kas nutiks realybėje
#include <stdio.h>

// Tie patys globalūs kintamieji
extern double account_balance;
extern char account_owner[50];
extern int account_number;

// Funkcijos iš bank_account_global.c
void deposit(double amount);
void withdraw(double amount);
void print_balance();

// "Nekaltas" kodas, kuris naudoja banko sistemą
void process_transaction() {
    printf("=== Apdorojama transakcija ===\n");
    
    // Kažkas "netyčia" pakeičia duomenis
    account_balance = 999999.99;  // 💥 KATASTROFA!
    strcpy(account_owner, "Hacker McHackface");
    account_number = 66666;
    
    printf("Transakcija baigta sėkmingai!\n");
}

// Dar blogiau - "tyčinis" kodas
void malicious_code() {
    printf("=== Paleidžiama 'saugi' ataskaita ===\n");
    
    // Atakuojantis kodas gali daryti bet ką
    account_balance = 0.0;        // Ištuština sąskaitą
    account_number = -1;          // Sugadina duomenis
    
    // Dar blogiau - buffer overflow
    strcpy(account_owner, "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
    
    printf("Ataskaita sugeneruota.\n");
}

int main() {
    printf("=== PRADŽIA ===\n");
    print_balance();
    
    printf("\n=== PO 'NORMALIOS' TRANSAKCIJOS ===\n");
    process_transaction();
    print_balance();
    
    printf("\n=== PO 'SAUGIOS' ATASKAITOS ===\n");
    malicious_code();
    print_balance();  // 💥 Segmentation fault galimas!
    
    return 0;
}
```

**Rezultatas:**
```
=== PRADŽIA ===
Sąskaita 12345 (Jonas Jonaitis): 1000.00 EUR

=== PO 'NORMALIOS' TRANSAKCIJOS ===
=== Apdorojama transakcija ===
Transakcija baigta sėkmingai!
Sąskaita 66666 (Hacker McHackface): 999999.99 EUR

=== PO 'SAUGIOS' ATASKAITOS ===
=== Paleidžiama 'saugi' ataskaita ===
Ataskaita sugeneruota.
Segmentation fault (core dumped)
```

### Demonstracija 2: "Multiple Accounts Chaos"

```c
// multiple_accounts_chaos.c
#include <stdio.h>

// Globalūs kintamieji - tik viena sąskaita!
double account_balance = 1000.0;
char account_owner[50] = "Jonas";
int account_number = 12345;

void create_account(const char* owner, int number, double initial) {
    // "Sukuriame" naują sąskaitą
    strcpy(account_owner, owner);
    account_number = number;
    account_balance = initial;
    printf("Sukurta sąskaita: %d (%s) su %.2f EUR\n", 
           number, owner, initial);
}

void transfer_money(int from_account, int to_account, double amount) {
    printf("Pervedama %.2f iš %d į %d\n", amount, from_account, to_account);
    
    // Problema: kaip rasti "from_account"?
    // Turime tik vieną globalų account_balance!
    
    if (account_number == from_account) {
        if (account_balance >= amount) {
            account_balance -= amount;
            printf("Išimta iš %d: %.2f\n", from_account, amount);
            
            // Kaip pridėti į to_account?
            // Negalime - neturime kitos sąskaitos duomenų!
            printf("KLAIDA: Negalima rasti sąskaitos %d!\n", to_account);
        }
    } else {
        printf("KLAIDA: Sąskaita %d nerasta!\n", from_account);
    }
}

int main() {
    // Bandome sukurti kelias sąskaitas
    create_account("Jonas", 12345, 1000.0);
    create_account("Petras", 67890, 2000.0);  // Perrašo Jonas duomenis!
    create_account("Marija", 11111, 500.0);   // Perrašo Petras duomenis!
    
    printf("\nDabar turime tik: %d (%s) su %.2f EUR\n", 
           account_number, account_owner, account_balance);
    
    // Bandome pervesti pinigus
    transfer_money(12345, 67890, 100.0);  // Neveiks!
    
    return 0;
}
```

**Rezultatas:**
```
Sukurta sąskaita: 12345 (Jonas) su 1000.00 EUR
Sukurta sąskaita: 67890 (Petras) su 2000.00 EUR
Sukurta sąskaita: 11111 (Marija) su 500.00 EUR

Dabar turime tik: 11111 (Marija) su 500.00 EUR
Pervedama 100.00 iš 12345 į 67890
KLAIDA: Sąskaita 12345 nerasta!
```

### C++ sprendimas su encapsulation

```cpp
// bank_account_safe.cpp
#include <iostream>
#include <string>
#include <vector>

class BankAccount {
private:  // 🔒 PASLĖPTA - niekas negali tiesiogiai keisti!
    double balance;
    std::string owner;
    int account_number;
    
public:   // 🌐 KONTROLIUOJAMA PRIEIGA
    BankAccount(const std::string& owner_name, int number, double initial_balance) 
        : owner(owner_name), account_number(number), balance(initial_balance) {
        std::cout << "✅ Sukurta sąskaita: " << number << " (" << owner << ")\n";
    }
    
    // Kontroliuojami metodai
    bool deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            std::cout << "✅ Įnešta: " << amount << " EUR\n";
            return true;
        }
        std::cout << "❌ Neigiama suma!\n";
        return false;
    }
    
    bool withdraw(double amount) {
        if (amount > 0 && balance >= amount) {
            balance -= amount;
            std::cout << "✅ Išimta: " << amount << " EUR\n";
            return true;
        }
        std::cout << "❌ Nepakanka lėšų arba neigiama suma!\n";
        return false;
    }
    
    // Saugi informacijos prieiga
    double get_balance() const { return balance; }
    std::string get_owner() const { return owner; }
    int get_account_number() const { return account_number; }
    
    void print_info() const {
        std::cout << "Sąskaita " << account_number << " (" << owner 
                  << "): " << balance << " EUR\n";
    }
};

// Dabar galime turėti kelias sąskaitas!
class Bank {
private:
    std::vector<BankAccount> accounts;
    
public:
    void add_account(const std::string& owner, int number, double initial) {
        accounts.emplace_back(owner, number, initial);
    }
    
    BankAccount* find_account(int number) {
        for (auto& account : accounts) {
            if (account.get_account_number() == number) {
                return &account;
            }
        }
        return nullptr;
    }
    
    bool transfer(int from_number, int to_number, double amount) {
        BankAccount* from = find_account(from_number);
        BankAccount* to = find_account(to_number);
        
        if (!from || !to) {
            std::cout << "❌ Sąskaita nerasta!\n";
            return false;
        }
        
        if (from->withdraw(amount)) {
            to->deposit(amount);
            std::cout << "✅ Pervedimas sėkmingas!\n";
            return true;
        }
        
        return false;
    }
    
    void print_all_accounts() {
        std::cout << "\n=== VISOS SĄSKAITOS ===\n";
        for (const auto& account : accounts) {
            account.print_info();
        }
    }
};

// Bandymas "nulaužti" sistemą
void hacker_attack(Bank& bank) {
    std::cout << "\n=== HACKER ATTACK ===\n";
    
    // Bandymas tiesiogiai keisti duomenis
    // account.balance = 999999;  // ❌ KOMPILIATORIAUS KLAIDA!
    // account.owner = "Hacker";  // ❌ KOMPILIATORIAUS KLAIDA!
    
    std::cout << "❌ Negalima tiesiogiai keisti duomenų!\n";
    std::cout << "✅ Encapsulation apsaugoja!\n";
}

int main() {
    Bank bank;
    
    // Sukuriame kelias sąskaitas
    bank.add_account("Jonas", 12345, 1000.0);
    bank.add_account("Petras", 67890, 2000.0);
    bank.add_account("Marija", 11111, 500.0);
    
    bank.print_all_accounts();
    
    // Saugus pervedimas
    bank.transfer(67890, 12345, 300.0);
    
    bank.print_all_accounts();
    
    // Bandymas nulaužti
    hacker_attack(bank);
    
    return 0;
}
```

---

## 2. "Game Character Stats" - Interaktyvus pavyzdys

### Problema su globaliais kintamaisiais

```c
// game_character_global.c
#include <stdio.h>

// Globalūs žaidėjo statistikos duomenys
int player_health = 100;
int player_mana = 50;
int player_level = 1;
int player_experience = 0;

void cast_spell() {
    if (player_mana >= 10) {
        player_mana -= 10;
        printf("🔥 Užkeikimas paleistas! Mana: %d\n", player_mana);
    } else {
        printf("❌ Nepakanka manos!\n");
    }
}

void take_damage(int damage) {
    player_health -= damage;
    printf("💥 Gauta %d žalos! Sveikata: %d\n", damage, player_health);
    
    if (player_health <= 0) {
        printf("💀 Žaidėjas mirė!\n");
    }
}

void gain_experience(int exp) {
    player_experience += exp;
    printf("⭐ Gauta %d patirties! Iš viso: %d\n", exp, player_experience);
    
    // Level up logika
    if (player_experience >= 100 * player_level) {
        player_level++;
        player_health = 100;  // Pilna sveikata
        player_mana = 50 + player_level * 10;
        printf("🎉 LEVEL UP! Dabar %d lygis!\n", player_level);
    }
}
```

### "Cheat Engine" demonstracija

```c
// game_cheats.c - Kas nutiks su cheat kodais
#include <stdio.h>

// Prieiga prie globalių kintamųjų
extern int player_health;
extern int player_mana;
extern int player_level;
extern int player_experience;

// Funkcijos iš game_character_global.c
void cast_spell();
void take_damage(int damage);
void gain_experience(int exp);

// "Nekalti" cheat kodai
void god_mode() {
    printf("=== GOD MODE ACTIVATED ===\n");
    player_health = 999999;
    player_mana = 999999;
    printf("✨ Dabar esi nemirtingas!\n");
}

void instant_max_level() {
    printf("=== INSTANT MAX LEVEL ===\n");
    player_level = 100;
    player_experience = 999999;
    player_health = 999999;
    player_mana = 999999;
    printf("🚀 Dabar esi 100 lygio!\n");
}

// "Atsitiktiniai" bugai
void random_bug() {
    printf("=== Paleidžiama 'saugi' funkcija ===\n");
    
    // "Netyčia" sugadina duomenis
    player_health = -50;      // Neigiama sveikata!
    player_mana = 1000000;    // Per daug manos
    player_level = 0;         // Nulis lygis!
    player_experience = -999; // Neigiama patirtis
    
    printf("💥 Ups! Kažkas nutiko...\n");
}

// Dar blogiau - memory corruption
void memory_corruption() {
    printf("=== 'Optimizacijos' funkcija ===\n");
    
    // Bandymas rašyti už kintamųjų ribų
    int* ptr = &player_health;
    for (int i = 0; i < 1000; i++) {
        ptr[i] = 0xDEADBEEF;  // 💥 Rašo random atminties vietose!
    }
    
    printf("🔥 Sistema gali crashinti...\n");
}

int main() {
    printf("=== ŽAIDIMO PRADŽIA ===\n");
    printf("Sveikata: %d, Mana: %d, Lygis: %d\n", 
           player_health, player_mana, player_level);
    
    // Normalus žaidimas
    cast_spell();
    take_damage(30);
    gain_experience(50);
    
    printf("\n=== CHEAT KODAI ===\n");
    god_mode();
    printf("Sveikata: %d, Mana: %d\n", player_health, player_mana);
    
    instant_max_level();
    printf("Lygis: %d, Patirtis: %d\n", player_level, player_experience);
    
    printf("\n=== 'ATSITIKTINIS' BUGAS ===\n");
    random_bug();
    printf("Sveikata: %d, Mana: %d, Lygis: %d, Patirtis: %d\n", 
           player_health, player_mana, player_level, player_experience);
    
    // Bandymas žaisti su sugadintais duomenimis
    cast_spell();  // Su neigiama sveikata!
    take_damage(10);
    
    printf("\n=== MEMORY CORRUPTION ===\n");
    memory_corruption();  // 💥 Gali crashinti
    
    return 0;
}
```

### C++ sprendimas su encapsulation

```cpp
// game_character_safe.cpp
#include <iostream>
#include <algorithm>

class GameCharacter {
private:  // 🔒 APSAUGOTI DUOMENYS
    int health;
    int max_health;
    int mana;
    int max_mana;
    int level;
    int experience;
    
    // Privatus metodas validacijai
    void validate_stats() {
        health = std::max(0, std::min(health, max_health));
        mana = std::max(0, std::min(mana, max_mana));
        level = std::max(1, level);
        experience = std::max(0, experience);
    }
    
public:
    GameCharacter() : health(100), max_health(100), mana(50), 
                     max_mana(50), level(1), experience(0) {
        std::cout << "🎮 Sukurtas naujas žaidėjas!\n";
    }
    
    // KONTROLIUOJAMI metodai
    bool cast_spell(int mana_cost = 10) {
        if (mana >= mana_cost) {
            mana -= mana_cost;
            std::cout << "🔥 Užkeikimas paleistas! Mana: " << mana << "\n";
            return true;
        }
        std::cout << "❌ Nepakanka manos!\n";
        return false;
    }
    
    void take_damage(int damage) {
        if (damage < 0) {
            std::cout << "❌ Neigiama žala ignoruojama!\n";
            return;
        }
        
        health -= damage;
        validate_stats();  // Automatinis patikrinimas!
        
        std::cout << "💥 Gauta " << damage << " žalos! Sveikata: " 
                  << health << "/" << max_health << "\n";
        
        if (health <= 0) {
            std::cout << "💀 Žaidėjas mirė!\n";
        }
    }
    
    void gain_experience(int exp) {
        if (exp < 0) {
            std::cout << "❌ Neigiama patirtis ignoruojama!\n";
            return;
        }
        
        experience += exp;
        std::cout << "⭐ Gauta " << exp << " patirties! Iš viso: " 
                  << experience << "\n";
        
        // Level up tikrinimas
        int required_exp = 100 * level;
        if (experience >= required_exp) {
            level_up();
        }
    }
    
    void level_up() {
        level++;
        max_health += 20;
        max_mana += 10;
        health = max_health;  // Pilna sveikata
        mana = max_mana;      // Pilna mana
        
        std::cout << "🎉 LEVEL UP! Dabar " << level << " lygis!\n";
        std::cout << "💪 Sveikata: " << health << ", Mana: " << mana << "\n";
    }
    
    // SAUGI informacijos prieiga
    int get_health() const { return health; }
    int get_max_health() const { return max_health; }
    int get_mana() const { return mana; }
    int get_level() const { return level; }
    int get_experience() const { return experience; }
    
    void print_stats() const {
        std::cout << "📊 Statistikos: HP:" << health << "/" << max_health 
                  << " MP:" << mana << "/" << max_mana 
                  << " LVL:" << level << " EXP:" << experience << "\n";
    }
    
    // Saugūs "cheat" metodai (su validacija)
    void admin_heal() {
        std::cout << "🏥 Admin heal...\n";
        health = max_health;
    }
    
    void admin_restore_mana() {
        std::cout << "💙 Admin mana restore...\n";
        mana = max_mana;
    }
};

// Bandymas "nulaužti" sistemą
void hacker_attempt(GameCharacter& player) {
    std::cout << "\n=== HACKER ATTACK ATTEMPT ===\n";
    
    // Visi šie bandymai neveiks!
    // player.health = 999999;     // ❌ KOMPILIATORIAUS KLAIDA!
    // player.mana = 999999;       // ❌ KOMPILIATORIAUS KLAIDA!
    // player.level = 100;         // ❌ KOMPILIATORIAUS KLAIDA!
    // player.experience = 999999; // ❌ KOMPILIATORIAUS KLAIDA!
    
    std::cout << "❌ Visi bandymai tiesiogiai keisti duomenis nepavyko!\n";
    
    // Bandymas su neigiamomis reikšmėmis
    std::cout << "\n--- Bandymas su neigiamomis reikšmėmis ---\n";
    player.take_damage(-50);      // Ignoruojama
    player.gain_experience(-100); // Ignoruojama
    
    std::cout << "✅ Encapsulation apsaugojo nuo visų atakų!\n";
}

int main() {
    GameCharacter player;
    
    std::cout << "\n=== NORMALUS ŽAIDIMAS ===\n";
    player.print_stats();
    
    player.cast_spell();
    player.take_damage(30);
    player.gain_experience(50);
    player.print_stats();
    
    player.gain_experience(60);  // Level up!
    player.print_stats();
    
    std::cout << "\n=== ADMIN KOMANDOS (SAUGIOS) ===\n";
    player.admin_heal();
    player.admin_restore_mana();
    player.print_stats();
    
    // Bandymas nulaužti
    hacker_attempt(player);
    player.print_stats();  // Duomenys vis dar saugūs!
    
    return 0;
}
```

---

## 3. "Library Book System" - Duomenų integrumo demonstracija

### Globalių kintamųjų katastrofa

```c
// library_global.c
#include <stdio.h>
#include <string.h>

// Globalūs bibliotekos duomenys
char book_titles[100][100];
char book_authors[100][100];
int book_available[100];  // 1 = prieinama, 0 = paimta
int total_books = 0;

void add_book(const char* title, const char* author) {
    if (total_books < 100) {
        strcpy(book_titles[total_books], title);
        strcpy(book_authors[total_books], author);
        book_available[total_books] = 1;
        total_books++;
        printf("📚 Pridėta knyga: %s (%s)\n", title, author);
    }
}

void borrow_book(int book_id) {
    if (book_id >= 0 && book_id < total_books) {
        if (book_available[book_id]) {
            book_available[book_id] = 0;
            printf("📖 Paimta: %s\n", book_titles[book_id]);
        } else {
            printf("❌ Knyga jau paimta!\n");
        }
    }
}

void return_book(int book_id) {
    if (book_id >= 0 && book_id < total_books) {
        book_available[book_id] = 1;
        printf("📚 Grąžinta: %s\n", book_titles[book_id]);
    }
}

void print_books() {
    printf("\n=== BIBLIOTEKOS KNYGOS ===\n");
    for (int i = 0; i < total_books; i++) {
        printf("%d. %s (%s) - %s\n", i, book_titles[i], book_authors[i],
               book_available[i] ? "Prieinama" : "Paimta");
    }
}
```

### "Chaos" demonstracija

```c
// library_chaos.c
#include <stdio.h>
#include <string.h>

// Prieiga prie globalių duomenų
extern char book_titles[100][100];
extern char book_authors[100][100];
extern int book_available[100];
extern int total_books;

extern void add_book(const char* title, const char* author);
extern void borrow_book(int book_id);
extern void return_book(int book_id);
extern void print_books();

// "Nekaltos" funkcijos, kurios sugadina duomenis
void update_catalog() {
    printf("=== Atnaujinamas katalogas ===\n");
    
    // "Netyčia" sugadina duomenis
    strcpy(book_titles[0], "SUGADINTA KNYGA");
    strcpy(book_authors[0], "NEŽINOMAS AUTORIUS");
    book_available[0] = -1;  // Neteisinga reikšmė!
    
    // Dar blogiau
    total_books = -5;  // Neigiamas knygų skaičius!
    
    printf("Katalogas atnaujintas.\n");
}

void generate_report() {
    printf("=== Generuojama ataskaita ===\n");
    
    // "Optimizacija" - išvalo visus duomenis
    memset(book_titles, 0, sizeof(book_titles));
    memset(book_authors, 0, sizeof(book_authors));
    memset(book_available, 0, sizeof(book_available));
    total_books = 0;
    
    printf("Ataskaita sugeneruota (duomenys išvalyti).\n");
}

void malicious_attack() {
    printf("=== 'Saugi' duomenų migracija ===\n");
    
    // Tyčinis duomenų sugadinimas
    for (int i = 0; i < 100; i++) {
        strcpy(book_titles[i], "HACKED BOOK");
        strcpy(book_authors[i], "HACKER");
        book_available[i] = 999;  // Neteisinga reikšmė
    }
    total_books = 999;
    
    printf("Duomenų migracija baigta.\n");
}

int main() {
    // Sukuriame normalią biblioteką
    add_book("C++ Programming", "Bjarne Stroustrup");
    add_book("Clean Code", "Robert Martin");
    add_book("Design Patterns", "Gang of Four");
    
    print_books();
    
    // Normalus naudojimas
    borrow_book(0);
    print_books();
    
    printf("\n=== PRADEDAMOS PROBLEMOS ===\n");
    
    // "Nekaltas" katalogas atnaujinimas
    update_catalog();
    print_books();
    
    // "Saugi" ataskaita
    generate_report();
    print_books();
    
    // Bandymas atkurti duomenis
    add_book("New Book", "New Author");
    print_books();
    
    // Galutinis smūgis
    malicious_attack();
    print_books();
    
    return 0;
}
```

### C++ sprendimas su encapsulation

```cpp
// library_safe.cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class Book {
private:
    std::string title;
    std::string author;
    bool available;
    int book_id;
    
public:
    Book(const std::string& t, const std::string& a, int id) 
        : title(t), author(a), available(true), book_id(id) {}
    
    // Kontroliuojama prieiga
    std::string get_title() const { return title; }
    std::string get_author() const { return author; }
    bool is_available() const { return available; }
    int get_id() const { return book_id; }
    
    bool borrow() {
        if (available) {
            available = false;
            return true;
        }
        return false;
    }
    
    void return_book() {
        available = true;
    }
    
    void print_info() const {
        std::cout << book_id << ". " << title << " (" << author << ") - "
                  << (available ? "Prieinama" : "Paimta") << "\n";
    }
};

class Library {
private:  // 🔒 APSAUGOTI DUOMENYS
    std::vector<Book> books;
    int next_id;
    
    // Privatus metodas validacijai
    bool is_valid_id(int id) const {
        return id >= 0 && id < static_cast<int>(books.size());
    }
    
public:
    Library() : next_id(0) {
        std::cout << "📚 Sukurta nauja biblioteka!\n";
    }
    
    // KONTROLIUOJAMI metodai
    void add_book(const std::string& title, const std::string& author) {
        if (title.empty() || author.empty()) {
            std::cout << "❌ Tuščias pavadinimas arba autorius!\n";
            return;
        }
        
        books.emplace_back(title, author, next_id++);
        std::cout << "📚 Pridėta knyga: " << title << " (" << author << ")\n";
    }
    
    bool borrow_book(int book_id) {
        if (!is_valid_id(book_id)) {
            std::cout << "❌ Neteisingas knygos ID!\n";
            return false;
        }
        
        if (books[book_id].borrow()) {
            std::cout << "📖 Paimta: " << books[book_id].get_title() << "\n";
            return true;
        } else {
            std::cout << "❌ Knyga jau paimta!\n";
            return false;
        }
    }
    
    bool return_book(int book_id) {
        if (!is_valid_id(book_id)) {
            std::cout << "❌ Neteisingas knygos ID!\n";
            return false;
        }
        
        books[book_id].return_book();
        std::cout << "📚 Grąžinta: " << books[book_id].get_title() << "\n";
        return true;
    }
    
    void print_books() const {
        std::cout << "\n=== BIBLIOTEKOS KNYGOS ===\n";
        if (books.empty()) {
            std::cout << "Biblioteka tuščia.\n";
            return;
        }
        
        for (const auto& book : books) {
            book.print_info();
        }
    }
    
    // Saugūs admin metodai
    int get_total_books() const { return books.size(); }
    
    int get_available_count() const {
        return std::count_if(books.begin(), books.end(),
                           [](const Book& b) { return b.is_available(); });
    }
    
    void print_statistics() const {
        std::cout << "\n📊 Statistikos:\n";
        std::cout << "Iš viso knygų: " << get_total_books() << "\n";
        std::cout << "Prieinamų: " << get_available_count() << "\n";
        std::cout << "Paimtų: " << (get_total_books() - get_available_count()) << "\n";
    }
};

// Bandymas "nulaužti" sistemą
void hacker_attack(Library& lib) {
    std::cout << "\n=== HACKER ATTACK ATTEMPT ===\n";
    
    // Visi šie bandymai neveiks!
    // lib.books.clear();           // ❌ KOMPILIATORIAUS KLAIDA!
    // lib.next_id = -999;          // ❌ KOMPILIATORIAUS KLAIDA!
    // lib.books[0].available = false; // ❌ KOMPILIATORIAUS KLAIDA!
    
    std::cout << "❌ Tiesioginis duomenų keitimas neįmanomas!\n";
    
    // Bandymas su neteisingais parametrais
    std::cout << "\n--- Bandymas su neteisingais parametrais ---\n";
    lib.add_book("", "");           // Ignoruojama
    lib.borrow_book(-1);            // Ignoruojama
    lib.borrow_book(999);           // Ignoruojama
    lib.return_book(-5);            // Ignoruojama
    
    std::cout << "✅ Visi neteisingi parametrai atmesti!\n";
}

// "Saugi" ataskaita
void generate_safe_report(const Library& lib) {
    std::cout << "\n=== SAUGI ATASKAITA ===\n";
    
    // Galime tik skaityti duomenis
    lib.print_statistics();
    
    // Negalime keisti duomenų
    // lib.books.clear();  // ❌ KOMPILIATORIAUS KLAIDA!
    
    std::cout << "✅ Ataskaita sugeneruota be duomenų sugadinimo!\n";
}

int main() {
    Library library;
    
    std::cout << "\n=== NORMALUS NAUDOJIMAS ===\n";
    library.add_book("C++ Programming", "Bjarne Stroustrup");
    library.add_book("Clean Code", "Robert Martin");
    library.add_book("Design Patterns", "Gang of Four");
    
    library.print_books();
    library.print_statistics();
    
    // Normalus skolinimas
    library.borrow_book(0);
    library.borrow_book(1);
    library.print_books();
    library.print_statistics();
    
    // Grąžinimas
    library.return_book(0);
    library.print_books();
    
    // Bandymas nulaužti
    hacker_attack(library);
    library.print_books();  // Duomenys vis dar saugūs!
    
    // Saugi ataskaita
    generate_safe_report(library);
    library.print_books();  // Duomenys nepakito!
    
    return 0;
}
```

---

## 4. Klasės diskusijos klausimai

### Po demonstracijų užduokite studentams:

1. **"Kas nutiko su banko sąskaita?"**
   - Kodėl globalūs kintamieji leido "hacker'iui" pakeisti balansą?
   - Kaip C++ private sekcija tai apsaugojo?

2. **"Kodėl negalėjome turėti kelių banko sąskaitų su globaliais kintamaisiais?"**
   - Kas yra "state" ir kodėl svarbu jį atskirti?

3. **"Ar pastebėjote, kad C++ versijoje kompiliatorius neleidžia daryti klaidų?"**
   - Kodėl tai geriau nei runtime klaidos?

4. **"Kas geriau - pasitikėti programuotoju ar kompiliatoriumi?"**
   - Žmonės daro klaidas, kompiliatorius - ne

### Praktinės užduotys studentams:

1. **"Sukurkite savo pavyzdį"**
   - Sugalvokite situaciją, kur globalūs kintamieji sukeltų problemas
   - Parodykite, kaip encapsulation tai išspręstų

2. **"Hack challenge"**
   - Duokite studentams C kodą su globaliais kintamaisiais
   - Paprašykite "nulaužti" sistemą
   - Tada parodykite C++ versiją ir paprašykite bandyti vėl

3. **"Design challenge"**
   - Duokite problemą (pvz., "Shopping Cart")
   - Paprašykite suprojektuoti su globaliais kintamaisiais
   - Tada su C++ klasėmis
   - Palyginkite rezultatus

---

## Išvados

### Kodėl šie pavyzdžiai veikia:

1. **Dramatiškas poveikis:** Studentai mato realų "crash'ą" ir duomenų sugadinimą
2. **Praktinės situacijos:** Bankai, žaidimai, bibliotekos - visiems suprantama
3. **Aiškus kontrastas:** C problemos vs C++ sprendimai
4. **Kompiliatoriaus pagalba:** Mato, kad C++ neleidžia daryti klaidų
5. **Interaktyvumas:** Studentai gali eksperimentuoti patys

### Pagrindinė žinutė studentams:

> **"Encapsulation - tai ne apribojimas, o apsauga. Tai kaip automobilio saugos diržas - neleidžia jums susižeisti, kai kas nors eina ne taip."**

Globalūs kintamieji = vairavimas be saugos diržo
Private/public = saugos sistema, kuri apsaugo nuo klaidų

Šie pavyzdžiai formuoja gilų supratimą, kodėl encapsulation yra būtinas, ne tik teorinis principas.
