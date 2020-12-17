class AC {  public:
    int T[MAXN][2], top;
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
            int ch = str[i] - '0';
            if (!T[u][ch]) {
                endpos[0] = fail[top] = 0;
                memset(T[top], 0, sizeof(T[top]));
                T[u][ch] = top++;
            }
            u = T[u][ch];
        }
        endpos[u] = 1;
    }

    void build() {
        for (int i = 0; i < 2; i++) {
            if (T[0][i]) {
                fail[T[0][i]] = 0;
                q.push(T[0][i]);
            }
        }
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            if (endpos[fail[u]]) endpos[u] = 1;
            for (int i = 0; i < 2; i++) {
                if (T[u][i]) {
                    fail[T[u][i]] = T[fail[u]][i];
                    q.push(T[u][i]);
                } else T[u][i] = T[fail[u]][i];
            }
        }
    }

    bool vis[MAXN];
    void dfs(int u) {
        if (vis[u]) {
            printf("TAK\n");    // 存在无限长的安全代码
            exit(0);
        }
        vis[u] = 1;
        for (int i = 0; i < 2; i++) {
            int v = T[u][i];
            if (!endpos[v]) {
                dfs(v);
            }
        }
        vis[u] = 0;
    }
} ac;

char str[MAXN];
int len[MAXN];

int main() {
    int n; scanf("%d", &n);
    ac.init();
    for (int i = 1; i <= n; i++) {
        scanf("%s", str + 1);
        len[i] = strlen(str + 1);
        ac.insert(str, len[i]);
    }
    ac.build();
    ac.dfs(0);
    printf("NIE\n");    // 不存在无限长的安全代码
}