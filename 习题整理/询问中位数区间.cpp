class HJT { public:
    struct node {
        int ch[2];
        int pre, suf, sum;
        node() {
            ch[0] = ch[1] = pre = suf = sum = 0;
        }
    } T[MAXN * 70];
    int tot;
#define lson T[rt].ch[0]
#define rson T[rt].ch[1]
    inline void push_up(int rt) {
        T[rt].sum = T[lson].sum + T[rson].sum;
        T[rt].pre = max(T[lson].pre, T[lson].sum + T[rson].pre);
        T[rt].suf = max(T[rson].suf, T[rson].sum + T[lson].suf);
    }
    int build(int l, int r) {
        int nrt = ++tot;
        if (l == r) {
            T[nrt].sum = T[nrt].pre = T[nrt].suf = 1;
            return nrt;
        }
        int mid = (l + r) >> 1;
        T[nrt].ch[0] = build(l, mid), T[nrt].ch[1] = build(mid + 1, r);
        push_up(nrt);
        return nrt;
    }
    int update(int rt, int pos, int v, int be, int en) {
        int nrt = ++tot;
        if (be == en) {
            T[nrt].sum = T[nrt].pre = T[nrt].suf = v;
            return nrt;
        }
        int mid = (be + en) >> 1;
        if (pos <= mid) {
            T[nrt].ch[0] = update(lson, pos, v, be, mid);
            T[nrt].ch[1] = rson;
        } else {
            T[nrt].ch[0] = lson;
            T[nrt].ch[1] = update(rson, pos, v, mid + 1, en);
        }
        push_up(nrt);
        return nrt;
    }
    int query_sum(int rt, int L, int R, int be, int en) {
        if (L <= be && en <= R) return T[rt].sum;
        int mid = (be + en) >> 1;
        int ans = 0;
        if (L <= mid) ans += query_sum(lson, L, R, be, mid);
        if (R > mid) ans += query_sum(rson, L, R, mid + 1, en);
        return ans;
    }
    node query_pre(int rt, int L, int R, int be, int en) {
        if (L <= be && en <= R) return T[rt];
        int mid = (be + en) >> 1;
        if (R <= mid) return query_pre(lson, L, R, be, mid);
        else if (L > mid) return query_pre(rson, L, R, mid + 1, en);
        else {
            node ans;
            node ansl = query_pre(lson, L, R, be, mid);
            node ansr = query_pre(rson, L, R, mid + 1, en);
            ans.sum = ansl.sum + ansr.sum;
            ans.pre = max(ansl.pre, ansl.sum + ansr.pre);
            return ans;

        }
    }
    node query_suf(int rt, int L, int R, int be, int en) {
        if (L <= be && en <= R) return T[rt];
        int mid = (be + en) >> 1;
        if (R <= mid) return query_suf(lson, L, R, be, mid);
        else if (L > mid) return query_suf(rson, L, R, mid + 1, en);
        else {
            node ans;
            node ansl = query_suf(lson, L, R, be, mid);
            node ansr = query_suf(rson, L, R, mid + 1, en);
            ans.sum = ansl.sum + ansr.sum;
            ans.suf = max(ansr.suf, ansr.sum + ansl.suf);
            return ans;
        }
    }
} tree;

int a[MAXN], root[MAXN];
vector<int> vec[MAXN];

int n;
bool check(int mid, const vector<int> &q) {
    int sum = 0;
    if (q[1] + 1 <= q[2] - 1) sum = tree.query_sum(root[mid - 1], q[1] + 1, q[2] - 1, 1, n);
    sum += tree.query_suf(root[mid - 1], q[0], q[1], 1, n).suf;
    sum += tree.query_pre(root[mid - 1], q[2], q[3], 1, n).pre;
    if (sum >= 0) return 1;
    else return 0;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        Discrete::insert(a[i]);
    }
    Discrete::init();
    for (int i = 1; i <= n; i++) a[i] = val2id(a[i]);
    for (int i = 1; i <= n; i++) {
        vec[a[i]].pb(i);
    }
    root[0] = tree.build(1, n);
    for (int i = 1; i <= Discrete::blen; i++) {
        root[i] = root[i - 1];
        for (auto e: vec[i]) {
            root[i] = tree.update(root[i], e, -1, 1, n);
        }
    }
    int m; scanf("%d", &m);
    int lastans = 0;
    while (m--) {
        vector<int> q(4);
        scanf("%d%d%d%d", &q[0], &q[1], &q[2], &q[3]);
        for (int i = 0; i < 4; i++) q[i] = (q[i] + lastans) % n + 1;
        sort(q.begin(), q.end());
        int L = 1, R = Discrete::blen;
        while (L < R) {
            int mid = (L + R + 1) >> 1;
            if (check(mid, q)) L = mid;
            else R = mid - 1;
        }
        lastans = id2val(L);
        printf("%d\n", lastans);
    }
}