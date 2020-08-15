const int MAXN = 6e5 + 5;
const int MAXC = 26;
int K;
class Suffix_Automaton {
public:
    int rt, link[MAXN], maxlen[MAXN], trans[MAXN][MAXC];
    int val[MAXN];
    int ans = 0;
    void init() {
        rt = 1;
        link[1] = maxlen[1] = 0;
        memset(trans[1], 0, sizeof(trans[1]));
        ans = 0;
    }

    Suffix_Automaton() { init(); }

    inline int insert(int ch, int last) {   // main: last = 1
        if (trans[last][ch]) {
            int p = last, x = trans[p][ch];
            if (maxlen[p] + 1 == maxlen[x]) return x;
            else {
                int y = ++rt;
                maxlen[y] = maxlen[p] + 1;
                val[y] = val[x];
                for (int i = 0; i < MAXC; i++) trans[y][i] = trans[x][i];
                while (p && trans[p][ch] == x) trans[p][ch] = y, p = link[p];
                link[y] = link[x], link[x] = y;
                return y;
            }
        }
        int z = ++rt, p = last;
        val[z]=0;
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
                val[y] = val[x];
                for (int i = 0; i < MAXC; i++) trans[y][i] = trans[x][i];
                while (p && trans[p][ch] == x) trans[p][ch] = y, p = link[p];
                link[y] = link[x], link[z] = link[x] = y;
            }
        }
        int t = z;
        while (t && val[t] < K) {
            val[t]++;
            if (val[t] >= K) ans+=maxlen[t] - maxlen[link[t]];
            t = link[t];
        }
        return z;
    }

} sa;
char str[MAXN];
int main() {
    int n, m;
    while(~scanf("%d%d%d", &n, &m, &K)) {
        sa.init();
        scanf("%s", str + 1);
        int last = 1;
        for (int i = 1; i <= n; i++) last = sa.insert(str[i] - 'a', last);
        while (m--) {
            int op;
            scanf("%d", &op);
            if (op == 1) {
                getchar();
                char ch;
                scanf("%c", &ch);
                last = sa.insert(ch - 'a', last);
            } else {
                printf("%d\n", sa.ans);
            }
        }
    }
}