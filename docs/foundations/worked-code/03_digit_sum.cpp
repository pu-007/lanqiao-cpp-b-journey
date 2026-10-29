// 原创基础练习：数位之和；题意见 ../practice.md
#include <iostream>
int main() {
    long long x; std::cin >> x;
    int sum=0;
    while (x>0) {
        sum+=static_cast<int>(x%10); // 把最后一位加入答案。
        x/=10;                       // 把处理过的最后一位删除。
    }
    std::cout << sum << '\n';
}
