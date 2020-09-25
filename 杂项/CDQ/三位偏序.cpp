class TREE { public:
    int T[MAXN], n;
    inline int lowbit(int x) { return x & (-x); }
    void add(int pos, int val) {
        while (pos <= n) {
            T[pos] += val; pos += lowbit(pos);
        }
    }
    int query(int pos) {
        int ans = 0;
        while (pos) {
            ans += T[pos]; pos -= lowbit(pos);
        }
        return ans;
    }
} tree;

struct node {
    int a, b, c;
    int cnt, ans;
    bool operator==(const node &tb) const {
        if (a == tb.a && b == tb.b && c == tb.c) return 1;
        else return 0;
    }
} p1[MAXN], p2[MAXN];

void cdq(int l, int r) {
    if (l == r) return;
    int mid = (l + r) >> 1;
    cdq(l, mid), cdq(mid + 1, r);
    sort(p2 + l, p2 + mid + 1, [&](const node &x, const node &y) {
        if (x.b != y.b) return x.b < y.b;
        else return x.c < y.c;
    });
    sort(p2 + mid + 1, p2 + r + 1, [&](const node &x, const node &y) {
        if (x.b != y.b) return x.b < y.b;
        else return x.c < y.c;
    });
    int j = l;
    for (int i = mid + 1; i <= r; i++) {
        while (p2[i].b >= p2[j].b && j <= mid) {
            tree.add(p2[j].c, p2[j].cnt);
            j++;
        }
        p2[i].ans += tree.query(p2[i].c);
    }
    for (int i = l; i < j; i++) tree.add(p2[i].c, -p2[i].cnt);
}

int res[MAXN];
int main() {
    int n, k; scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) scanf("%d%d%d", &p1[i].a, &p1[i].b, &p1[i].c);
    p1[n+1].a = p1[n+1].b = p1[n+1].c = 0;
    sort(p1 + 1, p1 + 1 + n, [&](const node &x, const node &y) {
        if (x.a != y.a) return x.a < y.a;
        if (x.b != y.b) return x.b < y.b;
        return x.c < y.c;
    });
    int tot = 0, m = 0;
    for (int i = 1; i <= n; i++) {
        tot++;
        if (p1[i].a != p1[i + 1].a || p1[i].b != p1[i + 1].b || p1[i].c != p1[i + 1].c) {
            m++;
            p2[m].a = p1[i].a, p2[m].b = p1[i].b, p2[m].c = p1[i].c, p2[m].cnt = tot;
            tot = 0;
        }
    }
    tree.n = k;
    cdq(1, m);
    for (int i = 1; i <= m; i++) res[p2[i].ans + p2[i].cnt -1] += p2[i].cnt;
    for (int d = 0; d < n; d++) printf("%d\n", res[d]); // 输出每个f(i) = d的数量
}