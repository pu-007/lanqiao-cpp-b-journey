// ranking：训练排行榜
// 来源：原创教学题
// 题面、范围、样例和训练步骤见同目录 ranking.md
// 复杂度：时间 O(n log n)，空间 O(n)（含记录；名字长度视为常数）

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
struct Record { std::string name; int score; };
int main() {
    int n;
    if (!(std::cin >> n)) return 0;
    std::vector<Record> records(n); // 创建 n 个元素，可以直接按下标访问。
    for (auto& record : records) {  // & 表示引用；去掉 & 会修改副本。
        std::cin >> record.name >> record.score;
    }
    std::sort(records.begin(), records.end(),
        [](const Record& a, const Record& b) {
            // const 引用避免复制，也表明比较不修改记录。
            if (a.score != b.score) return a.score > b.score;
            return a.name < b.name; // 两字段都相等时返回 false。
        });
    for (const auto& record : records)
        std::cout << record.name << ' ' << record.score << '\n';
}
