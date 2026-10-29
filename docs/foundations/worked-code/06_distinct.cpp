// 原创基础练习：统计不同数字；题意见 ../practice.md
#include <algorithm>
#include <iostream>
#include <vector>
int main() {
    int n; std::cin >> n;
    std::vector<int> a(n);
    for (int& x:a) std::cin >> x;
    std::sort(a.begin(),a.end());
    int count=0;
    for (int i=0;i<n;++i)
        if (i==0 || a[i]!=a[i-1]) ++count; // || 短路，i=0 时不会访问 a[-1]。
    std::cout << count << '\n';
}
