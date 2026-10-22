// difference：批量训练排期
// 来源：原创教学题
// 题面、范围、样例和训练步骤见同目录 difference.md
// 复杂度：时间 O(n+m)，空间 O(n)

#include <iostream>
#include <vector>
int main() {
    int n, m;
    if (!(std::cin >> n >> m)) return 0;
    std::vector<long long> diff(n + 2, 0); // n+1 是撤销影响的哨兵。
    for (int i = 0; i < m; ++i) {
        int l, r; long long delta;
        std::cin >> l >> r >> delta;
        diff[l] += delta;       // 从 l 开始生效。
        diff[r + 1] -= delta;   // 到 r+1 开始失效，而非在 r 失效。
    }
    long long current = 0;
    for (int i = 1; i <= n; ++i) {
        current += diff[i];
        if (i > 1) std::cout << ' ';
        std::cout << current;
    }
    std::cout << '\n';
}
