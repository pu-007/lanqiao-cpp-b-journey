// 原创基础练习：爬楼梯的方案数；题意见 ../practice.md
#include <iostream>
int main() {
    int n; std::cin >> n;
    const long long mod=1000000007;
    long long previous=1, current=1; // dp[0]=1, dp[1]=1。
    for (int i=2;i<=n;++i) {
        long long next=(previous+current)%mod;
        previous=current; current=next;
    }
    std::cout << (n==0 ? previous : current) << '\n';
}
