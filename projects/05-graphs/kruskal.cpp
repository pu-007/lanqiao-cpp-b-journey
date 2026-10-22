// kruskal：校园网络铺线
// 来源：原创教学题
// 题面、范围、样例和训练步骤见同目录 kruskal.md
// 复杂度：时间 O(m log m+n)，空间 O(n+m)

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
struct Edge {int u,v; long long w;};
int main() {
    int n,m; if(!(std::cin>>n>>m)) return 0;
    std::vector<Edge> edges(m);
    for(auto& e:edges) std::cin>>e.u>>e.v>>e.w;
    std::sort(edges.begin(),edges.end(),[](const Edge& a,const Edge& b){return a.w<b.w;});
    std::vector<int> parent(n+1),size(n+1,1);
    std::iota(parent.begin(),parent.end(),0);
    auto find=[&](int x) {
        while(x!=parent[x]) {parent[x]=parent[parent[x]]; x=parent[x];}
        return x;
    };
    long long cost=0; int chosen=0;
    for(const auto& e:edges) {
        int a=find(e.u),b=find(e.v);
        if(a==b) continue; // 同一连通块内加边会形成环（自环同样跳过）。
        if(size[a]<size[b]) std::swap(a,b);
        parent[b]=a; size[a]+=size[b];
        cost+=e.w; ++chosen;
    }
    // n=1 时，0 条边即可连通，答案自然是 0。
    std::cout << (chosen==n-1?cost:-1) << '\n';
}
