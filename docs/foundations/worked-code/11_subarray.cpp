// 原创基础练习：连续子数组的目标和；题意见 ../practice.md
#include <iostream>
#include <vector>
int main() {
    int n; long long k; std::cin >> n >> k;
    std::vector<long long> a(n); for (auto& x:a) std::cin >> x;
    long long count=0;
    for (int l=0;l<n;++l) {
        long long sum=0;
        for (int r=l;r<n;++r) {
            sum+=a[r]; // 增量维护 [l,r] 的和。
            if (sum==k) ++count;
        }
    }
    std::cout << count << '\n';
}
