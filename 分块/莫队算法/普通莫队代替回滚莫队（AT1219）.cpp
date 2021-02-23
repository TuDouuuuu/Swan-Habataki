const int SIZE = 100500;
ll T[SIZE * 3], lazy[SIZE * 3];
ll M;
inline void modify(ll n, ll v) {
    for (T[n += M] += v, n >>= 1; n; n >>= 1)
        T[n] = max(T[n + n], T[n + n + 1]);
}
struct node {
    ll l, r, id;
} q[SIZE];
ll arr[SIZE], bl[SIZE], unit;
bool cmp(node x, node y) {
    if (x.l / unit != y.l / unit) {
        return x.l < y.l;
    }
    return x.r < y.r;
}
ll mp[SIZE], dis[SIZE];

bool cmp_dis(ll x, ll y) { return x < y;}

void Discrete(int N) {
    sort(dis + 1, dis + N + 1, cmp_dis);
    ll dis_len = unique(dis + 1, dis + N + 1) - dis;
    for (M = 1; M <= dis_len; M <<= 1);
    for (ll i = 1; i <= N; i++) {
        ll lb = lower_bound(dis + 1, dis + 1 + dis_len, arr[i]) - dis;
        mp[lb] = arr[i];
        arr[i] = lb;
    }
}

ll res[SIZE];

void push(ll x) { modify(arr[x], mp[arr[x]]); }
void pop(ll x) { modify(arr[x], -mp[arr[x]]); }
int main() {
    int N, Q; scanf("%d%d", &N, &Q);
    unit = sqrt(N);
    for (int i = 1; i <= N; i++) {
        scanf("%lld", &arr[i]);
        dis[i] = arr[i];
    }
    Discrete(N);
    for (int i = 1; i <= Q; i++) {
        q[i].id = i;
        scanf("%lld%lld", &q[i].l, &q[i].r);
    }
    sort(q + 1, q + 1 + Q, cmp);
    ll l = 1, r = 0;
    for (int i = 1; i <= Q; i++) {
        while (l < q[i].l)pop(l++);
        while (l > q[i].l)push(--l);
        while (r < q[i].r)push(++r);
        while (r > q[i].r)pop(r--);
        res[q[i].id] = T[1];
    }
    for (int i = 1; i <= Q; i++)
        printf("%lld\n", res[i]);
}