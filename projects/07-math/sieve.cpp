// sieve：素数查询服务
// 来源：原创教学题
// 题面、范围、样例和训练步骤见同目录 sieve.md
// 复杂度：时间 O(N log log N+q)，空间 O(N)

#include <iostream>
#include <vector>
int main() {
    int n,q; if(!(std::cin>>n>>q)) return 0;
    std::vector<char> prime(n+1,true); // char 避免 vector<bool> 的代理引用特性。
    prime[0]=prime[1]=false;
    for(int p=2;p<=n/p;++p) {
        if(!prime[p]) continue;
        for(int multiple=p*p;multiple<=n;multiple+=p) prime[multiple]=false;
    }
    while(q--) {
        int x; std::cin>>x;
        std::cout<<(prime[x]?"YES\n":"NO\n");
    }
}
