// 原创基础练习：找到最高温度；题意见 ../practice.md
#include <algorithm>
#include <iostream>
int main() {
    int n; std::cin >> n;
    long long best; std::cin >> best; // 第一个数确实存在，能处理全负数。
    for (int i=1; i<n; ++i) {
        long long x; std::cin >> x;
        best=std::max(best,x); // 循环后 best 是已读元素的最大值。
    }
    std::cout << best << '\n';
}
