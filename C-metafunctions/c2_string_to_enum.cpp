// C2 ★★ 字串轉 enum：反過來比對名字，找不到就回傳 std::nullopt
// 編譯: g++ -std=c++26 -freflection c2_string_to_enum.cpp -o c2
#include <meta>
#include <iostream>
#include <optional>
#include <string>

enum class Color { red, green, blue };

template <typename E>
std::optional<E> string_to_enum(const std::string& name) {
    template for (constexpr std::meta::info e : std::define_static_array(std::meta::enumerators_of(^^E))) {
        if (name == std::meta::identifier_of(e))
            return [: e :];
    }
    return std::nullopt;
}

int main() {
    std::optional<Color> a = string_to_enum<Color>("blue");
    std::optional<Color> b = string_to_enum<Color>("purple");

    if (a.has_value())
        std::cout << "blue -> " << static_cast<int>(a.value()) << "\n";
    if (!b.has_value())
        std::cout << "purple -> not found\n";
}

// 預期輸出:
// blue -> 2
// purple -> not found
