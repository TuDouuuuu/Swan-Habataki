/*  [input] ababcbabccbaabc
    [output] 2  */
class HJT { public:
    int ch[MAXN * 70][2], sum[MAXN * 70];
    int tot;
    void init() { tot = 0; }
    inline void push_up(int rt) {
        sum[rt] = sum[ch[rt][0]] + sum[ch[rt][1]];
    }
    int update(int rt, int pos, int val, int be, int en) {
        int nrt = ++tot;
        ch[nrt][0] = ch[nrt][1] = sum[nrt] = 0;
        if (be == en) {
            sum[nrt] = sum[rt] + val;
            return nrt;
        }
        int mid = (be + en) >> 1;
        if (pos <= mid) {
            ch[nrt][0] = update(ch[rt][0], pos, val, be, mid);
            ch[nrt][1] = ch[rt][1];
        } else {
            ch[nrt][0] = ch[rt][0];
            ch[nrt][1] = update(ch[rt][1], pos, val, mid + 1, en);
        }
        push_up(nrt);
        return nrt;
    }
    int query(int lrt, int rrt, int R, int be, int en) {
        if (R == en) return sum[rrt] - sum[lrt];
        int mid = (be + en) >> 1;
        if (R <= mid) {
            return query(ch[lrt][0], ch[rrt][0], R, be, mid);
        } else {
            return sum[ch[rrt][0]] - sum[ch[lrt][0]] + query(ch[lrt][1], ch[rrt][1], R, mid + 1, en);
        }
    }
} tree;

void Manacher(char s[], int len, char A[], int B[]);
char A[MAXN * 2];
int B[MAXN * 2];

char str[MAXN];
int ren[MAXN], root[MAXN];

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%s", str + 1);
        int n = strlen(str + 1);
        Manacher(str + 1, n, A + 1, B + 1);

        int maxR = 0;
        for (int i = 1; i <= n; i++) ren[i] = (B[i * 2 + 1] - 2) >> 1, maxR = max(maxR, i - ren[i]);

        tree.init();
        root[0] = 0;
        for (int i = 1; i <= n; i++) {
            root[i] = tree.update(root[i - 1], i - ren[i], 1, 1, maxR);
        }
        
        ll res = 0;
        for (int i = 1; i <= n; i++) {
            res = res + tree.query(root[i], root[i+ren[i]], i, 1, maxR);
        }
        printf("%lld\n", res);
    }
}