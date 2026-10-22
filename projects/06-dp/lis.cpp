// lis：能力增长曲线
// 来源：原创教学题
// 题面、范围、样例和训练步骤见同目录 lis.md
// 复杂度：优化版时间 O(n log n)，空间 O(n)

#include <algorithm>
#include <iostream>
#include <vector>
int main() {
    int n; if(!(std::cin>>n)) return 0;
    std::vector<long long> tails;
    for(int i=0;i<n;++i) {
        long long x; std::cin>>x;
        auto it=std::lower_bound(tails.begin(),tails.end(),x);
        if(it==tails.end()) tails.push_back(x); // 能延长当前最长长度。
        else *it=x; // 让同长度结尾更小，为未来保留更多可能。
        // 替换不改变该长度可达；不能把“末尾表”当作路径直接输出。
    }
    std::cout<<tails.size()<<'\n';
}
