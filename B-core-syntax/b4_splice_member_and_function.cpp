// B4 ★★ splice 不只能貼型別，也能貼「成員」和「函式」
// 編譯: g++ -std=c++26 -freflection b4_splice_member_and_function.cpp -o b4
#include <meta>
#include <iostream>

struct Point { int x; int y; };

int add(int a, int b) { return a + b; }

// 在編譯期決定要用哪個成員
consteval std::meta::info pick_member(bool want_x) {
    if (want_x)
        return ^^Point::x;
    return ^^Point::y;
}

int main() {
    Point p{1, 2};

    // 1. 貼成員：p.[: ^^Point::x :] 等同於 p.x
    p.[: ^^Point::x :] = 10;

    // 2. 成員由函式決定：這裡選到 y，所以等同於 p.y = 20
    constexpr std::meta::info m = pick_member(false);
    p.[: m :] = 20;

    // 3. 貼函式：[: ^^add :](3, 4) 等同於 add(3, 4)
    int sum = [: ^^add :](3, 4);

    std::cout << "p.x = " << p.x << "\n";
    std::cout << "p.y = " << p.y << "\n";
    std::cout << "picked member: " << std::meta::identifier_of(m) << "\n";
    std::cout << "sum = " << sum << "\n";
}

// 預期輸出:
// p.x = 10
// p.y = 20
// picked member: y
// sum = 7
