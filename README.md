# AdvanceCPP-reflection-cpp26

用一系列小範例，由淺入深介紹 C++26 靜態反射（[P2996](https://wg21.link/p2996)）：從 `^^` 和 `[: :]` 的基本語法，一路到在編譯期自動產生型別。

每支範例都是一個獨立的 `.cpp`，都有自己的 `main`，只用 `std::cout` 輸出，不用其他炫技寫法。

## 環境與編譯

需要 **GCC 16 以上**。

```
g++ -std=c++26 -freflection file.cpp -o out
```

- 每個檔案的開頭都寫了編譯指令，結尾附上預期的輸出。
- 程式裡的 `static_assert` 兼作自我檢查：只要能編譯成功，就代表反射結果正確。

> 範例使用的是最終併入 C++26 的語法。這和 P2996R1 原文寫法不同：例如反射運算子是 `^^`，不是 `^`；取名字用 `identifier_of`，不是 `name_of`；產生型別用 `define_aggregate`，不是 `define_class`。

## 核心語法與 metafunction 範例

### `B-core-syntax/`：`^^`、`std::meta::info`、splice `[: :]`

| 檔案 | 難度 | 示範什麼 |
|---|---|---|
| `b1_reflect_and_splice.cpp` | ★ | 用 `^^int` 取得反射值，再用 `[: r :]` 貼回程式碼宣告變數 |
| `b2_names.cpp` | ★ | 用 `identifier_of` 取得型別、成員、enum 值、變數的名字；`int` 沒有名字算邊界案例 |
| `b3_info_is_a_value.cpp` | ★★ | `info` 是普通的值：可以放進 `vector`、用 for 迴圈比較，找出最大的型別 |
| `b4_splice_member_and_function.cpp` | ★★ | splice 成員 `p.[: m :]`、splice 函式 `[: ^^add :](3, 4)`、在編譯期決定要用哪個成員 |
| `b5_splice_in_template.cpp` | ★★★ | 什麼時候必須加 `typename` 或 `template`，以及寫錯時編譯器的實際錯誤訊息 |

### `C-metafunctions/`：`<meta>` 函式 + `template for`

| 檔案 | 難度 | 示範什麼 |
|---|---|---|
| `c1_enum_to_string.cpp` | ★ | enum 轉字串，不存在的值回傳 `<unknown>` |
| `c2_string_to_enum.cpp` | ★★ | 字串轉 enum，回傳 `std::optional` |
| `c3_print_struct.cpp` | ★★ | 印出任何 struct 的成員；`private` 成員會被 `access_context` 自動略過 |
| `c4_to_json.cpp` | ★★★ | 任何 struct 轉 JSON，巢狀 struct 用遞迴處理 |
| `c5_struct_of_arrays.cpp` | ★★★★ | 從 `Point` 自動產生 `PointSoA { vector<int> x, y; }`：反射不只能讀，也能產生型別 |

---

歡迎 fork 後發 PR。
