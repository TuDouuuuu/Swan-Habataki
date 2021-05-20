struct node {
    int id, len;
    node(int _id = 0, int _len = 0) : id(_id), len(_len) {}
    bool operator<(const node &tb) const {
        if (len != tb.len) return len < tb.len;
        else return id < tb.id;
    }
};
set<node> st;

class SAM {
public:
    int rt, link[MAXN], maxlen[MAXN], trans[MAXN][MAXC];
    int val[MAXN];
    void init() {
        rt = 1;
        link[1] = maxlen[1] = 0;
        memset(trans[1], 0, sizeof(trans[1]));
    }
    int insert(int ch, int last) {
        int z = ++rt, p = last;
        val[z] = 1;
        memset(trans[z], 0, sizeof(trans[z]));
        maxlen[z] = maxlen[last] + 1;
        while (p && !trans[p][ch])trans[p][ch] = z, p = link[p];
        if (!p) link[z] = 1;
        else {
            int x = trans[p][ch];
            if (maxlen[p] + 1 == maxlen[x]) {
                link[z] = x;
                if (val[x]) val[x] = 0, st.erase(node(x, maxlen[link[x]] + 1));
            } else {
                int y = ++rt;
                maxlen[y] = maxlen[p] + 1;
                if (val[x]) st.erase(node(x, maxlen[link[x]] + 1));
                for (int i = 0; i < MAXC; i++) trans[y][i] = trans[x][i];
                while (p && trans[p][ch] == x) trans[p][ch] = y, p = link[p];
                link[y] = link[x], link[z] = link[x] = y;
                if (val[x]) st.insert(node(x, maxlen[link[x]] + 1));
            }
        }
        st.insert(node(z, maxlen[link[z]] + 1));
        return z;
    }
} sa;

char s[MAXN];

int main() {
    int n;
    scanf("%d", &n);
    sa.init();
    scanf("%s", s + 1);
    int last = 1;
    for (int i = 1; i <= n; i++) {
        last = sa.insert(s[i] - 'a', last);
        set<node>::iterator it = st.begin();
        printf("%d\n", it->len);
    }
}