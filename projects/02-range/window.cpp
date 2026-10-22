// window：预算内连续训练段
// 来源：原创教学题
// 题面、范围、样例和训练步骤见同目录 window.md
// 复杂度：时间 O(n)，空间 O(n)

#include <iostream>
#include <vector>
int main() {
    int n; long long limit;
    if (!(std::cin >> n >> limit)) return 0;
    std::vector<long long> a(n);
    for (auto& x : a) std::cin >> x;
    int left = 0;
    long long sum = 0, answer = 0;
    for (int right = 0; right < n; ++right) {
        sum += a[right];
        while (left <= right && sum > limit) sum -= a[left++];
        // 若单个 a[right] 都过大，此时 left=right+1，贡献恰为 0。
        answer += right - left + 1;
    }
    std::cout << answer << '\n';
}
