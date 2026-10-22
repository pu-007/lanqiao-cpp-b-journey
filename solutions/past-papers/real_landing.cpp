// real_landing：飞机降落
// 来源：2023 省赛 C/C++ B 组；https://www.luogu.com.cn/problem/P9241
// 题面、范围、样例和训练步骤见同目录 real_landing.md
// 复杂度：最坏时间 O(n·n!)，空间 O(n)

#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>
struct Plane {long long arrival,wait,duration;};
int main() {
    int tests;if(!(std::cin>>tests))return 0;
    while(tests--) {
        int n;std::cin>>n;
        std::vector<Plane>planes(n);
        for(auto&p:planes)std::cin>>p.arrival>>p.wait>>p.duration;
        std::vector<char>used(n,false);
        std::function<bool(int,long long)>dfs=[&](int count,long long now) {
            if(count==n)return true;
            for(int i=0;i<n;++i)if(!used[i]) {
                long long start=std::max(now,planes[i].arrival);
                if(start>planes[i].arrival+planes[i].wait)continue;
                used[i]=true; // 做选择。
                if(dfs(count+1,start+planes[i].duration))return true;
                used[i]=false; // 此顺序失败，撤销后试别的飞机。
            }
            return false;
        };
        std::cout<<(dfs(0,0)?"YES\n":"NO\n");
    }
}
