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

# Initialization
```cpp
int a = 0;
int b = {0};
int c = {};
int d(0);
int e{0};


int f; // in static scope

int (g);
int ((h));
int (((((((((g)))))))));
```

# Disanbiguate

```cpp

struct point {};
pair<int, int> point;

point p;


class point p;


class vector<class pair<int, int>>;


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

# vector<bool> -> string_base<bool>

# Compiler specifics

__builtin
__gcc
case ranges
