// intervals：会议室预约
// 来源：原创教学题
// 题面、范围、样例和训练步骤见同目录 intervals.md
// 复杂度：时间 O(n log n)，空间 O(n)

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
int main() {
    int n; if (!(std::cin >> n)) return 0;
    // pair 默认先比较 first，再比较 second；因此存 (结束,开始)。
    std::vector<std::pair<int,int>> meetings(n);
    for (auto& p : meetings) std::cin >> p.second >> p.first;
    std::sort(meetings.begin(), meetings.end());
    int last_end = -1, chosen = 0;
    for (const auto& p : meetings) {
        if (p.second >= last_end) {
            ++chosen;
            last_end = p.first; // 只记录最后一场的结束时间即可。
        }
    }
    std::cout << chosen << '\n';
}
