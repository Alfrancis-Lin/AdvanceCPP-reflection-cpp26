// C3 ★★ 印出任何 struct 的所有成員：nonstatic_data_members_of + template for
// 編譯: g++ -std=c++26 -freflection c3_print_struct.cpp -o c3
#include <meta>
#include <iostream>
#include <string>

struct Point { int x; int y; };
struct Student { std::string name; int age; double score; };

class Account {
public:
    Account(std::string o, int b) : owner(o), balance(b) {}
    std::string owner;
private:
    int balance;
};

template <typename T>
void print_struct(const T& obj) {
    // access_context::current()：只看得到「在這裡本來就能存取」的成員，所以 private 會被略過
    // 換成 access_context::unchecked() 就連 private 都看得到（見 E 段的封裝討論）
    bool first = true;
    template for (constexpr std::meta::info m :
                  std::define_static_array(std::meta::nonstatic_data_members_of(^^T, std::meta::access_context::current()))) {
        if (!first)
            std::cout << ", ";
        std::cout << std::meta::identifier_of(m) << " = " << obj.[: m :];
        first = false;
    }
    std::cout << "\n";
}

int main() {
    print_struct(Point{1, 2});
    print_struct(Student{"Amy", 20, 91.5});

    // 邊界案例：balance 是 private，不會被印出來
    print_struct(Account{"Bob", 1000});
}

// 預期輸出:
// x = 1, y = 2
// name = Amy, age = 20, score = 91.5
// owner = Bob
