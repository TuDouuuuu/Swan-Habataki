const int muls[4] = {7, 13, 17, 19}; // 4 divers
namespace CRT {
    int a[4], m[4];
    void exgcd(int a, int b, int &x, int &y) {
        if (b == 0) {
            x = 1, y = 0;
            return;
        }
        exgcd(b, a % b, x, y);
        int z = x;
        x = y, y = z - y * (a / b);
    }
    int solve() {
        int mul_sum = 29393;
        int ans = 0;
        for (int i = 0; i < 4; i++) {
            int M = mul_sum / m[i];
            int x = 0, y = 0;
            exgcd(M, m[i], x, y);
            ans += a[i] * M * (x < 0 ? x + m[i] : x);
        }
        return ans % mul_sum;
    }
}
using CRT::solve;
int qpow[4][20][MAXN];
void init() {
    for (int i = 0; i < 4; i++) {
        CRT::m[i] = muls[i];
    }
    for (int i = 0; i < 4; i++) {
        int p = muls[i];
        for (int j = 0; j < p; j++) {
            int now = 1;
            for (int k = 0; k < MAXN; k++) {
                qpow[i][j][k] = now;
                now = now * j % p;
            }
        }
    }
}
int opt[MAXN], a[MAXN];
class SEG { public:
    struct node {
        int l, r;
        int val[4][20];
    } T[MAXN << 2];
    inline void push_up(int rt) {
        for (int i = 0; i < 4; i++) {
            int p = muls[i];
            for (int j = 0; j < p; j++) {
                T[rt].val[i][j] = T[rt << 1 | 1].val[i][T[rt
                        << 1].val[i][j]]; // T[rt<<1].val[i][j] -> calculate left, T[rt<<1|1].val[i][left] -> answer
            }
        }
    }
    void build(int rt, int l, int r) {
        T[rt].l = l, T[rt].r = r;
        if (l == r) {
            for (int i = 0; i < 4; i++) {
                int p = muls[i];
                for (int j = 0; j < p; j++) {
                    int now = j;
                    if (opt[l] == 0) now = (now + a[l]) % p;
                    else if (opt[l] == 1) now = (now * a[l]) % p;
                    else now = qpow[i][now][a[l]]; // now ^ (a[l]) % mul[i]
                    T[rt].val[i][j] = now;
                }
            }
            return;
        }
        int mid = (l + r) >> 1;
        build(rt << 1, l, mid), build(rt << 1 | 1, mid + 1, r);
        push_up(rt);
    }
    void update(int rt, int pos) {
        if (T[rt].l == T[rt].r) {
            for (int i = 0; i < 4; i++) {
                int p = muls[i];
                for (int j = 0; j < p; j++) {
                    int now = j;
                    if (opt[T[rt].l] == 0) now = (now + a[T[rt].l]) % p;
                    else if (opt[T[rt].l] == 1) now = (now * a[T[rt].l]) % p;
                    else now = qpow[i][now][a[T[rt].l]]; // now ^ (a[l]) % mul[i]
                    T[rt].val[i][j] = now;
                }
            }
            return;
        }
        int mid = (T[rt].l + T[rt].r) >> 1;
        if (pos <= mid) update(rt << 1, pos);
        else update(rt << 1 | 1, pos);
        push_up(rt);
    }
} tree;

int main() {
    init();
    int T; scanf("%d", &T); int kass = 1;
    while (T--) {
        int n, m; scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++) {
            char s[10]; scanf("%s", s);
            if (s[0] == '+') opt[i] = 0;
            else if (s[0] == '*') opt[i] = 1;
            else opt[i] = 2;
            int s_len = strlen(s);
            a[i] = 0;
            for (int j = 1; j < s_len; j++) a[i] = a[i] * 10 + s[j] - '0';
        }
        tree.build(1, 1, n);
        printf("Case #%d:\n", kass++);
        while (m--) {
            int ops; scanf("%d", &ops);
            if (ops == 1) {
                int x; scanf("%d", &x);
                for (int i = 0; i < 4; i++) {
                    int p = muls[i];
                    CRT::a[i] = tree.T[1].val[i][x % p];
                }
                printf("%d\n", solve());
            } else {
                int pos; scanf("%d", &pos);
                char s[10]; scanf("%s", s);
                if (s[0] == '+') opt[pos] = 0;
                else if (s[0] == '*') opt[pos] = 1;
                else opt[pos] = 2;
                int s_len = strlen(s);
                a[pos] = 0;
                for (int j = 1; j < s_len; j++) a[pos] = a[pos] * 10 + s[j] - '0';
                tree.update(1, pos);
            }
        }

    }
}