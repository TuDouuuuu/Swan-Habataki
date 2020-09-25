int pos[MAXN];  // +1后对应为所建的fail树上的点
class Palindrome_Tree { public:
    struct node {
        int ch[MAXC], fail, len, num;   // num：以该位置结尾的回文子串个数
    } T[MAXN];
    int las, tot, c[MAXN];
    inline int get_fail(int x, int pos) {
        while (c[pos - T[x].len - 1] != c[pos]) {
            x = T[x].fail;
        }
        return x;
    }
    void init() { // 传入字符串长度
        memset(T[0].ch, 0, sizeof(T[0].ch));
        memset(T[1].ch, 0, sizeof(T[1].ch));
        T[0].len = 0, T[1].len = -1;
        T[0].fail = 1, T[1].fail = 0;
        las = 0, tot = 1;
    }
    void insert(char s[], int len) {  // call: insert(str, strlen(str+1));
        c[0] = -1;
        for (int i = 1; i <= len; i++) {
            c[i] = s[i] - 'a';
            int p = get_fail(las, i);
            if (!T[p].ch[c[i]]) {
                T[++tot].len = T[p].len + 2;
                memset(T[tot].ch, 0, sizeof(T[tot].ch));
                int u = get_fail(T[p].fail, i);
                T[tot].fail = T[u].ch[c[i]];
                T[tol].num = T[T[tol].fail].num + 1;
                T[p].ch[c[i]] = tot;
            }
            las = T[p].ch[c[i]];
            pos[i] = las;
        }
    }
    struct Edge {
        int to, nex;
    } e[MAXN << 1];
    int head[MAXN], tol;
    int len[MAXN];
    void addEdge(int u, int v) {
        e[tol].to = v, e[tol].nex = head[u], head[u] = tol, tol++;
    }
    void build() { // build tree
        tol = 0;
        for (int i = 0; i <= tot; i++) head[i+1] = -1;
        for (int i = 1; i <= tot; i++) addEdge(T[i].fail + 1, i + 1);
        for (int i = 0; i <= tot; i++) len[i + 1] = T[i].len;
    }
} tree;

char str[MAXN];
int main() {
    scanf("%s", str + 1);
    tree.init();
    tree.insert(str, strlen(str + 1));
    tree.build();
    for (int i = 1; i <= len; i++) printf("%d ", pos[i]+1); // fail树上对应位置
}
