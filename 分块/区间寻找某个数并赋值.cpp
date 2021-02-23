ll a[MAXN];
int bl[MAXN], unit;
int flag[sqrt(MAXN)]; ll tag[sqrt(MAXN)];
int n;
void reset(int pos) {
    if (!flag[pos]) return;
    for (int i = (pos - 1) * unit + 1; i <= min(pos * unit, n); i++) a[i] = tag[pos];
    flag[pos] = 0;
}
int solve(int l, int r, ll c) {
    int ans = 0;
    int sid = bl[l], eid = bl[r];
    if (sid == eid) {
        reset(sid);
        for (int i = l; i <= r; i++) {
            if (a[i] == c) ans++;
            else a[i] = c;
        }
        return ans;
    }
    reset(sid);
    for (int i = l; bl[i] == sid; i++) {
        if (a[i] == c) ans++;
        else a[i] = c;
    }
    for (int i = sid + 1; i < eid; i++) {
        if (flag[i]) {
            if (tag[i] == c) ans += unit;
            else tag[i] = c;
        } else {
            for (int j = (i - 1) * unit + 1; j <= min(n, i * unit); j++) {
                if (a[j] == c) ans++;
                else a[j] = c;
            }
            tag[i] = c, flag[i] = 1;
        }
    }
    reset(eid);
    for (int i = r; bl[i] == eid; i--) {
        if (a[i] == c) ans++;
        else a[i] = c;
    }
    return ans;
}
int main() {
    scanf("%d", &n);
    unit = sqrt(n);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
        bl[i] = (i - 1) / unit + 1;
    }
    for (int i = 1; i <= n; i++) {
        int l, r; ll c; scanf("%d%d%lld", &l, &r, &c);
        printf("%d\n", solve(l, r, c));
    }
}