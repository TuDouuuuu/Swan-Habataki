/*
    input       output
    4
    1 2 2 3
    0 1 3 1     1
    1 1 4 4
    0 1 2 2     4
    1 1 2 4
*/
ll a[MAXN], b[MAXN], sum[MAXN];
int bl[MAXN], unit;
void add(int l, int r, ll c) {
    int sid = bl[l], eid = bl[r];
    if (sid == eid) {
        for (int i = l; i <= r; i++) a[i] += c, sum[sid] += c;
        return;
    }
    for (int i = l; bl[i] == sid; i++) a[i] += c, sum[sid] += c;
    for (int i = sid + 1; i < eid; i++) b[i] += c, sum[i] += unit * c;
    for (int i = r; bl[i] == eid; i--) a[i] += c, sum[eid] += c;
}
ll query(int l, int r, ll mod) {
    int sid = bl[l], eid = bl[r];
    ll ans = 0;
    if (sid == eid) {
        for (int i = l; i <= r; i++) ans = ((ans + a[i]) % mod + b[sid]) % mod;
        return ans;
    }
    for (int i = l; bl[i] == sid; i++) ans = ((ans + a[i]) % mod + b[sid]) % mod;
    for (int i = sid + 1; i < eid; i++) ans = (ans + sum[i]) % mod;
    for (int i = r; bl[i] == eid; i--) ans = ((ans + a[i]) % mod + b[eid]) % mod;
    return ans;
}
int main() {
    int n;
    scanf("%d", &n);
    unit = sqrt(n);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
        bl[i] = (i - 1) / unit + 1;
        sum[bl[i]] += a[i];
    }
    for (int i = 1; i <= n; i++) {
        int opt, l, r; ll c;
        scanf("%d%d%d%lld", &opt, &l, &r, &c);
        if (opt == 0) add(l, r, c); // [l, r] 的数+c
        else printf("%lld\n", query(l, r, c + 1));  // sum[l, r] % (c + 1)
    }
}