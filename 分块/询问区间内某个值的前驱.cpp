ll a[MAXN], b[sqrt(MAXN)];
int bl[sqrt(MAXN)], unit;
set<ll> st[sqrt(MAXN)];
void add(int l, int r, ll c) {
    int sid = bl[l], eid = bl[r];
    if (sid == eid) {
        for (int i = l; i <= r; i++) {
            st[sid].erase(a[i]); a[i] += c; st[sid].insert(a[i]);
        }
        return;
    }
    for (int i = l; bl[i] == sid; i++) {
        st[sid].erase(a[i]), a[i] += c, st[sid].insert(a[i]);
    }
    for (int i = sid + 1; i < eid; i++) b[i] += c;
    for (int i = r; bl[i] == eid; i--) {
        st[eid].erase(a[i]), a[i] += c, st[eid].insert(a[i]);
    }
}

ll query(int l, int r, ll c) {
    int sid = bl[l], eid = bl[r];
    ll ans = -1;
    if (sid == eid) {
        for (int i = l; i <= r; i++) {
            if (a[i] + b[sid] < c) ans = max(ans, a[i] + b[sid]);
        }
        return ans;
    }
    for (int i = l; bl[i] == sid; i++) {
        if (a[i] + b[sid] < c) ans = max(ans, a[i] + b[sid]);
    }
    for (int i = sid + 1; i < eid; i++) {
        set<ll>::iterator it = st[i].lower_bound(c - b[i]);
        if (it == st[i].begin()) continue;
        it--;
        ans = max(ans, (*it) + b[i]);
    }
    for (int i = r; bl[i] == eid; i--) {
        if (a[i] + b[eid] < c) ans = max(ans, a[i] + b[eid]);
    }
    return ans;
}

int main() {
    int n; scanf("%d", &n);
    unit = sqrt(n);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
        bl[i] = (i - 1) / unit + 1;
        st[bl[i]].insert(a[i]);
    }
    for (int i = 1; i <= n; i++) {
        int opt, l, r; ll c; scanf("%d%d%d%lld", &opt, &l, &r, &c);
        if (opt) printf("%lld\n", query(l, r, c));
        else add(l, r, c);
    }

}