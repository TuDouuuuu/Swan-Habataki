/*
    input   
    10 5
    0 0, 0 1, 1 0, 1 1, 2 0, 2 1, 1 2, 0 2, 3 0, 3 1
    ouput 
    9
*/
const int MAXN = 1e5 + 5;   // 点的个数
class KD {
public:
    priority_queue<ll, vector<ll>, greater<ll> > q;
    struct node {
        int x, y;
    } T[MAXN];
    int ch[MAXN][2], L[MAXN], R[MAXN], D[MAXN], U[MAXN];
    
    inline void push_up(int rt) {
        L[rt] = R[rt] = T[rt].x;
        D[rt] = U[rt] = T[rt].y;
        if (ch[rt][0]) {
            L[rt] = min(L[rt], L[ch[rt][0]]), R[rt] = max(R[rt], R[ch[rt][0]]),
            D[rt] = min(D[rt], D[ch[rt][0]]), U[rt] = max(U[rt], U[ch[rt][0]]);
        }
        if (ch[rt][1]) {
            L[rt] = min(L[rt], L[ch[rt][1]]), R[rt] = max(R[rt], R[ch[rt][1]]),
            D[rt] = min(D[rt], D[ch[rt][1]]), U[rt] = max(U[rt], U[ch[rt][1]]);
        }
    }

    int build(int l, int r) {
        if (l > r) return 0;
        int mid = (l + r) >> 1;
        double av1 = 0, av2 = 0, va1 = 0, va2 = 0;
        for (int i = l; i <= r; i++) av1 += T[i].x, av2 += T[i].y;
        av1 /= (r - l + 1);
        av2 /= (r - l + 1);
        for (int i = l; i <= r; i++) va1 += (av1 - T[i].x) * (av1 - T[i].x), va2 += (av2 - T[i].y) * (av2 - T[i].y);
        if (va1 > va2)
            nth_element(T + l, T + mid, T + r + 1, [&](const node &ta, const node &tb) { return ta.x < tb.x; });
        else nth_element(T + l, T + mid, T + r + 1, [&](const node &ta, const node &tb) { return ta.y < tb.y; });
        ch[mid][0] = build(l, mid - 1);
        ch[mid][1] = build(mid + 1, r);
        push_up(mid);
        return mid;
    }

    ll sq(int x) { return (ll) x * x; }
    ll dist(int a, int b) {
        return max(sq(T[a].x - L[b]), sq(T[a].x - R[b])) + max(sq(T[a].y - D[b]), sq(T[a].y - U[b]));
    }
    void query(int l, int r, int rt) {
        if (l > r) return;
        int mid = (l + r) >> 1;
        ll tmp = sq(T[mid].x - T[rt].x) + sq(T[mid].y - T[rt].y);
        if (tmp > q.top()) q.pop(), q.push((tmp));
        ll distl = dist(rt, ch[mid][0]), distr = dist(rt, ch[mid][1]);
        if (distl > q.top() && distr > q.top()) {
            if (distl > distr) {
                query(l, mid - 1, rt);
                if (distr > q.top()) query(mid + 1, r, rt);
            } else {
                query(mid + 1, r, rt);
                if (distl > q.top()) query(l, mid - 1, rt);
            }
        } else {
            if (distl > q.top()) query(l, mid - 1, rt);
            if (distr > q.top()) query(mid + 1, r, rt);
        }
    }
    void init(int k) {
        k *= 2;
        for (int i = 1; i <= k; i++) q.push(0);
    }
    ll get_res() {
        return q.top();
    }
} tree;

int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    tree.init(k);
    for (int i = 1; i <= n; i++) scanf("%d%d", &tree.T[i].x, &tree.T[i].y);
    tree.build(1, n);
    for (int i = 1; i <= n; i++) {
        tree.query(1, n, i);
    }
    printf("%lld\n", tree.get_res());
}