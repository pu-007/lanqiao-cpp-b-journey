// real_smelting：冶炼金属
// 来源：2023 省赛 C/C++ B 组；https://www.luogu.com.cn/problem/P9240
// 题面、范围、样例和训练步骤见同目录 real_smelting.md
// 复杂度：时间 O(n)，空间 O(1)

#include <algorithm>
#include <iostream>
int main() {
    int n;if(!(std::cin>>n))return 0;
    long long low=1,high=1000000000LL;
    while(n--) {
        long long a,b;std::cin>>a>>b;
        low=std::max(low,a/(b+1)+1);
        high=std::min(high,a/b);
        // 每条记录就是一个可行区间；全部成立等价于取交集。
    }
    std::cout<<low<<' '<<high<<'\n';
}
