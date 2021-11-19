/*  6 4
    3 8 -3 2 5 2
    1 6 17          17
    1 6 16          15
    2 5 4           4
    2 5 -4          NONE    */
class BIT { public:
    ll val[MAXN][MAXN];
    int n, m;
    void init(int _n, int _m) {
        n = _n, m = _m;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++)
                val[i][j] = -llinf;
        }
    }
    inline int lowbit(int x) { return x & (-x); }
    void add(int x, int y, ll v) {
        for (int i = x; i <= n; i += lowbit(i)) {
            for (int j = y; j <= m; j += lowbit(j)) {
                val[i][j] = max(val[i][j], v);
            }
        }
    }
    ll query(int x, int y) {
        ll ans = -llinf;
        for (int i = x; i >= 1; i -= lowbit(i)) {
            for (int j = y; j >= 1; j -= lowbit(j)) {
                ans = max(ans, val[i][j]);
            }
        }
        return ans;
    }
} tree;
struct Query {
    int l, r,id; ll u;
    Query(int _l = 0, int _r = 0, ll _u = 0, int _id = 0) : l(_l), r(_r), u(_u), id(_id) {}
};
vector<Query> vec;
struct node {
    ll v; int be, en;
    node(int _be = 0, int _en = 0, ll _v = 0) : be(_be), en(_en), v(_v) {}
    bool operator<(const node &tb) const {  return v < tb.v;    }
};

vector<node> nd;
ll arr[MAXN], pre[MAXN], res[MAXM];
int main() {
    int n, m; scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &arr[i]);
        pre[i] = pre[i - 1] + arr[i];
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < i; j++) {
            nd.push_back(node(j + 1, i, pre[i] - pre[j]));
        }
    }
    sort(nd.begin(), nd.end());
    tree.init(n, n);
    for (int i = 1; i <= m; i++) {
        int s, e; ll u; scanf("%d%d%lld", &s, &e, &u);
        vec.push_back(Query(s, e, u, i));
    }
    sort(vec.begin(), vec.end(), [&](const Query &ta, const Query &tb) {
        return ta.u < tb.u;
    });
    int pos = 0;
    for (int i = 0; i < SZ(vec); i++) {
        while (pos < SZ(nd) && nd[pos].v <= vec[i].u) {
            tree.add(n+1-nd[pos].be, nd[pos].en, nd[pos].v);
            pos++;
        }
        res[vec[i].id] = tree.query(n+1-vec[i].l, vec[i].r);
    }
    for (int i = 1; i <= m; i++) {
        if (res[i] == -llinf) printf("NONE\n");
        else printf("%lld\n", res[i]);
    }
}
 