// 原创基础练习：一次预处理，多次查询；题意见 ../practice.md
#include <iostream>
#include <vector>
int main() {
    int n,q; std::cin >> n >> q;
    std::vector<long long> prefix(n+1,0); // 前 0 项和为 0。
    for (int i=1;i<=n;++i) {
        long long x; std::cin >> x;
        prefix[i]=prefix[i-1]+x;
    }
    while (q--) {
        int l,r; std::cin >> l >> r;
        std::cout << prefix[r]-prefix[l-1] << '\n';
    }
}
