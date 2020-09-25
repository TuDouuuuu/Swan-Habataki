class HJT { public:
    int query(int rt, int L, int R, int be, int en) {
        if (L <= be && en <= R) return sum[rt];
        int mid = (be + en) >> 1;
        int ans = 0;
        if (L <= mid) ans += query(ch[rt][0], L, R, be, mid);
        if (R > mid) ans += query(ch[rt][1], L, R, mid + 1, en);
        return ans;
    }
} tree;
int val[MAXN], root[MAXN];
unordered_map<int, int> pre;

int main() {
    int n; scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &val[i]);
    root[0] = 0;
    for (int i = 1; i <= n; i++) {
        if (pre[val[i]]) {
            int tmp = tree.change(root[i - 1], pre[val[i]], -1, 1, n);
            root[i] = tree.change(tmp, i, 1, 1, n);
        } else {
            root[i] = tree.change(root[i - 1], i, 1, 1, n);
        }
        pre[val[i]] = i;
    }
    int q; scanf("%d", &q);
    while (q--) {
        int l, r;
        scanf("%d%d", &l, &r);
        printf("%d\n", tree.query(root[r], l, r, 1, n));
    }
}
