// 原创基础练习：判断质数；题意见 ../practice.md
#include <iostream>
int main() {
    long long n; std::cin >> n;
    bool prime=n>=2;
    for (long long d=2;d<=n/d;++d) {
        if (n%d==0) {prime=false;break;}
    }
    std::cout << (prime ? "YES\n" : "NO\n");
}
