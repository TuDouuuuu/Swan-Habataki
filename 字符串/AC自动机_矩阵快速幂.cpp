int char2id(char ch) {
    switch (ch) {
        case 'A': return 0;
        case 'T': return 1;
        case 'G': return 2;
        case 'C': return 3;
    }
}
class AC {  public:
    int T[MAXN][4], top;
    bool endpos[MAXN];
    int fail[MAXN];
    queue<int> q;
    void init() {
        top = 1;
        memset(T[0], 0, sizeof(T[0]));
        endpos[0] = fail[0] = 0;
    }
    void insert(char str[], int lenstr) {
        int u = 0;
        for (int i = 1; i <= lenstr; i++) {
            int ch = char2id(str[i]);
            if (!T[u][ch]) {
                endpos[top] = fail[top] = 0;    // init a node
                memset(T[top], 0, sizeof(T[top]));
                T[u][ch] = top++;
            }
            u = T[u][ch];
        }
        endpos[u] = 1;
    }
    void build() {
        for (int i = 0; i < 4; i++)
            if (T[0][i]) {
                fail[T[0][i]] = 0;
                q.push(T[0][i]);
            }
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            if (endpos[fail[u]]) endpos[u] = 1;
            for (int i = 0; i < 4; i++)
                if (T[u][i]) {
                    fail[T[u][i]] = T[fail[u]][i];
                    q.push(T[u][i]);
                } else T[u][i] = T[fail[u]][i];
        }
    }
    void build_mat(mat &mat) {
        mat.init();
        for (int i = 0; i < top; i++) {
            if (endpos[i]) continue;
            for (int j = 0; j < 4; j++) {
                if (!endpos[T[i][j]]) mat.v[i][T[i][j]]++;
            }
        }
    }
} ac;

char str[MAXN];
int main() {
    int m, n;
    while (~scanf("%d%d", &m, &n)) {
        ac.init();
        while (m--) {
            scanf("%s", str + 1);
            ac.insert(str, strlen(str + 1));

        }
        ac.build();
        mat ma(ac.top, ac.top);
        ac.build_mat(ma);
        ma = ma ^ n;
        int res = 0;
        for (int i = 0; i < ac.top; i++) {
            res = (res + ma.v[0][i]) % mod;
        }
        printf("%d\n", res);
    }
}
