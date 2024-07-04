# C++ Quirks

## Table of contents

- Bűbűjok / Spells

  - Inicializáció
  - If utasítások
  - For ciklusok
  - Switch case
  - Tömbök
  - Disanbiguate
  - Structured bindings

- varázsigék / Intermediate Incantations
- Operátorok / alternatív tokenek
- auto
- macro define, stringify, include
- Forward declaration
- vector, pair, tuple, std::tie < op
- Mesteri Varázslat / Masterful Magic
- Nem szabványos
  - ternary (elvis)
  - tömb inicializálás
  - Compiler specifics
- Legfelsőbb Mágia / Supreme Sorcery
  - raw string + multiline
  - folds
  - vector<bool> -> string_base<bool>
  - macro hibák () és do while
  - a bunch of braces: Lambda
- Fekete mágia / Black Magic
  - UB
  - ternary
  - vessző operátor vs vessző szeparátor
  - Konstruktor - destruktor

# Szintaxis

"Egyszerűbb" szintaxisbeli elemek

## Inicializáció

```cpp
int foo() {
    int x;
    return x;
}
```

- Jó kis random szám generátor
- Valójában nem definiált viselkedés
- A fordíttó akár teljesen el is távolíthatja a változót

### Pop quiz #1

Melyik változók értéke NEM 0?

```cpp
int a;

int b = 0;
int c = {0};
int d = {};

int e();
int f{};
int g(0);
int h{0};

int (i);
int ((j));
int (((k)));

int l = false;

int main() {
    int m;
}
```

---

```cpp
int a;

int b = 0;
int c = {0};
int d = {};

int e(); // Ez egy függvény deklaráció
int f{};
int g(0);
int h{0};

int (i);
int ((j));
int (((k))); // Ez nem fordul le

int l = false;

int main() {
    int m;
}
```

## Egyértelműsítés

```cpp
int a();
int ((a));

```

```cpp
struct point {
    int x, y;
};

void do_something(point point) {
    // ...
}

point q; // Ez még helyes
pair<int, int> point;
// vagy akár point point

point p; // Nem fordul le, mert nem egyértelmű
class point p; // Egyértelműsíttés

// Minden nem alaptípusra rátehetjük
class vector<class pair<int, int>>;
```

# If / elágazások utasítás

````cpp
int a = 42, b = 1729;

if (a == b) {
  // do something
}

if (a) {
    // do something
}

if (a == b) cout << a;
```

```cpp
if (int k = 2; k==2) {
    // ...
    cout << k;
}

if(false; true) {

}

if(; true) {

}

````

### Pop quiz #2

Mi a leghasznosabb dolog amire használhatjuk ezt az inicializáoló mezőt?

---

```cpp

if (struct Foo; true) {

}


if (struct Point {int x, y;}; k < 3) {
    Point p = {k, k};
    cout << p.x << ' ' << p.y;
}
```

A `constexpr` nagyon hasznos, de versenyen nem éri meg ezzel foglalkozni.

```cpp
if constexpr (false) {

} else {

}
```

## For ciklusok

```cpp
for (int i = 0; i < 10; i++) {
    cout << i << ' ';
}
cout << '\n';
```

```cpp
for (int i = 0; i < 10; i++) {
    cout << i << " \n"[i==9];
}
```

```cpp
for (<first-once>; <boolean expr>; <after-each>) {
    // ...
}

// Tehát természetesen a <first-once> mezőben is létrehozatunk egy saját osztályt

for (;;) {

} // Végtelen ciklus
// Hivatalosan a végtelen ciklus nem definiált viselkedés
```

```cpp
#define ever (;;)

for ever {
}
```

Ranged-based for ciklus

```cpp
vector<int> v = {1, 2, 3, 4, 5};
for (int i : v) {
    cout << i << ' ';
}

for (int i : v) {
    i++;
}
```

Referenciák

```cpp
int a = 4;
int& b = a;
b++;
cout << a;


vector<int> v = {1, 2, 3, 4, 5};
for (int& i : v) {
    i++;
}


// referenciákal találkoztatokmár
v[1]; // egy referencia
v.back(); // is egy referencia
// ha vector<vector<string>> lenne, akkor O(n) helyett O(n*m) ha nincs &
```

Map konténerrel

```cpp
map<string, int> mp;
mp["hello"] = 42;

// nice O(n*m) looping because of string copy
for(pair<string, int> kv : mp) {
    cout << kv.first << " " << kv.second << '\n';
}
```

```cpp
map<string, int> mp;
mp["hello"] = 42;

// nice O(n) looping because of string copy
for(pair<string, int>& kv : mp) {
    cout << kv.first << " " << kv.second << '\n';
}
```

Valaki tudja miért nem fordul?

```cpp
map<string, int> mp;
mp["hello"] = 42;

// nice O(n) looping because of string copy
for(pair<const string, int>& kv : mp) {
    cout << kv.first << " " << kv.second << '\n';
}

for(auto& kv : mp) {
    cout << kv.first << " " << kv.second << '\n';
}

```

[Structured bindings](https://en.cppreference.com/w/cpp/language/structured_binding)

```cpp
pair<int, int> p = {1, 2}; // Ennek a hivatalos neve "Aggregate initialization"

auto [x, y] = p; // Másolás
// Mintha
int x = p.first; // Ez természetesen nem fordul le
int y = p.second;

// Tényleges áttnevezésnek
auto& [x, y] = p; // Referencia
```

```cpp
// tuple-el és saját struktúrákkal is működik
struct Point {
    int x, y;
};

auto [x, y] = Point{1, 2};
auto [x, y, z] = tuple<int, int, int>{1, 2, 3};
```

[Template argument deduction / TAD](https://en.cppreference.com/w/cpp/language/template_argument_deduction)

```cpp
auto [x, y, z] = tuple{1, 2, 3};
vector v = {1, 2, 3, 4, 5};
```

```cpp
map<string, int> mp;
mp["hello"] = 42;

for(auto&[key, value] : mp) {
    cout << key << " " << value << '\n';
}
```

---

# Switch case / Többágú elágazás

```cpp

int k = 2;
switch (k) {
    case 1:
        cout << "One";
        break;
    case 2:
        cout << "Two";
        break;
    case 3:
        cout << "Three";
        break;
}
```

Csak alap típusokkal működik, pl string nem

```cpp
int k = 2;
switch (k) {
    case 1:
        cout << "One";
        break;
    case 2:
        cout << "Two";
        break;
    case 3:
        cout << "Three";
        break;
    default:
        cout << "Default";
}
```

```cpp
int k = 2;
switch (k) {
    case 1:
        int r = 42; // Nem fordul
        cout << "One";
        break;
    case 2:
        cout << "Two";
        break;
    case 3:
        cout << "Three";
        break;
    default:
        cout << "Default";
}
```

Scoping

Valójában csak a {} bokkok.

Az első hasznos dolog:
Zárójeleket bárhova tehetunk, ahhoz hogy saját scope-ot hozzunk létre

Valójában az if és for nál is ezt csináljuk

```cpp
int k = 2;
switch (k) {
    case 1: {
        int r = 42; // így igen
        cout << "One";
    } break;
    case 2: {
        cout << "Two";
    } break;
    case 3: {
        cout << "Three";
    } break;
    default: {
        cout << "Default";
    }
}
```

#

- auto
- Operátorok / alternatív tokenek
- Forward declaration
- ternary
- macro define, stringify, include
- Structured bindings
- vector, pair, tuple, std::tie < op
- Nem szabványos
  - ternary (elvis)
  - tömb inicializálás
  - Compiler specifics
- Halandó
  - raw string + multiline
  - folds
  - vector<bool> -> string_base<bool>
  - Konstruktor - destruktor
  - macro hibák () és do while
  - a bunch of braces: Lambda
- Fekete mágia
  - UB
  - vessző operátor vs vessző szeparátor
  - Tömbök

---

# Switch lifeteme

-- range based switch

# Forward declaration

```cpp
void asdf(struct S* x);
```

# Array

-- Classified

```cpp
// designated array initializer
// This is clang specific
int arr[] = {
    [8] = 3,
    [5] = 2,
    [9] = 6
}

// In GCC you can only do this if the elements are in sequence from 0
// The intented usecase
enum nums {
  one,
  two,
  three,
};

int arr[] = {
  [one] = 1,
  [two] = 2,
  [three] = 3,
};


// This only works on clang :(
int arr[12] = { [0 ... 12] = 3 };

```

# Constructor - destructor

constexpr constructor

```cpp

```

psudeo destructor

```cpp
int i; // int is a type specifier, not a type name
i.~int(); // This wont compile, but

using foo = int;
i.~foo();


// You can just sprinkle in ~int(); as a function definition
// bitwise int constructed;


class Point() {
    ~Point() {
    }
}

Point p;
p.~Point();

```

# Alternative tokens

```cpp

struct Point{
    compl Point() {

    }
};

// and, or, bitand, bitor;

// alternative tokens for references

```

# Macros and preprocessing

# define

# include

# folds

```cpp
template<typename... Values>
auto sum(Values... values)
{
    return (values + ...);
}

// c++20
auto sum(auto... values){
    return (values + ...);
}
```

# auto auto

# vector<bool> -> string_base<bool>

```cpp

vector<bool> v = {true, false, false};

bool& x = v[1];


basic_string<bool> v = {true, false, false};

bool& x = v[1];
x = true;
```

# Compiler specifics

**builtin
**gcc
case ranges

# UB

```cpp
bool is_intmax(int x){
    if(x > x + 1) {
        return true;
    }
    return false;
}

```

# vector, pair, tuple, std::tie < op

# a bunch of braces: Lambda

# Strings 'R'

# Macros, macro pitfalls

# Structured bindings

and casting to cheat

```cpp
// tuple, pair, and any aggretate (custom struct)

// vector "cannot be destructued"
vector<int> v = {1, 2, 3, 4, 5}
    // note the reversed parameter order
  auto[three, two, one] = *(tuple<int, int, int>*)(v.data());
  auto[three, two, one] = take<3>(v);

```

# Ternaly operator

```cpp

// Returns a reference
// We can assign to it


// Non-conform c++
/// "The elvis operator"
  auto f = [](auto x) {
    return x + 1;
  };
  cout << (f(1) ?: 0) << endl;

```
