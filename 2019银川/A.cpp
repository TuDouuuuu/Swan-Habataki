const int MAXN = 1e5 + 5;
string name[MAXN], color[MAXN], bo_name[6], bo_color;
int val[MAXN];
vector<int> vec[4], v2[4];
int main() {
    cin.tie(0), cin.sync_with_stdio(0);
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> name[i] >> color[i] >> val[i];
        }
        for (int i = 1; i <= 5; i++) cin >> bo_name[i];
        cin >> bo_color;
        for (int i = 0; i < 4; i++) vec[i].clear(), v2[i].clear();
        for (int i = 1; i <= n; i++) {
            int fg1 = 0, fg2 = 0;
            for (int j = 1; j <= 5; j++) {
                if (name[i] == bo_name[j]) {
                    fg1 = 1;
                    break;
                }
            }
            if (color[i] == bo_color) fg2 = 1;
            if (fg1 == 0 && fg2 == 0) vec[0].pb(i);
            else if (fg1 == 0 && fg2 == 1) vec[1].pb(i);
            else if (fg1 == 1 && fg2 == 0) vec[2].pb(i);
            else vec[3].pb(i);
        }
        for (int i = 0; i < 4; i++) {
            sort(vec[i].begin(), vec[i].end(), [&](int ta, int tb) {
                if (name[ta] != name[tb]) return name[ta] < name[tb];
                return val[ta] > val[tb];
            });
            string pre = "";
            for (auto e: vec[i]) {
                if (name[e] != pre) {
                    v2[i].pb(e);
                    pre = name[e];
                }
            }
            sort(v2[i].begin(), v2[i].end(), [&](int ta, int tb) {
                return val[ta] > val[tb];
            });
        }
        int res = 0;
        set<string> st;
        function<void(int, int, int, int, int, int, int, int)> dfs = [&](int pos, int ri1, int ri2, int base, int t0,
                                                                         int t1, int t2, int t3) {
            if (pos == 6) {
                double ri = 1.0 + 0.1 * ri1 + 0.2 * ri2;
                res = max(res, (int) floor(ri * base));
                return;
            }
            if (t0 < SZ(v2[0])) {
                if (!st.count(name[v2[0][t0]])) {
                    st.insert(name[v2[0][t0]]);
                    dfs(pos + 1, ri1, ri2, base + val[v2[0][t0]], t0 + 1, t1, t2, t3);
                    st.erase(name[v2[0][t0]]);
                } else dfs(pos, ri1, ri2, base, t0 + 1, t1, t2, t3);
            }
            if (t1 < SZ(v2[1])) {
                if (!st.count(name[v2[1][t1]])) {
                    st.insert(name[v2[1][t1]]);
                    dfs(pos + 1, ri1, ri2 + 1, base + val[v2[1][t1]], t0, t1 + 1, t2, t3);
                    st.erase(name[v2[1][t1]]);
                } else dfs(pos, ri1, ri2, base, t0, t1 + 1, t2, t3);
            }
            if (t2 < SZ(v2[2])) {
                if (!st.count(name[v2[2][t2]])) {
                    st.insert(name[v2[2][t2]]);
                    dfs(pos + 1, ri1 + 1, ri2, base + val[v2[2][t2]], t0, t1, t2 + 1, t3);
                    st.erase(name[v2[2][t2]]);
                } else dfs(pos, ri1, ri2, base, t0, t1, t2 + 1, t3);
            }
            if (t3 < SZ(v2[3])) {
                if (!st.count(name[v2[3][t3]])) {
                    st.insert(name[v2[3][t3]]);
                    dfs(pos + 1, ri1 + 1, ri2 + 1, base + val[v2[3][t3]], t0, t1, t2, t3 + 1);
                    st.erase(name[v2[3][t3]]);
                } else dfs(pos, ri1, ri2, base, t0, t1, t2, t3 + 1);
            }
        };
        dfs(1, 0, 0, 0, 0, 0, 0, 0);
        cout << res << '\n';
    }
}