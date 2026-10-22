// offline_connectivity：网络故障回放
// 来源：原创教学题
// 题面、范围、样例和训练步骤见同目录 offline_connectivity.md
// 复杂度：时间 O((n+m+q)α(n))，空间 O(n+m+q)

#include <algorithm>
#include <iostream>
#include <numeric>
#include <utility>
#include <vector>
int main() {
    int n,m,q;if(!(std::cin>>n>>m>>q))return 0;
    std::vector<std::pair<int,int>>edges(m+1);
    for(int i=1;i<=m;++i)std::cin>>edges[i].first>>edges[i].second;
    std::vector<int>removed(q),answer(q),parent(n+1),size(n+1,1);
    std::vector<char>deleted(m+1,false);
    for(auto&x:removed){std::cin>>x;deleted[x]=true;}
    std::iota(parent.begin(),parent.end(),0);
    auto find=[&](int x){while(x!=parent[x]){parent[x]=parent[parent[x]];x=parent[x];}return x;};
    int components=n;
    auto unite=[&](int u,int v){
        u=find(u);v=find(v);if(u==v)return;
        if(size[u]<size[v])std::swap(u,v);
        parent[v]=u;size[u]+=size[v];--components;
    };
    for(int i=1;i<=m;++i)if(!deleted[i])unite(edges[i].first,edges[i].second);
    for(int i=q-1;i>=0;--i) {
        answer[i]=components; // 此时正处在正向删除第 i 条边之后。
        auto [u,v]=edges[removed[i]];unite(u,v);
    }
    for(int value:answer)std::cout<<value<<'\n';
}
