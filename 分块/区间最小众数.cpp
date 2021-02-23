using Discrete::id2val;
using Discrete::val2id;
int a[MAXN];
int bl[MAXN], unit;
int f[sqrt(n / (log(n) / log(2)))][sqrt(n / (log(n) / log(2)))];
vector<int> vec[MAXN];
int cnt[MAXN];
int n;
void pre(int pos) {
    memset(cnt, 0, sizeof(cnt));
    int ans = 0;
    for (int i = (pos - 1) * unit + 1; i <= n; i++) {
        cnt[a[i]]++;
        if (cnt[a[i]] > cnt[ans] || (cnt[a[i]] == cnt[ans] && a[i] < ans)) ans = a[i];
        f[pos][bl[i]] = ans;
    }
}
int _query(int l, int r, int x) {
    return upper_bound(vec[x].begin(), vec[x].end(), r) - lower_bound(vec[x].begin(), vec[x].end(), l);
}
int query(int l, int r) {
    int ans = f[bl[l] + 1][bl[r] - 1], mx = _query(l, r, ans);
    int sid = bl[l], eid = bl[r];
    if (sid == eid) {
        for (int i = l; i <= r; i++) {
            int t = _query(l, r, a[i]);
            if (t > mx || (t == mx && a[i] < ans)) ans = a[i], mx = t;
        }
        return ans;
    }
    for (int i = l; bl[i] == sid; i++) {
        int t = _query(l, r, a[i]);
        if (t > mx || (t == mx && a[i] < ans)) ans = a[i], mx = t;
    }
    for (int i = r; bl[i] == eid; i--) {
        int t = _query(l, r, a[i]);
        if (t > mx || (t == mx && a[i] < ans)) ans = a[i], mx = t;
    }
    return ans;
}

int main() {
    scanf("%d", &n);
    unit = sqrt(n / (log(n) / log(2)));
    Discrete::btol = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        Discrete::insert(a[i]);
    }
    Discrete::init();
    for (int i = 1; i <= n; i++) {
        a[i] = val2id(a[i]);
        vec[a[i]].push_back(i);
    }
    for (int i = 1; i <= n; i++) {
        bl[i] = (i - 1) / unit + 1;
    }
    for (int i = 1; i <= bl[n]; i++) pre(i);
    for (int i = 1; i <= n; i++) {
        int l, r; scanf("%d%d", &l, &r);
        printf("%d\n", id2val(query(l, r)));
    }
}