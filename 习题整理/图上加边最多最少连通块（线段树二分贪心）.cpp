/*
    input   ouput
    5 5
    1 1 2
    2 1     3 3
    1 1 3
    2 1     2 3
    2 3     1 2
*/
ll com[MAXN];
int n;
class SEG { public:
    struct node {
        int l, r, cnt, sum;
        ll edge;
    } T[MAXN << 2];
    inline void push_up(int rt) {
        T[rt].cnt = T[rt << 1].cnt + T[rt << 1 | 1].cnt;
        T[rt].edge = T[rt << 1].edge + T[rt << 1 | 1].edge;
        T[rt].sum = T[rt << 1].sum + T[rt << 1 | 1].sum;
    }

    void build(int rt, int l, int r) {
        T[rt].l = l, T[rt].r = r;
        if (l == r) {
            if (l == 1) {
                T[rt].edge = com[l] * n, T[rt].cnt = n, T[rt].sum = n;
            } else {
                T[rt].edge = 0, T[rt].cnt = 0, T[rt].sum = 0;
            }
            return;
        }
        int mid = (l + r) >> 1;
        build(rt << 1, l, mid), build(rt << 1 | 1, mid + 1, r);
        push_up(rt);
    }
    void update(int rt, int pos, int v) {
        if (T[rt].l == T[rt].r) {
            T[rt].cnt += v;
            T[rt].sum += v * T[rt].l;
            T[rt].edge += com[T[rt].l] * v;
            return;
        }
        int mid = (T[rt].l + T[rt].r) >> 1;
        if (pos <= mid) update(rt << 1, pos, v);
        else update(rt << 1 | 1, pos, v);
        push_up(rt);
    }
    int query(int rt, ll k, int vs, ll vk) {    // 二分查找
        if (T[rt].l == T[rt].r) {
            int L = 0, R = T[rt].cnt;
            while (L < R) {
                int mid = (L + R) >> 1;
                if (com[mid * T[rt].l + vs] - mid * com[T[rt].l] - vk < k) L = mid + 1;
                else R = mid;
            }
            return L;
        }
        if (com[vs + T[rt << 1 | 1].sum] - T[rt << 1 | 1].edge >= k) return query(rt << 1 | 1, k, vs, vk);
        else return T[rt << 1 | 1].cnt + query(rt << 1, k, vs + T[rt << 1 | 1].sum, vk + T[rt << 1 | 1].edge);
    }
} tree;
int cnt[MAXN];  ll edge[MAXN];
int fa[MAXN];
int find(int x) {
    if (fa[x] == x) return x;
    else return fa[x] = find(fa[x]);
}
int main() {
    int T;  scanf("%d", &T);
    for (int i = 1; i < MAXN; i++) com[i] = (ll) i * (i - 1) / 2;
    while (T--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) fa[i] = i;
        for (int i = 1; i <= n; i++) cnt[i] = 1, edge[i] = 0;
        tree.build(1, 1, n);
        int q;  scanf("%d", &q);
        int blocks = n;
        ll free = 0;
        while (q--) {
            int opt;    scanf("%d", &opt);
            if (opt == 1) {
                int x, y;   scanf("%d%d", &x, &y);
                int fx = find(x), fy = find(y);
                if (fx == fy) {
                    edge[fx]++; free--;
                } else {
                    blocks--;
                    free -= com[cnt[fx]] - edge[fx];
                    free -= com[cnt[fy]] - edge[fy];
                    tree.update(1, cnt[fx], -1);
                    tree.update(1, cnt[fy], -1);
                    fa[fx] = fy;
                    cnt[fy] += cnt[fx];
                    edge[fy] += edge[fx] + 1;
                    free += com[cnt[fy]] - edge[fy];
                    tree.update(1, cnt[fy], 1);
                }
            } else {
                ll k;
                scanf("%lld", &k);
                printf("%lld ", max(1ll, (ll) blocks - k)); // minn
                if (free >= k) printf("%d\n", blocks);  // maxx
                else {
                    k -= free;
                    int tmp = tree.query(1, k, 0, 0);
                    printf("%d\n", blocks - tmp + 1);   // maxx
                }
            }
        }
    }
}