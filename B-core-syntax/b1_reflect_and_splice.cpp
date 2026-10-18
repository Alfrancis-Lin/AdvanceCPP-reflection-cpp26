// B1 ★ 反射運算子 ^^ 把「程式裡的東西」變成一個值；splice [: :] 再把它貼回程式碼
// 編譯: g++ -std=c++26 -freflection b1_reflect_and_splice.cpp -o b1
#include <meta>
#include <iostream>

int main() {
    // 1. ^^int：把型別 int 變成一個編譯期的值，型別是 std::meta::info
    constexpr std::meta::info r = ^^int;

    // 2. [: r :]：把這個值貼回程式碼，當成型別使用
    typename [: r :] x = 42;    // 等同於 int x = 42;

    // 同一個實體的反射一定相等，不同的就不相等
    static_assert(r == ^^int);
    static_assert(r != ^^double);

    std::cout << "r is: " << std::meta::display_string_of(r) << "\n";
    std::cout << "x = " << x << "\n";
}

// 預期輸出:
// r is: int
// x = 42
