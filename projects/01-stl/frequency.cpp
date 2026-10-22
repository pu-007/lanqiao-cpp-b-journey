// frequency：日志词频分析
// 来源：原创教学题
// 题面、范围、样例和训练步骤见同目录 frequency.md
// 复杂度：时间 O(n log u)，空间 O(u)，u 是不同单词数（长度视为常数）

#include <iostream>
#include <map>
#include <string>
int main() {
    int n;
    if (!(std::cin >> n)) return 0;
    std::map<std::string, int> count;
    for (int i = 0; i < n; ++i) {
        std::string word;
        std::cin >> word;
        ++count[word]; // 缺失键对应的 int 会值初始化为 0。
    }
    // map 已按 key 排序；不要为了排序再复制一遍。
    for (const auto& entry : count)
        std::cout << entry.first << ' ' << entry.second << '\n';
}
