/*  3
    bcbcbc
    bbbccc
    cbcbcb
    res = 4 ['b', 'c', 'bc', 'cb']
*/
class Suffix_Automaton {
public:
    int rt, link[MAXN], maxlen[MAXN], trans[MAXN][MAXC];
    int val[MAXN];

    void init() {
        rt = 1;
        link[1] = maxlen[1] = 0;
        memset(trans[1], 0, sizeof(trans[1]));
    }

    Suffix_Automaton() { init(); }

    inline int insert(int ch, int last) {   // main: last = 1
        if (trans[last][ch]) {
            int p = last, x = trans[p][ch];
            if (maxlen[p] + 1 == maxlen[x]) {   // 特判1：这个节点已经存在于SAM中
                return x;
            } else {
                int y = ++rt;
                maxlen[y] = maxlen[p] + 1;
                for (int i = 0; i < MAXC; i++) trans[y][i] = trans[x][i];
                while (p && trans[p][ch] == x) trans[p][ch] = y, p = link[p];
                link[y] = link[x], link[x] = y;
                return y;
            }
        }
        int z = ++rt, p = last;
        memset(trans[z], 0, sizeof(trans[z]));
        maxlen[z] = maxlen[last] + 1;
        while (p && !trans[p][ch]) trans[p][ch] = z, p = link[p];
        if (!p) link[z] = 1;
        else {
            int x = trans[p][ch];
            if (maxlen[p] + 1 == maxlen[x]) link[z] = x;
            else {
                int y = ++rt;
                maxlen[y] = maxlen[p] + 1;
                for (int i = 0; i < MAXC; i++) trans[y][i] = trans[x][i];
                while (p && trans[p][ch] == x) trans[p][ch] = y, p = link[p];
                link[y] = link[x], link[z] = link[x] = y;
            }
        }
        return z;
    }

    ll dfs(int n) {
        ll ans = 0;
        for (int i = 2; i <= rt; i++) {
            if (val[i] == n) ans += maxlen[i] - maxlen[link[i]];
        }
        return ans;
    }

} sa;

int p[MAXN];

int getmin(char *s) {//最小循环节
    int n = 1;
    for (int i = 2; s[i]; i++) {
        n++;
        p[i] = p[i - 1];
        while (p[i] && s[p[i] + 1] != s[i]) p[i] = p[p[i]];
        p[i] += (s[p[i] + 1] == s[i]);
    }
    int x = n;
    while (x) {
        x = p[x];
        if (n % (n - x) == 0) return n - x;
    }
    return n;
}

string calc(char *s) {//最小表示法
    int t = getmin(s);
    for (int i = 1; i <= t; i++) s[i + t] = s[i];
    int i = 1, j = 2, k;
    while (j <= t && i <= t) {
        for (k = 0; s[i + k] == s[j + k] && k < t; k++);
        if (k == t) break;
        if (s[i + k] < s[j + k]) j += k + 1;
        else i += k + 1;
        if (i == j) i++;
    }
    i = min(i, j);
    s[i + t] = 0;
    return string(s + i);
}

const int REPEAT = 3;
string s[MAXN], ns[MAXN];

int las[MAXN];

void update(int x, int id) {
    for (; x && las[x] != id; x = sa.link[x]) {
        sa.val[x]++;
        las[x] = id;
    }
}

char str[MAXN];

int main() {
    sa.init();
    int n; scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%s", str + 1);
        s[i] = calc(str);
    }
    sort(s + 1, s + 1 + n, [&](const string &ta, const string &tb) { return SZ(ta) < SZ(tb); });
    n = unique(s + 1, s + 1 + n) - (s + 1);
    if (n == 1) {
        cout << -1 << '\n'; return 0;
    }
    for (int i = 2; i <= n; i++) {
        string t = s[i];
        s[i] += t + t;//公共子串长度<3倍长串,所以要用到4倍长串的长度.
    }
    string t = s[1];
    while (SZ(s[1]) < SZ(s[n])) s[1] += t;

    for (int i = 1; i <= n; i++) {
        int last = 1;
        for (auto e: s[i]) last = sa.insert(e - 'a', last);
    }
    auto fun = [&](string ts, int id) {
        int x = 1;
        for (auto e: ts) {
            update(x = sa.trans[x][e - 'a'], id);
        }
    };
    for (int i = 1; i <= n; i++) fun(s[i], i);
    cout << sa.dfs(n) << '\n';
}