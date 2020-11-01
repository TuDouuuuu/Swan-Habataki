class HJT_01 {  public:
    int ch[MAXN * 70][2], sum[MAXN * 70];
    int tot;
    int update(int rt, int v, int dep) {
        int nrt = ++tot, tmp = nrt;
        for (int i = 30; i >= 0; i--) {
            sum[nrt] = sum[rt] + 1;  // 在原版本的基础上更新
            if ((v & (1 << i)) == 0) {
                if (!ch[nrt][0]) ch[nrt][0] = ++tot;
                ch[nrt][1] = ch[rt][1];
                nrt = ch[nrt][0];
                rt = ch[rt][0];
            } else {
                if (!ch[nrt][1]) ch[nrt][1] = ++tot;
                ch[nrt][0] = ch[rt][0];
                nrt = ch[nrt][1];
                rt = ch[rt][1];
            }
        }
        sum[nrt] = sum[rt] + 1;
        return tmp;
    }
    int query(int lrt, int rrt, int v) {
        int ans = 0;
        for (int i = 30; i >= 0; i--) {
            int t = ((v & (1 << i)) ? 1 : 0);
            if (sum[ch[rrt][!t]] - sum[ch[lrt][!t]]) {
                ans += (1 << i);
                lrt = ch[lrt][!t], rrt = ch[rrt][!t];
            } else lrt = ch[lrt][t], rrt = ch[rrt][t];
        }
        return ans;
    }
} tree;
int a[MAXN], pre[MAXN], root[MAXN];
char opt[5];
int main() {
    int n, m;   scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]), pre[i] = pre[i - 1] ^ a[i];
    int root_cnt = n;
    root[0] = 0;
    for (int i = 1; i <= n; i++) root[i] = tree.update(root[i - 1], pre[i], 30);
    while (m--) {
        scanf("%s", opt + 1);
        if (opt[1] == 'A') {
            root_cnt++;
            scanf("%d", &a[root_cnt]);
            pre[root_cnt] = pre[root_cnt - 1] ^ a[root_cnt];
            root[root_cnt] = tree.update(root[root_cnt - 1], pre[root_cnt], 30);
        } else {
            int l, r, x;
            scanf("%d%d%d", &l, &r, &x);
            l--, r--;
            if (l == r && l == 0) printf("%d\n", pre[root_cnt] ^ x);
            else printf("%d\n", tree.query(root[max(0, l - 1)], root[r], x ^ pre[root_cnt]));
        }
    }
}