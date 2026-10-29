// 原创基础练习：第一次出现的位置；题意见 ../practice.md
#include <iostream>
int main() {
    int n; long long target; std::cin >> n >> target;
    int answer=-1;
    for (int i=1;i<=n;++i) {
        long long x; std::cin >> x;
        if (x==target && answer==-1) answer=i;
    }
    std::cout << answer << '\n';
}
