#define pii pair<int , ll>
class LT {  public:
    int pool[MAXN], pool_cnt;
    int fa[MAXN];
    int find(int x) {
        if (x == fa[x]) return x;
        else return fa[x] = find(fa[x]);
    }
    struct node {
        int id; ll v;
        node() {}
        node(int _id, ll _v) { id = _id, v = _v; }
        bool operator<(const node &tb) { return v < tb.v; }
        bool operator==(const node &tb) { return v == tb.v; }
        bool operator>(const node &tb) { return v > tb.v; }
    } val[MAXN];
    ll add[MAXN], mul[MAXN];

    int ch[MAXN][2], dist[MAXN];
    int tot;

    void init() { tot = 0, pool_cnt = 0; }
    inline int Newnode(ll v, int id) { // 初始化左偏树节点
        int nrt = New();
        val[nrt].v = v, val[nrt].id = id, ch[nrt][0] = ch[nrt][1] = dist[nrt] = 0;
        mul[nrt] = 1, add[nrt] = 0;
        fa[nrt] = nrt;
        return nrt;
    }
#define lson ch[rt][0]
#define rson ch[rt][1]
    inline void push_down(int rt) {
        if (mul[rt] != 1) {
            if (lson) val[lson].v *= mul[rt], add[lson] *= mul[rt], mul[lson] *= mul[rt];
            if (rson) val[rson].v *= mul[rt], add[rson] *= mul[rt], mul[rson] *= mul[rt];
            mul[rt] = 1;
        }
        if (add[rt]) {
            if (lson) val[lson].v += add[rt], add[lson] += add[rt];
            if (rson) val[rson].v += add[rt], add[rson] += add[rt];
            add[rt] = 0;
        }
    }
    int merge(int x, int y) {   // 合并左偏树
        if (!x || !y) return x + y;
        if (val[x] == val[y] ? x > y : val[x] > val[y]) swap(x, y); // 小根堆
        push_down(x);
        ch[x][1] = merge(ch[x][1], y);
        if (dist[ch[x][0]] < dist[ch[x][1]]) swap(ch[x][0], ch[x][1]);
        fa[ch[x][0]] = fa[ch[x][1]] = fa[x] = x;
        dist[x] = dist[ch[x][1]] + 1;
        return x;
    }

    int insert(int rt, ll v, int id) {  return merge(rt, Newnode(v, id));}
    int pop(int rt) {   // call：root[fx] = tree.pop(root[fx]);
        push_down(rt);
        int tl = ch[rt][0], tr = ch[rt][1];
        Del(rt);
        return merge(tl, tr);
    }
    bool isempty(int x) { return x == 0;}
    pii top(int x) { return mp(val[x].id, val[x].v); }
} tree;

ll h[MAXN];
int f[MAXN], a[MAXN], c[MAXN];
ll v[MAXN], s[MAXN];

int root[MAXN]; int dep[MAXN]; int res1[MAXN], res2[MAXN];
void dfs(int u, int father) {
    dep[u] = dep[father] + 1;
    for (int i = head[u]; ~i; i = e[i].nex) {
        int tv = e[i].to;
        dfs(tv, u);
    }
    while (!tree.isempty(root[u]) && tree.top(root[u]).second < h[u]) {
        res1[u]++;
        int id = tree.top(root[u]).first;
        res2[id] = dep[c[id]] - dep[u];
        root[u] = tree.pop(root[u]);
    }
    if (tree.isempty(root[u])) return;
    if (a[u]) { // mul
        int ru = root[u];
        tree.val[ru].v *= v[u], tree.add[ru] *= v[u], tree.mul[ru] *= v[u];
    } else {
        int ru = root[u];
        tree.val[ru].v += v[u], tree.add[ru] += v[u];
    }
    if (u == 1) {
        while (!tree.isempty(root[1])) {
            int id = tree.top(root[1]).first;
            res2[id] = dep[c[id]] - dep[1] + 1;
            root[1] = tree.pop(root[1]);
        }
    } else {
        root[f[u]] = tree.merge(root[f[u]], root[u]);
    }
}

int main() {
    int n, m; scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) head[i] = -1;
    for (int i = 1; i <= n; i++) scanf("%lld", &h[i]);
    for (int i = 2; i <= n; i++) {
        scanf("%d%d%lld", &f[i], &a[i], &v[i]);
        addEdge(f[i], i);
    }
    for (int i = 1; i <= m; i++) {
        scanf("%lld%d", &s[i], &c[i]);
        root[c[i]] = tree.insert(root[c[i]], s[i], i);  // build a lot of heap
    }
    dfs(1, 1);
    for (int i = 1; i <= n; i++) printf("%d\n", res1[i]);
    for (int i = 1; i <= m; i++) printf("%d\n", res2[i]);
}