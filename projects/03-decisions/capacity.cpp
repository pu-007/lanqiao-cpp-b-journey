// capacity：最小运输容量
// 来源：原创教学题
// 题面、范围、样例和训练步骤见同目录 capacity.md
// 复杂度：时间 O(n log(sum a))，空间 O(n)

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
int main() {
    int n, days;
    if (!(std::cin >> n >> days)) return 0;
    std::vector<long long> a(n);
    for (auto& x : a) std::cin >> x;
    long long low = *std::max_element(a.begin(), a.end());
    long long high = std::accumulate(a.begin(), a.end(), 0LL);
    auto feasible = [&](long long capacity) {
        int used = 1;
        long long load = 0;
        for (long long weight : a) {
            if (load + weight > capacity) { ++used; load = 0; }
            load += weight;
        }
        return used <= days;
    };
    // 不变量：最优容量始终在闭区间 [low, high] 中，high 一定可行。
    while (low < high) {
        long long mid = low + (high - low) / 2;
        if (feasible(mid)) high = mid; // mid 可能正是最优答案，保留它。
        else low = mid + 1;           // mid 及更小的值都不可能。
    }
    std::cout << low << '\n';
}
