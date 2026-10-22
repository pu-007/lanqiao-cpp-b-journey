// windowmax：滑动峰值监控
// 来源：原创教学题
// 题面、范围、样例和训练步骤见同目录 windowmax.md
// 复杂度：时间 O(n)，空间 O(n)（输入数组；队列 O(k)）

#include <deque>
#include <iostream>
#include <vector>
int main() {
    int n,k;if(!(std::cin>>n>>k))return 0;
    std::vector<long long>a(n);for(auto&x:a)std::cin>>x;
    std::deque<int> candidates;
    bool first=true;
    for(int i=0;i<n;++i) {
        while(!candidates.empty()&&candidates.front()<=i-k) candidates.pop_front();
        while(!candidates.empty()&&a[candidates.back()]<=a[i]) candidates.pop_back();
        candidates.push_back(i); // 同值保留较新的，过期更晚。
        if(i>=k-1) {
            if(!first)std::cout<<' ';
            first=false;
            std::cout<<a[candidates.front()];
        }
    }
    std::cout<<'\n';
}
