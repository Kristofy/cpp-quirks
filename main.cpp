#include <bits/stdc++.h>

using namespace std;

// #define LOG(x) cout << #x << ": " << (x) << endl;
// // The input is some kind of iterable
// #define LOGV(x) cout << #x << ": {"; for (auto i : x) cout << i << ", "; cout << "}\n";
//
// #pragma region start 
//
// template<typename T, typename Seq>
// struct expander;
//
// template<typename T, std::size_t... Is>
// struct expander<T, std::index_sequence<Is...>> {
//     template<typename E, std::size_t>
//     using elem = E;
//     using type = std::tuple<elem<T, Is>...>;
// };
//
// template <typename T, int N>
// struct repeat_tuple {
//     using type = typename expander<T, std::make_index_sequence<N>>::type;
// };
//
// template<typename T, int N>
// using repeat_tuple_t = typename repeat_tuple<T, N>::type;
//
// template<int I, typename T>
// auto take(vector<T>& v) {
//     using EquivalentTuple = repeat_tuple_t<T, I>;
//     return *(EquivalentTuple*)(v.data());
// }
//
// #pragma region end

// int arr[8] = { [0] = 3, [1] = 2, [2] = 3, [3 ... 7] = 8 };
//
// enum nums {
//   one,
//   two,
//   three,
// };
//
// int arr[] = {
//   [one] = 1,
//   [two] = 2,
//   [three] = 3,
// };
int arr[] = { [0] = 5 };

int main() {
  for (int i = 0; i < (int)(sizeof(arr) / sizeof(int)); i++) {
    cout << arr[i] << endl;
  }

  // vector<int> v = {1, 2, 3, 4, 5, 6};


  // auto[three, two, one] = take<3>(v);

  // LOG(one);
  // LOG(two);
  // LOG(three);
  //
  //
  // int v = 2;
  // char ch = 'd';
  //
  // switch(v)  {
  //   case 1:
  //     cout << "one" << endl;
  //     break;
  //   case 2 ... 3:
  //     cout << "two or three" << endl;
  //     break;
  //   default:
  //     cout << "default" << endl;
  // }
  //
  //
  // switch (ch) {
  //   case 'a' ... 'z':
  //     cout << "lowercase" << endl;
  //     break;
  //   case 'A' ... 'Z':
  //     cout << "uppercase" << endl;
  //     break;
  // }
  //
  // auto f = [](auto x) {
  //   return x + 1;
  // };
  // cout << (f(1) ?: 0) << endl;



  return 0;
}
