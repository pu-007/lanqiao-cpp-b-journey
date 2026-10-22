// kmp：日志模式匹配
// 来源：原创教学题
// 题面、范围、样例和训练步骤见同目录 kmp.md
// 复杂度：时间 O(n+m)，空间 O(m)

#include <iostream>
#include <string>
#include <vector>
int main() {
    std::string text,pattern;if(!(std::cin>>text>>pattern))return 0;
    int m=static_cast<int>(pattern.size());
    std::vector<int> pi(m,0);
    for(int i=1,j=0;i<m;++i) {
        while(j>0&&pattern[i]!=pattern[j]) j=pi[j-1];
        if(pattern[i]==pattern[j]) ++j;
        pi[i]=j;
    }
    long long count=0;int j=0;
    for(char c:text) {
        while(j>0&&c!=pattern[j]) j=pi[j-1]; // 文本位置不后退。
        if(c==pattern[j]) ++j;
        if(j==m) {
            ++count;
            j=pi[j-1]; // aaa 在 aaaaa 里有 3 次，不能直接清零。
        }
    }
    std::cout<<count<<'\n';
}
