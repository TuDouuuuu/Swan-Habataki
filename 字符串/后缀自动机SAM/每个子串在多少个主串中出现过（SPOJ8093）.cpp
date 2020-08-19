/*
    input       output
    3 3
    abcabcabc
    aaa
    aafe
    abc         1
    a           3
    ca          1
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
} sa;

char str_sum[MAXN];
char str[MAXN];
int len[MAXN];

int las[MAXN];  // 记得清空las数组

inline void update(int x, int id) { // 暴力跳Link链
    for (; x && las[x] != id; x = sa.link[x]) {
        sa.val[x]++;
        las[x] = id;
    }
}

int main() {
   int n, q;
   scanf("%d%d", &n, &q);
   int tot = 0;
   for (int i = 1; i <= n; i++) {
       scanf("%s", str + 1);
       int last = 1;
       len[i] = strlen(str + 1);
       for (int j = 1; j <= len[i]; j++) {
           str_sum[++tot] = str[j];
           last = sa.insert(str[j] - 'a', last);
       }
   }
   sa.debug();
   tot = 0;
   for (int i = 1; i <= n; i++) {
       for (int j = 1, x = 1; j <= len[i]; j++) {
           update(x = sa.trans[x][str_sum[++tot] - 'a'], i);
       }
   }
   while (q--) {
       scanf("%s", str + 1);
       len[0] = strlen(str + 1);
       int flag = 1, u = 1;
       for (int i = 1; i <= len[0]; i++) {
           int ch = str[i]- 'a';
           if (sa.trans[u][ch]) {
               u = sa.trans[u][ch];
           } else {
               flag = 0; break;
           }
       }
       if (flag) printf("%d\n", sa.val[u]);
       else printf("0\n");
   }
}