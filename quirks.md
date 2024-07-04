# C++ Quirks

## Table of contents

- Szintaxis
  - Inicializáció
  - If utasítások
  - For ciklusok
  - Switch case
  - Tömbök
  - Konstruktor - destruktor
  - Operátorok / alternatív tokenek
  - auto
  - Forward declaration
  - ternary
  - macro define, stringify, include
  - Structured bindings
  - Disanbiguate
  - vector, pair, tuple, std::tie < op
- Nem szabványos
  - ternary (elvis)
  - tömb inicializálás
  - Compiler specifics
- Halandó
  - raw string + multiline
  - folds
  - vector<bool> -> string_base<bool>
  - macro hibák () és do while
  - a bunch of braces: Lambda
- Fekete mágia
  - UB
  - vessző operátor vs vessző szeparátor

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

# If / elágazások utasítás

# Disanbiguate

```cpp

struct point {};
pair<int, int> point;

point p;


class point p;


class vector<class pair<int, int>>;


```

- Inicializáció
- If utasítások
- For ciklusok
- Switch case
- Tömbök
- Konstruktor - destruktor
- Operátorok / alternatív tokenek
- auto
- Forward declaration
- ternary
- macro define, stringify, include
- Structured bindings
- Disanbiguate
- vector, pair, tuple, std::tie < op
- Nem szabványos
  - ternary (elvis)
  - tömb inicializálás
  - Compiler specifics
- Halandó
  - raw string + multiline
  - folds
  - vector<bool> -> string_base<bool>
  - macro hibák () és do while
  - a bunch of braces: Lambda
- Fekete mágia
  - UB
  - vessző operátor vs vessző szeparátor

---

# If statements

```cpp
if (int k = 2; k==2) {
    ...
}


if (struct Foo; true) {

}


if(false; true) {

}

if(; true) {

}

```

```cpp
if constexpr (false) {


} else {

}
```

# For loops

```cpp
map<string, int> mp;
mp["hello"] = 42;

// nice O(n*m) looping because of string copy
for(pair<string, int> kv : mp) {


}

```

```cpp
map<string, int> mp;
mp["hello"] = 42;

for(pair<string, int>& kv : mp) {
    cout << kv.first << " " << kv.second << '\n';
}

```

```cpp
map<string, int> mp;
mp["hello"] = 42;

// nice O(n*m) looping because of string copy
for(auto&[key, value] : mp) {
    cout << key << " " << value << '\n';
}

```

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
