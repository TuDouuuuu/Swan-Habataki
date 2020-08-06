class Trie {
public:
    int T[MAXN][26], val[MAXN], top;

    Trie() {
        top = 1;
        memset(T[0], 0, sizeof(T[0]));
        memset(val, 0, sizeof(val));
    }

    void insert(char str[], int lenstr) { // cal: scanf("%s", str+1), len = strlen(str+1), tree.insert(str, len);
        int u = 0;
        for (int i = 1; i <= lenstr; i++) {
            int ch = str[i] - 'a';
            if (!T[u][ch]) {
                memset(T[top], 0, sizeof(T[top]));
                T[u][ch] = top++;
            }
            u = T[u][ch];
        }
    }

    int search(char str[], int lenstr) {
        int u = 0;
        for (int i = 1; i <= lenstr; i++) {
            int ch = str[i] - 'a';
            if (!T[u][ch])return -1; //找不到
            u = T[u][ch];
        }
        if (!val[u]) {
            val[u] = 1;
            return 0;
        }
        return val[u];
    }
} tree;