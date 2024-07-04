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
- Mesteri Varázslatok / Masterful Magic
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

# varázsigék / Intermediate Incantations

## Az `auto` kulcsszó

```cpp
    int a = 42;
    auto b = a;

    vector<int> v = {1, 2, 3, 4, 5};
    auto v2 = {1, 2, 3, 4, 5}; // Ez nem egy vector
    auto v3 = vector<int>{1, 2, 3, 4, 5}; // Ez egy vector
    auto v4 = vector{1, 2, 3, 4, 5}; // Ez egy vector
```

```cpp
auto add(int a, int b) {
    return a + b;
}

auto a = add(1, 2);
```

```cpp
auto add(auto a, auto b) {
    return a + b;
}

string s1 = "hello";
string s2 = "world";
auto b = add(s1, s2);
```

## Alternatív tokenek

A teljes [lista](https://en.cppreference.com/w/cpp/language/operator_alternative)

```cpp
bool visited = false;
if(not visited) {
    // ...
}

bool seen = false;
if(seen or visited) {

}

// A bit műveletekre is van alternatív token
// pl
int x = 2 | 1;
int y = 2 bitor 1;

```

### Pop quiz #3

Mire használjuk az alternatív tokeneket?

```cpp
// természetesen semmi hasznosra

// referencia típusokra
vector v = {1, 2, 3, 4, 5};

for (int bitand i : v) {
    cout << i << ' ';
    i++;
}
```

```cpp
vector v = <% 1, 2, 3, 4, 5 %>;

for (int i = 0; i < v.size();i++) <%
  cout << i << "th element: " << v<:i:> << endl;
%>
```

## Preprocessor / Makrók

```cpp
#define PI 3.1415

cout << PI;
```

```cpp
#define PI 3.1415 + 0.0001

cout << 3*PI;
```

```cpp
#define PI 3.1415 + 0.0001

cout << 3*3.1415 + 0.0001;
```

Erről csak később, ha lesz rá idő

```cpp
// Makróknak lehetnek paraméterei
// sőt akár tetszőleges számú
#define SUM(a, b) a + b
#define PRINT_ALL(...) ...
```

Include szöveg behelyettesítés fileból

```cpp
// "closing.h"
}
```

```cpp
int main() {

    return 0;

#include "closing.h"
```

# Mesteri Varázslatok / Masterful Magic

Összehasonlítás lexikografikusan

```cpp
    string s1 = "hello";
    string s2 = "world";

    cout << (s1 < s2);
```

```cpp
    vector<int> v = {1, 2, 3, 4};
    vector<int> v2 = {1, 2, 3, 5, 1};

    cout << (v < v2);
```

```cpp
    pair<int, int> p = {1, 2};
    pair<int, int> p2 = {1, 3};

    tuple<int, string, float> t = {1, "hello", 3.14};
    tuple<int, string, float> t2 = {1, "world", 3.14};

    cout << (p < p2);
    cout << (t < t2);
```

Saját összehasonlítást tudunk ezzel írni

```cpp
Struct Point {
    int x, y, z;
};

bool kisebb(Point a, Point b) {
    return (a.x < b.x) or (a.x == b.x and a.y < b.y) or (a.x == b.x and a.y == b.y and a.z < b.z);
}
```

```cpp
struct Point {
    int x, y, z;
};

bool kisebb(Point a, Point b) {
    tuple t1 = {a.x, a.y, a.z};
    tuple t2 = {b.x, b.y, b.z};
    return a.x < b.x;
}
```

Ez így rendben van, de ha nem int, name string lenne, akkor?
Ez itt mind másolás így string vagy vector esetén lassebb lenne

```cpp
struct Point {
    int x, y, z;
};

bool kisebb(Point a, Point b) {
    return tie(a.x, a.y, a.z) < tie(b.x, b.y, b.z);
}
```

Stringek és escape karakterek

```cpp
cout << "Hello\nWorld";
cout << "Hello\tWorld";

// Ha \n-t akarunk kiírni
cout << "Hello\\nWorld";

// Valójában minden \-t kétszer
```

[Raw string literals](https://en.cppreference.com/w/cpp/language/string_literal)

```cpp
cout << R"(Hello\nWorld)";
// kiír: Hello\nWorld

// A sima stringgel elentétben még többsoros is lehet
string s = R"(Hello
World
How
are
"you"?)";
```

### Pop quiz #4

Tegyük fel hogy nem tudtuk hogy így is lehet több soros stringet csinálni, hogyan csináltuk volna?

```cpp
string s = "Hello\nWorld\nHow\nare\nyou?";
```

```cpp
string s =  "Hello\n"
          + "World\n"
          + "How\n"
          + "are\n"
          + "you?";
```

Sajnos ez nem fordul le

```cpp
using namespace std::literals;

string s =  "Hello\n"s
          + "World\n"
          + "How\n"
          + "are\n"
          + "you?";
```

## vector<bool> csodái

```cpp
// egy bool 1 byte de csak 1 bitet használ
// így a vector<bool> ra optimalizált megoldást használnak
// ahol 1 biten tárolják, viszont cserébe nem bool okat tartalmaz

// Ez szinte sosem probléma
vector<bool> v = {true, false, false};
v[1] = true;
for (bool b : v) {
    cout << b << ' ';
}
// Minden működik, kivétel
bool& x = v[1]; // Ez nem fordul le

// Bárcsak lenne egy vectorhoz hasonló konténer
// ami elemeket tárol és tud nőni
```

```cpp
string s = "Hello";
char& c = s[1];

basic_string<bool> v = {true, false, false};
bool& x = v[1];
```

# Mesteri Varázslatok / Masterful Magic

## Ternaly operator

```cpp
// Az "egysoros if"
int a = 42;
int b = (a == 42) ? 3 : 27;
// Az igaz és hamis típusának pontosan egyeznie kell
// Vagyis néha, nem mindig
```

Az operátor állhat az egyenlőség bal oldalán is, feltéve, hogy az igaz hamis ág típusai pontosan megegyeznek, és tudunk hozzájuk értéket rendelni. (refereciák)

```cpp
float a = -1.0f;
int b;
(false ? a : b) = 42; // nem egyenlő típusok

(false ? 3 : 4) = 42; // nem referenciák, nem adhatunk értéket a 3-nak


int c = 5;
(a < 0.1f ? a : c) = 42; // Ez helyes
```

## Literálok

### Pop quiz #5

Mi a típusa az alábbi változóknak?

```cpp
auto a = 1;
auto b = 1u;
auto c = 1U;
auto c = 1LL;
auto d = 1.0;
auto e = 1.0f;
auto f = 1e9 + 7;
```

### Pop quiz #6

Mennyi a + b + c?

```cpp
int a = 001;
int b = 010;
int c = 100;
cout << a + b + c;
```

---

109

[Int literálok](https://en.cppreference.com/w/cpp/language/integer_literal)

```cpp
int large = 1'000'000;
int binary = 0b1010;
int octal =  011230;
int hex =    0x123f;
int binary = 0b1010'1010'1010'1010'1010'1010'1010'1010;
```

## Lambdák (Opcionális)

```cpp
// This is c++20
auto add = [&]<class T>(T a, auto&&... as) -> decltype(auto) { return (a + ... + as);};

int sum = add(1, 2, 3, 4, 5);
cout << sum;

int sum1 = [&]<class T>(T a, auto&&... as) -> decltype(auto) { return (a + ... + as);}(1, 2, 3, 4, 5);


// in c++17
auto add = [&](auto a, auto&&... as) -> decltype((a + ... + as)) { return (a + ... + as);};

```

```cpp
auto cmp = [](pair<int, int> a, pair<int, int> b) {
    return a.second < b.second;
};

// Ugyan az mint

bool cmp(pair<int, int> a, pair<int, int> b) {
    return a.second < b.second;
}

vector<pair<int, int>> v = {{1, 2}, {3, 4}, {5, 6}};
sort(v.begin(), v.end(), [](pair<int, int> a, pair<int, int> b) {
    return a.second < b.second;
});
```

Macros

```cpp
#define LOG(x) cout << x << '\n'

int main() {
    int k = 42;
    LOG(k);
    return 0;
}
```

```cpp
#define LOG(x) cout << x << '\n'

int main() {
    int k = 42;
    LOG(k << 1);
    return 0;
}
```

```cpp
#define LOG(x) cout << (x) << '\n'
#define L(X) cout << #x << (x) << '\n';

int main() {
    string s = "hello";
    L(s);

    return 0;
}
```

Több "soros" makró

```cpp
#define LOG(x) cout << "{: "; cout << (x); cout << " :}\n";

// Lehet így is:
#define LOG(x) cout << "{: "; \
cout << (x); \
cout << " :}\n";
```

### Pop quiz #7

Hogyan tudunk kitolni magunkal egy ilyen makróval?

```cpp
#define LOG(x) cout << "{: "; cout << (x); cout << " :}\n";

int main() {
    int k = 42
    if (k == 42) {
        LOG(k);
    }

    for(int i = 0; i < 10; i++) LOG(i);

    return 0;
}
```

Írhatunk köré egy scope-ot mint a case-eknél a switch-ben

```cpp
#define LOG(x) {cout << "{: "; cout << (x); cout << " :}\n"};

int main() {
    for(int i = 0; i < 10; i++) LOG(i);

    return 0;
}
```

Látszólag működik, kivétel ha

```cpp
#define LOG(x) {cout << "{: "; cout << (x); cout << " :}\n";}

int main() {
    int k = 10;
    if (k == 10)
        LOG(k); // Ez itt syntax error
    else
        cout << "Not 10\n";

    return 0;
}
```

```cpp
int main() {
    int k = 10;
    if (k == 10)
        {cout << "{: "; cout << (x); cout << " :}\n";};
    else
        cout << "Not 10\n";

    return 0;
}
```

```cpp
int main() {
    int k = 10;
    if (k == 10) {
        cout << "{: ";
        cout << (x);
        cout << " :}\n";
    }; else
        cout << "Not 10\n";

    return 0;
}
```

Az egyetlen alkalom a do-while ciklusra

```cpp
#define LOG(x) do {cout << "{: "; cout << (x); cout << " :}\n";} while(0)
```

Így már minden esetben helyes

# Fekete mágia / Black Magic

- UB
- vessző operátor vs vessző szeparátor
- Tömbök
- ternary (elvis)
- tömb inicializálás
- Compiler specifics

---

# Switch

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

# Macros and preprocessing advanced

# auto auto

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

# a bunch of braces: Lambda

# Strings 'R'

# Macros, macro pitfalls

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

Other interesting but harder
remaining keyword c++20

```cpp
alignas
alignof
asm
catch
concept (C++20)
const
consteval (C++20)
constexpr
constinit (C++20)
const_cast
co_await (C++20)
co_return (C++20)
co_yield (C++20)
decltype
delete
dynamic_cast
enum
explicit
export
extern
friend
goto
inline
mutable
namespace
new
noexcept
operator
register
reinterpret_cast
requires (C++20)
sizeof
static
static_assert
static_cast
template
thread_local
throw
try
typedef
typeid
typename
union
using
virtual
volatile
```

[keywords](https://en.cppreference.com/w/cpp/keyword)

https://en.cppreference.com/w/cpp/language/decltype + decltype(auto)
https://en.cppreference.com/w/cpp/language/fold

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

https://en.cppreference.com/w/cpp/language/parameter_pack
https://en.cppreference.com/w/cpp/language/lambda
take C style arrays as reference to a function without it decaying to a pointer
