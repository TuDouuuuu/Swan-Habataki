ll a[MAXN], b[sqrt(MAXN)];
int bl[sqrt(MAXN)], unit;
vector<ll> vec[sqrt(MAXN)];
int n;
void reset(int x) {
    vec[x].clear();
    for (int i = (x - 1) * unit + 1; i <= min(x * unit, n); i++)
        vec[x].push_back(a[i]);
    sort(vec[x].begin(), vec[x].end());
}
void add(int l, int r, ll c) {
    int sid = bl[l], eid = bl[r];
    if (sid == eid) {
        for (int i = l; i <= r; i++) a[i] += c;
        reset(sid);
        return;
    }
    for (int i = l; bl[i] == sid; i++) a[i] += c;
    for (int i = sid + 1; i < eid; i++) b[i] += c;
    for (int i = r; bl[i] == eid; i--) a[i] += c;
    reset(sid), reset(eid);
}
int query(int l, int r, ll c) {
    int ans = 0;
    int sid = bl[l], eid = bl[r];
    if (sid == eid) {
        for (int i = l; i <= r; i++) {
            if (a[i] + b[sid] < c) ans++;
        }
        return ans;
    }
    for (int i = l; bl[i] == sid; i++) {
        if (a[i] + b[sid] < c) ans++;
    }

    for (int i = sid + 1; i < eid; i++) {
        ans += lower_bound(vec[i].begin(), vec[i].end(), c - b[i]) - vec[i].begin();
    }
    for (int i = r; bl[i] == eid; i--) {
        if (a[i] + b[eid] < c) ans++;
    }
    return ans;
}

int main() {
    scanf("%d", &n);
    unit = sqrt(n);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
        bl[i] = (i - 1) / unit + 1;
        vec[bl[i]].push_back(a[i]);
    }
    for (int i = 1; i <= bl[n]; i++) sort(vec[i].begin(), vec[i].end());
    for (int i = 1; i <= n; i++) {
        int opt, l, r; ll c; scanf("%d%d%d%lld", &opt, &l, &r, &c);
        if (opt) printf("%d\n", query(l, r, c * c));
        else add(l, r, c);
    }

}