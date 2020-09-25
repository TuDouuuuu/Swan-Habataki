class SEG { public:
    int ch[MAXM][2];
    ll sum[MAXM];
#define lson ch[rt][0]
#define rson ch[rt][1]
    int pool[MAXM], pool_cnt, cnt;
    int New() { // recycle
        return pool_cnt ? pool[pool_cnt--] : ++cnt;
    }
    void Del(int rt) {
        pool[++pool_cnt] = rt;
        ch[rt][0] = ch[rt][1] = sum[rt] = 0;
    }
    inline void push_up(int rt) {
        sum[rt] = sum[lson] + sum[rson];
    }
    int change(int rt, int pos, int v, int be, int en) {
        if (!rt) rt = New();
        if (be == en) {
            sum[rt] += (ll) v;
            return rt;
        }
        int mid = (be + en) >> 1;
        if (pos <= mid) lson = change(lson, pos, v, be, mid);
        else
            rson = change(rson, pos, v, mid + 1, en);
        push_up(rt);
        return rt;
    }
    ll query_sum(int rt, int L, int R, int be, int en) {
        if (!rt) return 0;
        if (L <= be && R >= en) return sum[rt];
        int mid = (be + en) >> 1;
        ll ans = 0;
        if (L <= mid) ans += query_sum(lson, L, R, be, mid);
        if (R > mid) ans += query_sum(rson, L, R, mid + 1, en);
        return ans;
    }
    int Kth(int rt, int be, int en, int k) {
        if (be == en) return be;
        int mid = (be + en) >> 1;
        int ans = -1;
        if (sum[ch[rt][0]] >= k) ans = Kth(lson, be, mid, k);
        else ans = Kth(rson, mid + 1, en, k - sum[ch[rt][0]]);
        return ans;
    }
    int merge(int x, int y, int be, int en) {
        if (!x || !y) return x + y;
        if (be == en) {
            sum[x] += sum[y];
            return x;
        }
        int mid = (be + en) >> 1;
        ch[x][0] = merge(ch[x][0], ch[y][0], be, mid);
        ch[x][1] = merge(ch[x][1], ch[y][1], mid + 1, en);
        push_up(x);
        Del(y);
        return x;
    }
    void split(int &rt1, int &rt2, int L, int R, int be, int en) {
        if (en < L || R < be) return;
        if (!rt1) return;
        if (L <= be && en <= R) {
            rt2 = rt1, rt1 = 0;
            return;
        }
        if (!rt2) rt2 = New();
        int mid = (be + en) >> 1;
        split(ch[rt1][0], ch[rt2][0], L, R, be, mid);
        split(ch[rt1][1], ch[rt2][1], L, R, mid + 1, en);
        push_up(rt1), push_up(rt2);
    }
} tree;

int root[MAXN];
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    int max_n_m = max(n, m);
    for (int i = 1; i <= n; i++) {
        int x;
        scanf("%d", &x);
        root[1] = tree.change(root[1], i, x, 1, max_n_m);
    }
    int id = 1;
    while (m--) {
        int opt;
        scanf("%d", &opt);
        if (opt == 0) { // 将可重集p中>=x且<=y的值放入一个新的可重集中
            int p, x, y;
            scanf("%d%d%d", &p, &x, &y);
            tree.split(root[p], root[++id], x, y, 1, max_n_m);
        } else if (opt == 1) {  // 将可重集t中的数放入可重集p，且清空可重集t
            int p, t;
            scanf("%d%d", &p, &t);  // 数据保证在此后的操作中不会出现可重集t
            root[p] = tree.merge(root[p], root[t], 1, max_n_m);
        } else if (opt == 2) {  // 在p这个可重集中加入x个数字q
            int p, x, q;
            scanf("%d%d%d", &p, &x, &q);
            root[p] = tree.change(root[p], q, x, 1, max_n_m);
        } else if (opt == 3) {  // 查询可重集p中大>=x且<=y的值的个数
            int p, x, y;
            scanf("%d%d%d", &p, &x, &y);
            printf("%lld\n", tree.query_sum(root[p], x, y, 1, max_n_m));
        } else {  // 查询在p这个可重集中第k小的数，不存在时输出-1
            int p, k;
            scanf("%d%d", &p, &k);
            if (tree.sum[root[p]] < k) {
                printf("-1\n");
            } else printf("%d\n", tree.Kth(root[p], 1, max_n_m, k));
        }
    }
}
