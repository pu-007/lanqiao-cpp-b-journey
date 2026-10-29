// 原创基础练习：最大公约数；题意见 ../practice.md
#include <iostream>
int main() {
    long long a,b; std::cin >> a >> b;
    while (b!=0) {
        long long remainder=a%b;
        a=b; b=remainder; // 原问题变成 gcd(b, a%b)。
    }
    std::cout << a << '\n';
}
