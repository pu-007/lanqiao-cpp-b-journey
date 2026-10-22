// powmod：大指数取模器
// 来源：原创教学题
// 题面、范围、样例和训练步骤见同目录 powmod.md
// 复杂度：时间 O(log(b+1))，空间 O(1)

#include <iostream>
int main() {
    long long a,b,m; if(!(std::cin>>a>>b>>m)) return 0;
    a%=m;
    long long result=1%m; // b=0 或 m=1 都能正确处理。
    while(b>0) {
        if(b&1LL) result=result*a%m;
        a=a*a%m; // 模数上限 10^9；若扩到 10^18，此乘法可能溢出。
        b>>=1;
        // 数学不变量：result * a^b 与原目标同余。
    }
    std::cout<<result<<'\n';
}
