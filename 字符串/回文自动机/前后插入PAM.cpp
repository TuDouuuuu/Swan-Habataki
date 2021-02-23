const int MAXN = 1e5 + 5;
const int base = MAXN;
int L, R;
class PAM { public:
    struct node {
        int ch[26];
        int len, fail, num;
    } T[MAXN];
    int pre, nex, tot;
    ll sum;
    void init() {
        memset(T[0].ch, 0, sizeof(T[0].ch));
        memset(T[1].ch, 0, sizeof(T[1].ch));
        T[0].len = 0, T[1].len = -1;
        T[0].fail = 1, T[1].fail = 0;
        tot = 1;
        pre = nex = 0;
        sum = 0;
    }
    void pre_insert(char s[], int i) {
        while (s[i + T[pre].len + 1] != s[i]) pre = T[pre].fail;
        if (!T[pre].ch[s[i] - 'a']) {
            T[++tot].len = T[pre].len + 2;
            memset(T[tot].ch, 0, sizeof(T[tot].ch));
            T[tot].fail = T[tot].num = 0;
            int j = T[pre].fail;
            while (s[i + T[j].len + 1] != s[i]) j = T[j].fail;
            T[tot].fail = T[j].ch[s[i] - 'a'];
            T[pre].ch[s[i] - 'a'] = tot;
            T[tot].num = T[T[tot].fail].num + 1;
        }
        pre = T[pre].ch[s[i] - 'a'];
        if (T[pre].len == R - L + 1) nex = pre;
        sum = sum + T[pre].num;
    }
    void bac_insert(char s[], int i) {
        while (s[i - T[nex].len - 1] != s[i]) nex = T[nex].fail;
        if (!T[nex].ch[s[i] - 'a']) {
            T[++tot].len = T[nex].len + 2;
            memset(T[tot].ch, 0, sizeof(T[tot].ch));
            T[tot].fail = T[tot].num = 0;
            int j = T[nex].fail;
            while (s[i - T[j].len - 1] != s[i]) j = T[j].fail;
            T[tot].fail = T[j].ch[s[i] - 'a'];
            T[nex].ch[s[i] - 'a'] = tot;
            T[tot].num = T[T[tot].fail].num + 1;
        }
        nex = T[nex].ch[s[i] - 'a'];
        if (T[nex].len == R - L + 1) pre = nex;
        sum = sum + T[nex].num;
    }
} tree;
char str[MAXN<<1]; // 两倍空间注意！
int main() {
    int n;
    while (~scanf("%d", &n)) {
        tree.init();
        L = base + 1, R = base;
        memset(str, 0,  sizeof(str));
        while (n--) {
            int opt; scanf("%d", &opt);
            if (opt == 1) { // 向前面插入
                char s[2]; scanf("%s", s);
                str[--L] = s[0];
                tree.pre_insert(str, L);
            } else if (opt == 2) { // 向后面插入
                char s[2]; scanf("%s", s);
                str[++R] = s[0];
                tree.bac_insert(str, R);
            } else if (opt == 3) { // 统计不同回文串个数
                printf("%d\n", tree.tot - 1);
            } else printf("%lld\n", tree.sum); // 统计回文串个数
        }
    }
}
