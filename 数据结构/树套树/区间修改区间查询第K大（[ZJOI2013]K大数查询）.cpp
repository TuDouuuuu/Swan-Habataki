/*
  树状数组套主席套线段树
  可重集的并是不去除重复元素的，如{1,1,4} & {5,1,4}={1,1,4,5,1,4}
  input     output
  2 5
  1 1 2 1
  1 1 2 2
  2 1 1 2   1
  2 1 1 1   2
  2 1 2 3   1
*/
class BIT { public:
    class SEG { public:
        int tot_rt, ch[MAXN * 400][2]; ll lazy[MAXN * 400], sum[MAXN * 400];
#define lson ch[rt][0]
#define rson ch[rt][1]
        inline void push_up(int rt) {
            sum[rt] = sum[lson] + sum[rson];
        }
        inline void push_down(int rt, int len_left, int len_right) {
            if (lazy[rt]) {
                if (!ch[rt][0]) ch[rt][0] = ++tot_rt;
                if (!ch[rt][1]) ch[rt][1] = ++tot_rt;
                sum[lson] += lazy[rt] * len_left, sum[rson] += lazy[rt] * len_right;
                lazy[lson] += lazy[rt], lazy[rson] += lazy[rt];
                lazy[rt] = 0;
            }
        }
        int change(int rt, int L, int R, int val, int be, int en) {
            if (!rt) rt = ++tot_rt;
            if (L <= be && R >= en) {
                sum[rt] += (ll) (en - be + 1);
                lazy[rt] += (ll) val;
                return rt;
            }
            int mid = (be + en) >> 1;
            push_down(rt, mid - be + 1, en - (mid + 1) + 1);
            if (L <= mid) lson = change(lson, L, R, val, be, mid);
            if (R > mid) rson = change(rson, L, R, val, mid + 1, en);
            push_up(rt);
            return rt;
        }
        ll query(int rt, int L, int R, int be, int en) {
            if (!rt) return 0;
            if (L <= be && R >= en) return sum[rt];
            int mid = (be + en) >> 1;
            push_down(rt, mid - be + 1, en - (mid + 1) + 1);
            ll ans = 0;
            if (L <= mid) ans += query(lson, L, R, be, mid);
            if (R > mid) ans += query(rson, L, R, mid + 1, en);
            return ans;
        }
    } seg;

    int n, c_len, root[MAXN];
    void init(int _n, int _c_len) {
        c_len = _c_len, n = _n;
        for (int i = 1; i <= c_len; i++) root[i] = i;
        seg.tot_rt = _c_len;
    }
    inline int lowbit(int x) { return x & (-x); }
    inline int log(int x) { return 1ll << (int) (log2(x)); }
    void insert(int l, int r, int c) {
        for (int i = c_len - c + 1; i <= c_len; i += lowbit(i)) seg.change(root[i], l, r, 1, 1, n);
    }
    int query(int l, int r, ll k) {
        int ans = 0;
        ll sum = 0;
        for (int i = log(c_len); i != 0; i >>= 1) {
            if (ans + i > c_len) continue;
            ll tmp = seg.query(root[ans + i], l, r, 1, n) + sum;
            if (tmp < k) ans += i, sum = tmp;
        }
        ans++;
        return c_len - ans + 1;
    }
} tree;

int opt[MAXN], l[MAXN], r[MAXN]; ll c[MAXN];
int main() {
    int n, m; scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        scanf("%d%d%d%lld", &opt[i], &l[i], &r[i], &c[i]);
        if (opt[i] == 1) Discrete::push(c[i]);
    }
    Discrete::init(); // 离散化
    int c_len = Discrete::blen;
    tree.init(n, c_len);  // n为[l,r]，c_len表示离散化后数字个数
    for (int i = 1; i <= m; i++) {
        if (opt[i] == 1) {  // 表示将c加入到编号在[l,r]内的集合中
            tree.insert(l[i], r[i], Discrete::val2id(c[i]));
        } else {  // 表示查询编号在[l,r]内的集合的并集中，第c大的数是多少
            printf("%lld\n", Discrete::id2val(tree.query(l[i], r[i], c[i])));
        }
    }
}
