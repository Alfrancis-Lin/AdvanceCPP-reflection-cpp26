// C1 ★ enum 轉字串：enumerators_of 拿到所有 enum 值，template for 逐一比對
// 編譯: g++ -std=c++26 -freflection c1_enum_to_string.cpp -o c1
#include <meta>
#include <iostream>
#include <string>

enum class Color { red, green, blue };

template <typename E>
std::string enum_to_string(E value) {
    // enumerators_of 回傳的是編譯期的 std::vector，不能直接留到執行期；
    // define_static_array 把它轉成固定的靜態陣列，template for 才能展開
    template for (constexpr std::meta::info e : std::define_static_array(std::meta::enumerators_of(^^E))) {
        // 這個迴圈在編譯期就展開成 3 個 if：red、green、blue 各一個
        if (value == [: e :])
            return std::string(std::meta::identifier_of(e));
    }
    return "<unknown>";
}

int main() {
    std::cout << enum_to_string(Color::red) << "\n";
    std::cout << enum_to_string(Color::green) << "\n";
    std::cout << enum_to_string(Color::blue) << "\n";

    // 邊界案例：不在 enum 定義裡的值
    std::cout << enum_to_string(static_cast<Color>(7)) << "\n";
}

// 預期輸出:
// red
// green
// blue
// <unknown>
