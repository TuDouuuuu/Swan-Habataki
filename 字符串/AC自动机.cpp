const int MAXN = 1e5 + 5;

class AC_Automaton {
public:
    int T[MAXN][26], val[MAXN], top;  //Trie相关
    int fail[MAXN];
    queue<int> q;
    // int pid[SIZE];  //对应字符串编号

    void init() {
        top = 1;
        memset(T[0], 0, sizeof(T[0]));
        memset(val, 0, sizeof(val));
//        memset(pid, 0, sizeof(pid));
    }

    AC_Automaton() {
        init();
    }

    void insert(char str[], int lenstr, int _pid) {
        int u = 0;
        for (int i = 1; i <= lenstr; i++) {
            int ch = str[i] - 'a';
            if (!T[u][ch]) {
                memset(T[top], 0, sizeof(T[top]));
                T[u][ch] = top++;
            }
            u = T[u][ch];
        }
        val[u]++;
        // pid[u] = _pid;
    }

    void build() {
        for (int i = 0; i < 26; i++)
            if (T[0][i]) {
                fail[T[0][i]] = 0;
                q.push(T[0][i]);
            }
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int i = 0; i < 26; i++)
                if (T[u][i]) {
                    fail[T[u][i]] = T[fail[u]][i];
                    q.push(T[u][i]);
                } else T[u][i] = T[fail[u]][i];
        }
    }

    int query(char str[], int lenstr) {
        int u = 0, ans = 0;
        for (int i = 1; i <= lenstr; i++) {
            int id = str[i] - 'a';
            u = T[u][id];
            for (int j = u; j && (~val[j]); j = fail[j]) {
                ans += val[j]; //val[j]=-1;
                if (pid[j]) {
                    qs[pid[j]].cnt++;
                }
            }

        }
        return ans;
    }
} tree;