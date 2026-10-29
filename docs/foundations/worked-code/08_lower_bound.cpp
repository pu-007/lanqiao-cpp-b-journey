// 原创基础练习：有序数组中找第一次；题意见 ../practice.md
#include <algorithm>
#include <iostream>
#include <vector>
int main() {
    int n,x; std::cin >> n >> x;
    std::vector<int> a(n);
    for (int& v:a) std::cin >> v;
    auto it=std::lower_bound(a.begin(),a.end(),x); // 前提：数组已按非递减排序。
    if (it==a.end()) std::cout << -1 << '\n';
    else std::cout << (it-a.begin()+1) << '\n'; // 迭代器差值是从 0 开始的下标。
}
