// C4 ★★★ 任何 struct 轉 JSON：基本型別用一般多載，struct 用反射，巢狀 struct 靠遞迴
// 編譯: g++ -std=c++26 -freflection c4_to_json.cpp -o c4
#include <meta>
#include <iostream>
#include <string>

struct Point { int x; int y; };
struct Line { Point a; Point b; };
struct Student { std::string name; int age; double score; };

// 基本型別：一般的函式多載
void write_json(std::ostream& out, int v) { out << v; }
void write_json(std::ostream& out, double v) { out << v; }
void write_json(std::ostream& out, const std::string& v) { out << '"' << v << '"'; }   // 未處理跳脫字元

// 其他型別：當成 struct，用反射逐一處理成員
template <typename T>
void write_json(std::ostream& out, const T& obj) {
    static_assert(std::meta::is_class_type(^^T), "write_json only supports int, double, std::string and structs");

    out << "{";
    bool first = true;
    template for (constexpr std::meta::info m :
                  std::define_static_array(std::meta::nonstatic_data_members_of(^^T, std::meta::access_context::current()))) {
        if (!first)
            out << ", ";
        out << '"' << std::meta::identifier_of(m) << "\": ";
        write_json(out, obj.[: m :]);    // 成員如果也是 struct，就會再走進這個函式
        first = false;
    }
    out << "}";
}

int main() {
    write_json(std::cout, Point{1, 2});
    std::cout << "\n";

    write_json(std::cout, Student{"Amy", 20, 91.5});
    std::cout << "\n";

    write_json(std::cout, Line{{0, 0}, {3, 4}});
    std::cout << "\n";
}

// 預期輸出:
// {"x": 1, "y": 2}
// {"name": "Amy", "age": 20, "score": 91.5}
// {"a": {"x": 0, "y": 0}, "b": {"x": 3, "y": 4}}
