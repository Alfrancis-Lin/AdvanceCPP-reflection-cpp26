// B5 ★★★ 邊界案例：什麼時候 splice 前面一定要加 typename 或 template
// 編譯: g++ -std=c++26 -freflection b5_splice_in_template.cpp -o b5
#include <meta>
#include <iostream>

template <typename T>
struct Box { T value; };

template <typename T>
T twice(T v) { return v + v; }

// 情況 1：info 當 template 參數。R 要等實例化才知道是什麼，
// 所以必須寫 typename 告訴編譯器「這是型別」。
template <std::meta::info R>
void print_default() {
    typename [: R :] v{};
    // 如果寫成 [: R :] v{};  GCC 會報錯：expected ';' before 'v'
    // 因為編譯器預設把 splice 當成「表達式」，不是型別
    std::cout << std::meta::display_string_of(R) << " default = " << v << "\n";
}

int main() {
    print_default<^^int>();
    print_default<^^double>();

    // 情況 2：splice 出來的是 template，後面接 <...> 時要加關鍵字，否則 < 會被當成「小於」
    //   類別 template（結果是型別）     -> 加 typename
    //   函式 template（結果是表達式）   -> 加 template
    typename [: ^^Box :]<int> b{5};             // 等同於 Box<int> b{5};
    int y = template [: ^^twice :]<int>(21);    // 等同於 twice<int>(21)
    // 如果寫成 template [: ^^Box :]<int> b{5};  GCC 會報錯：expected a reflection of an expression

    // 情況 3：不想寫 template 關鍵字，可以用 substitute 先在編譯期組出 Box<double>
    constexpr std::meta::info box_double = std::meta::substitute(^^Box, { ^^double });
    typename [: box_double :] c{1.5};           // 等同於 Box<double> c{1.5};

    std::cout << "b.value = " << b.value << "\n";
    std::cout << "y = " << y << "\n";
    std::cout << std::meta::display_string_of(box_double) << " c.value = " << c.value << "\n";
}

// 預期輸出:
// int default = 0
// double default = 0
// b.value = 5
// y = 42
// Box<double> c.value = 1.5
