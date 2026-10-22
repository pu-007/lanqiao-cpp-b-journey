// prefix：静态区间报表
// 来源：原创教学题
// 题面、范围、样例和训练步骤见同目录 prefix.md
// 复杂度：时间 O(n+q)，空间 O(n)

#include <iostream>
#include <vector>
int main() {
    std::ios::sync_with_stdio(false); std::cin.tie(nullptr);
    int n, q;
    if (!(std::cin >> n >> q)) return 0;
    std::vector<long long> prefix(n + 1, 0); // 第 0 项是空前缀。
    for (int i = 1; i <= n; ++i) {
        long long x; std::cin >> x;
        prefix[i] = prefix[i - 1] + x;
    }
    while (q--) {
        int l, r; std::cin >> l >> r;
        // 包含第 l 项，所以减掉的只能是 l-1 之前的部分。
        std::cout << prefix[r] - prefix[l - 1] << '\n';
    }
}
