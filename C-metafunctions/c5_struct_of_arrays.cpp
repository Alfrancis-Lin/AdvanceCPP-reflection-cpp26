// C5 ★★★★ 反射不只能「讀」，還能「產生」型別：從 Point 自動產生 PointSoA
//   struct Point    { int x; int y; };
//   struct PointSoA { std::vector<int> x; std::vector<int> y; };   <- 這個由程式產生
// 編譯: g++ -std=c++26 -freflection c5_struct_of_arrays.cpp -o c5
#include <meta>
#include <iostream>
#include <type_traits>
#include <vector>

struct Point { int x; int y; };

struct PointSoA;    // 只宣告，內容交給下面的 consteval 區塊產生

// consteval { ... }：在編譯期執行的一段程式碼
consteval {
    std::vector<std::meta::info> new_members;
    for (std::meta::info m : std::meta::nonstatic_data_members_of(^^Point, std::meta::access_context::current())) {
        // 成員型別 int  ->  std::vector<int>
        std::meta::info vec_type = std::meta::substitute(^^std::vector, { std::meta::type_of(m) });
        // 名字沿用原本的 x、y
        new_members.push_back(std::meta::data_member_spec(vec_type, { .name = std::meta::identifier_of(m) }));
    }
    std::meta::define_aggregate(^^PointSoA, new_members);
}

// 檢查產生出來的型別真的長這樣
static_assert(std::is_same_v<decltype(PointSoA::x), std::vector<int>>);
static_assert(std::is_same_v<decltype(PointSoA::y), std::vector<int>>);

int main() {
    PointSoA soa;
    soa.x.push_back(1);  soa.y.push_back(2);
    soa.x.push_back(3);  soa.y.push_back(4);

    std::cout << "x: " << soa.x[0] << " " << soa.x[1] << "\n";
    std::cout << "y: " << soa.y[0] << " " << soa.y[1] << "\n";
}

// 預期輸出:
// x: 1 3
// y: 2 4
