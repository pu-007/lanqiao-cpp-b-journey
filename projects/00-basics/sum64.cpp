// sum64：训练时长统计
// 来源：原创教学题
// 题面、范围、样例和训练步骤见同目录 sum64.md
// 复杂度：时间 O(n)，额外空间 O(1)

#include <iostream>
int main() {
    // 关闭 C/C++ 流同步以减少输入开销；之后不混用 scanf/printf。
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    if (!(std::cin >> n)) return 0; // 空输入时正常结束。
    long long total = 0;           // 总和的类型由上界决定。
    for (int i = 0; i < n; ++i) {
        long long minutes;
        std::cin >> minutes;
        total += minutes;         // 不需要保存全部数据：读一项，处理一项。
    }
    std::cout << total << '\n';    // 竞赛输出只含答案，不输出提示语。
}
