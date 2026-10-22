// fenwick：实时训练报表
// 来源：原创教学题
// 题面、范围、样例和训练步骤见同目录 fenwick.md
// 复杂度：时间 O((n+q) log n)，空间 O(n)

#include <iostream>
#include <vector>
class Fenwick {
    int n; std::vector<long long> tree;
public:
    explicit Fenwick(int size):n(size),tree(size+1,0){}
    void add(int i,long long delta) {
        for(;i<=n;i+=i&-i) tree[i]+=delta; // 跳到管理更大区间的父节点。
    }
    long long prefix(int i) const {
        long long result=0;
        for(;i>0;i-=i&-i) result+=tree[i]; // 每次移除最后一个互不重叠块。
        return result;
    }
};
int main() {
    std::ios::sync_with_stdio(false); std::cin.tie(nullptr);
    int n,q; if(!(std::cin>>n>>q)) return 0;
    Fenwick bit(n);
    for(int i=1;i<=n;++i) {long long x;std::cin>>x;bit.add(i,x);}
    while(q--) {
        int op;std::cin>>op;
        if(op==1) {int i;long long d;std::cin>>i>>d;bit.add(i,d);}
        else {int l,r;std::cin>>l>>r;std::cout<<bit.prefix(r)-bit.prefix(l-1)<<'\n';}
    }
}
