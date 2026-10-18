// B2 ★ 用反射拿到「名字」：型別名、成員名、enum 值的名字、變數名
// 編譯: g++ -std=c++26 -freflection b2_names.cpp -o b2
#include <meta>
#include <iostream>

struct Point { int x; int y; };
enum class Color { red, green, blue };
int counter = 0;

int main() {
    // identifier_of：只給名字本身
    std::cout << std::meta::identifier_of(^^Point) << "\n";
    std::cout << std::meta::identifier_of(^^Point::y) << "\n";
    std::cout << std::meta::identifier_of(^^Color::red) << "\n";
    std::cout << std::meta::identifier_of(^^counter) << "\n";

    // 名字在編譯期就拿得到，所以可以直接 static_assert
    static_assert(std::meta::identifier_of(^^Point) == "Point");

    // 邊界案例：int 是內建型別，沒有「識別字」，不能用 identifier_of
    static_assert(!std::meta::has_identifier(^^int));
    // 這時改用 display_string_of：給人看的描述，任何反射都能用
    std::cout << std::meta::display_string_of(^^int) << "\n";
}

// 預期輸出:
// Point
// y
// red
// counter
// int
