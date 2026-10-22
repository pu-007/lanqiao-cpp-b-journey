// brackets：括号检查器
// 来源：原创教学题
// 题面、范围、样例和训练步骤见同目录 brackets.md
// 复杂度：时间 O(n)，空间 O(n)

#include <iostream>
#include <stack>
#include <string>
int main() {
    std::string s;
    std::getline(std::cin, s);
    std::stack<char> pending;
    for (char c : s) {
        if (c == '(' || c == '[' || c == '{') pending.push(c);
        else {
            char expected = (c == ')' ? '(' : c == ']' ? '[' : '{');
            // || 短路求值：empty 为真时，不会执行非法的 top()。
            if (pending.empty() || pending.top() != expected) {
                std::cout << "NO\n";
                return 0;
            }
            pending.pop(); // pop 不返回被删除的值。
        }
    }
    // 全部右括号合法，也可能还有多余左括号。
    std::cout << (pending.empty() ? "YES\n" : "NO\n");
}
