// p[i]存放[1, n]数据
class cartesian {
    int stk[MAXN], lson[MAXN], rson[MAXN];
    void build() {
        int tmp = 0, x;
        for (int i = 1; i <= n; i++) {
            x = tmp;
            while (x && p[stk[x]] > p[i]) x--;
            if (x) rson[stk[x]] = i;
            if (x < tmp) lson[i] = stk[x + 1];
            stk[++x] = i;
            tmp = x;
        }
    }
} ;