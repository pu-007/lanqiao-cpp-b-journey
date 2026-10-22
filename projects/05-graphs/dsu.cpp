// dsu：好友圈连通性
// 来源：原创教学题
// 题面、范围、样例和训练步骤见同目录 dsu.md
// 复杂度：均摊时间 O((n+q)α(n))，空间 O(n)

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
class DSU {
    std::vector<int> parent,size;
public:
    explicit DSU(int n):parent(n+1),size(n+1,1) {
        std::iota(parent.begin(),parent.end(),0);
    }
    int find(int x) {
        if (parent[x]==x) return x;
        return parent[x]=find(parent[x]); // 回程时压缩路径。
    }
    bool unite(int a,int b) {
        a=find(a); b=find(b);
        if (a==b) return false; // 已连通，不重复累加集合大小。
        if (size[a]<size[b]) std::swap(a,b);
        parent[b]=a; size[a]+=size[b];
        return true;
    }
};
int main() {
    int n,q; if (!(std::cin >> n >> q)) return 0;
    DSU dsu(n);
    while(q--) {
        int op,u,v; std::cin >> op >> u >> v;
        if (op==1) dsu.unite(u,v);
        else std::cout << (dsu.find(u)==dsu.find(v)?"YES\n":"NO\n");
    }
}
