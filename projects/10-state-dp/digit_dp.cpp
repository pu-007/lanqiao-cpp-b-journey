// digit_dp：超大数字筛选器
// 来源：原创教学题
// 题面、范围、样例和训练步骤见同目录 digit_dp.md
// 复杂度：时间 O(位数×10)，空间 O(位数)

#include <cstring>
#include <functional>
#include <iostream>
#include <string>
int main() {
    std::string bound;if(!(std::cin>>bound))return 0;
    long long memo[20];std::memset(memo,-1,sizeof memo);
    std::function<long long(int,bool)>dfs=[&](int pos,bool tight)->long long {
        if(pos==static_cast<int>(bound.size()))return 1;
        if(!tight&&memo[pos]!=-1)return memo[pos];
        int upper=tight?bound[pos]-'0':9;
        long long answer=0;
        for(int digit=0;digit<=upper;++digit) {
            if(digit==4)continue;
            answer+=dfs(pos+1,tight&&digit==upper);
        }
        // 已低于上界时，后缀只依赖 pos，才能复用缓存。
        if(!tight)memo[pos]=answer;
        return answer;
    };
    std::cout<<dfs(0,true)<<'\n';
}
