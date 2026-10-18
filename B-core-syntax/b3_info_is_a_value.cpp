// B3 ★★ std::meta::info 是普通的值：可以放進 vector、比較、傳進函式、當回傳值
// 編譯: g++ -std=c++26 -freflection b3_info_is_a_value.cpp -o b3
#include <meta>
#include <iostream>
#include <vector>

// 一般的函式，只是參數和回傳值是 info；consteval 代表只在編譯期執行
consteval std::meta::info bigger(std::meta::info a, std::meta::info b) {
    if (std::meta::size_of(a) >= std::meta::size_of(b))
        return a;
    return b;
}

// 用普通的 vector 和 for 迴圈處理「型別」
consteval std::meta::info largest_type() {
    std::vector<std::meta::info> types = { ^^char, ^^short, ^^int, ^^double };
    std::meta::info best = types[0];
    for (std::meta::info t : types)
        best = bigger(best, t);
    return best;
}

int main() {
    constexpr std::meta::info t = largest_type();
    static_assert(t == ^^double);

    // 算出來的結果再 splice 回去，宣告一個變數
    typename [: t :] value = 3.5;    // 等同於 double value = 3.5;

    std::cout << "largest type: " << std::meta::display_string_of(t) << "\n";
    std::cout << "size: " << std::meta::size_of(t) << "\n";
    std::cout << "value = " << value << "\n";
}

// 預期輸出:
// largest type: double
// size: 8
// value = 3.5
