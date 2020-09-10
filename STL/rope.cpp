#include <bits/stdc++.h>
#include <bits/extc++.h>

using namespace std;
using namespace __gnu_cxx;
rope<char> tree;
inline void read_str(char *s, int len) {    // 读入长度为len的字符串
    s[len] = '\0';
    len--;
    for (int i = 0; i <= len; i++) {
        s[i] = '\0';
        while (s[i] < 32 || 126 < s[i]) s[i] = getchar();
    }
}

inline void read_int(int &x) {
    x = 0;
    char ch;
    while (!isdigit(ch = getchar()));
    x = ch - '0';
    while (isdigit(ch = getchar())) x = x * 10 + ch - '0';
}
const int MAXN = 2e6 + 5;
char word[MAXN];

int main() {
    int T;
    int now = 0;
    scanf("%d", &T);
    while (T--) {
        int opt = '1', x;
        while (!isalpha(opt = getchar()));
        while (isalpha(getchar()));
        // 格式:Move k
        // 将光标移动到第k个字符之后，如果k=0，将光标移到文本开头
        if (opt == 'M') read_int(now); 
        // Insert n s
        // 在光标处插入长度为n的字符串s，光标位置不变n>=1
        else if (opt == 'I') {
            read_int(x);
            read_str(word, x);
            tree.insert(now, word);
        } 
        // Delete n
        // 删除光标后的n个字符，光标位置不变，n>=1
        else if (opt == 'D') {
            read_int(x);
            tree.erase(now, x);
        } 
        // Get n
        // 输出光标后的n个字符，光标位置不变，n>=1
        else if (opt == 'G') {
            read_int(x);
            x--;
            for (int i = now; i <= now + x; i++) printf("%c", tree[i]);
            printf("\n");
        } else if (opt == 'P') now--;   // 光标前移
        else now++; //光标后移
    }
}