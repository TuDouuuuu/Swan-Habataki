/*
	input				output
	9					3
	1 2 2 2 1 1 2 2 2
	10					0
	1 2 3 4 1 2 3 1 2 3
	12					1
	1 2 3 4 3 4 2 1 3 4 2 1
*/
int arr[MAXN];
vector<int> vec[MAXN];
struct node {
    int l, r, v;
    node(int _l = 0, int _r = 0, int _v = 0) : l(_l), r(_r), v(_v) {}
};

class SEG { public:
    struct node {
        int l, r, mx, cnt;
    } T[MAXN << 2];
    int lazy[MAXN << 2];

    void build(int rt, int l, int r) {
        T[rt].l = l, T[rt].r = r, T[rt].mx = 0, T[rt].cnt = r - l;
        if (l + 1 == r) {
            T[rt << 1].l = T[rt << 1].r = T[rt << 1].mx = T[rt << 1].cnt = 0;
            T[rt << 1 | 1].l = T[rt << 1 | 1].r = T[rt << 1 | 1].mx = T[rt << 1 | 1].cnt = 0;
            return;
        }
        int mid = (l + r) >> 1;
        build(rt << 1, l, mid);
        build(rt << 1 | 1, mid, r);
    }

    inline void push_up(int rt) {
        if (T[rt << 1].mx > T[rt << 1 | 1].mx) T[rt].mx = T[rt << 1].mx, T[rt].cnt = T[rt << 1].cnt;
        else if (T[rt << 1].mx < T[rt << 1 | 1].mx) T[rt].mx = T[rt << 1 | 1].mx, T[rt].cnt = T[rt << 1 | 1].cnt;
        else T[rt].mx = T[rt << 1].mx, T[rt].cnt = T[rt << 1].cnt + T[rt << 1 | 1].cnt;
    }

    inline void push_down(int rt) {
        if (lazy[rt]) {
            T[rt << 1].mx += lazy[rt], lazy[rt << 1] += lazy[rt];
            T[rt << 1 | 1].mx += lazy[rt], lazy[rt << 1 | 1] += lazy[rt];
            lazy[rt] = 0;
        }
    }

    void update(int rt, int L, int R, int val) {
        if (L <= T[rt].l && R >= T[rt].r) {
            T[rt].mx += val, lazy[rt] += val;
            return;
        }
        if (L >= T[rt].r || R <= T[rt].l)  return ;
        push_down(rt);
        int mid = (T[rt].l + T[rt].r) >> 1;
        if (L <= mid) update(rt << 1, L, R, val);
        if (R >= mid) update(rt << 1 | 1, L, R, val);
        push_up(rt);
    }
} tree;

vector<node> event[MAXN];
void add(int l1, int l2, int r1, int r2) {
    event[l1].push_back(node(r1, r2, 1));
    event[l2].push_back(node(r1, r2, -1));
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &arr[i]);
        vec[arr[i]].push_back(i);
    }
    for (int x = 1; x <= n; x++) {
        int sz = SZ(vec[x]);
        for (int i = 0; i <= sz; i++) {
            add(i == 0 ? 1 : vec[x][i - 1] + 1, i == sz ? n + 2 : vec[x][i] + 1,
                i == 0 ? 1 : vec[x][i - 1] + 1, i == sz ? n + 2 : vec[x][i] + 1);
        }
        for (int i = 0; i <= sz - 3; i++) {
            add(i == 0 ? 1 : vec[x][i - 1] + 1, vec[x][i] + 1,
                vec[x][i + 2] + 1, i + 3 == sz ? n + 2 : vec[x][i + 3] + 1);
        }
    }
    tree.build(1, 1, n + 2);
    ll res = 0;
    for (int l = 1; l <= n; l++) {  // enum left
        for (auto e: event[l]) {
            int el = e.l, er = e.r, ev = e.v;
            tree.update(1, el, er, ev);
        }
        tree.update(1, l, l+1, -1);
        if (tree.T[1].mx == n) {
            res += tree.T[1].cnt;
        }
    }
    printf("%lld\n", res);
}
