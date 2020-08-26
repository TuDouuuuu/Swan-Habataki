#define IT set<node>::iterator
const int MAXN = 1e5 + 5;
const int MOD7 = 1e9 + 7;

ll powmod(ll base, ll times, ll mod) {
    ll p = 1;
    ll ans = base % mod;
    while (times) {
        if (times & 1) p = p * ans % mod;
        ans = ans * ans % mod;
        times >>= 1;
    }
    return p;
}
class ODT {
public:
    struct node {
        int l, r;
        mutable ll val; // 玄学mutable注意！
        node() {}
        node(int _l, int _r = -1, ll _val = 0) { l = _l, r = _r, val = _val; }
        bool operator<(const node &tb) const { return l < tb.l; }
    };
    set<node> st;
    IT split(int pos) {
        IT it = st.lower_bound(node(pos));
        if (it != st.end() && it->l == pos) return it;
        --it;
        int ul = it->l, ur = it->r; ll uv = it->val;
        st.erase(it);
        st.insert(node(ul, pos - 1, uv));
        return st.insert(node(pos, ur, uv)).first;
    }
    void add(int l, int r, ll v = 1) {  // 对一段区间加上一个数
        IT itl = split(l), itr = split(r + 1);
        for (; itl != itr; itl++) itl->val += v;
    }
    void assign_val(int l, int r, ll v = 0) {   // 对一段区间进行赋值
        IT itl = split(l), itr = split(r + 1);
        st.erase(itl, itr);
        st.insert(node(l, r, v));
    }
    ll rank(int l, int r, int k) {
        vector<pair<ll, int>> vp;
        IT itl = split(l), itr = split(r + 1);
        vp.clear();
        for (; itl != itr; itl++)
            vp.push_back(pair<ll, int>(itl->val, (itl->r) - (itl->l) + 1));
        sort(vp.begin(), vp.end());
        for (vector<pair<ll, int>>::iterator it = vp.begin(); it != vp.end(); it++) {
            k -= it->second;
            if (k <= 0) return it->first;
        }
        return -1ll;
    }
    ll sum(int l, int r, int times, int mod) {
        IT itl = split(l), itr = split(r + 1);
        ll ans = 0;
        for (; itl != itr; itl++)
            ans = (ans + (ll) (itl->r - itl->l + 1) * powmod(itl->val, (ll) times, (ll) mod) % mod) % mod;
        return ans;
    }
    void insert(int l, int r, ll v) {
        st.insert(node(l, r, v));
    }
} tree;

ll seed, vmax;
ll rnd() {
    ll ret = seed;
    seed = (seed * 7 + 13) % MOD7;
    return ret;
}

ll a[MAXN];
int main() {
    int n, m;
    scanf("%d%d%lld%lld", &n, &m, &seed, &vmax);
    for (int i = 1; i <= n; i++) {
        a[i] = (rnd() % vmax) + 1;
        tree.insert(i, i, a[i]);
    }
    tree.insert(n + 1, n + 1, 0);
    int lines = 0;
    for (int i = 1; i <= m; i++) {
        int opt = int(rnd() % 4) + 1, l = int(rnd() % n) + 1, r = int(rnd() % n) + 1;
        if (l > r) swap(l, r);
        int x, y;
        // 原题神奇的操作，可以不用理会
        if (opt == 3) x = int(rnd() % (r - l + 1)) + 1;
        else x = int(rnd() % vmax) + 1;
        if (opt == 4) y = int(rnd() % vmax) + 1;

        if (opt == 1) tree.add(l, r, x);
        else if (opt == 2) tree.assign_val(l, r, x);
        else if (opt == 3) printf("%lld\n", tree.rank(l, r, x));
        else printf("%lld\n", tree.sum(l, r, x, y));
    }
}