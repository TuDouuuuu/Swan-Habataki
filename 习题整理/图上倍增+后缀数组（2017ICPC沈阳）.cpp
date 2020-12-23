/*  [input]     [output]
    4
    3           Case #1: 999
    149
    5           Case #2: 53123
    12345
    7           Case #3: 7166666
    3214567
    9           Case #4: 615015015
    261025520
*/
int to[MAXN][22];
int sa[MAXN], rk[MAXN << 1], oldrk[MAXN << 1], id[MAXN], cnt[MAXN];
void run(int s[], int n) {
    int m = 10;
    for (int i = 0; i <= m; i++) cnt[i] = 0;
    for (int i = 1; i <= n; i++) ++cnt[rk[i] = s[i]];
    for (int i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
    for (int i = n; i >= 1; i--) sa[cnt[rk[i]]--] = i;
    int n2 = (n << 1);
    for (int i = n + 1; i <= n2; i++) oldrk[i] = rk[i] = 0;
    for (int w = 0; (1 << w) <= n; w++) {
        for (int i = 0; i <= m; i++) cnt[i] = 0;
        for (int i = 1; i <= n; i++) id[i] = sa[i];
        for (int i = 1; i <= n; i++) ++cnt[rk[to[id[i]][w]]];
        for (int i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
        for (int i = n; i >= 1; i--) sa[cnt[rk[to[id[i]][w]]]--] = id[i];
        for (int i = 0; i <= m; i++) cnt[i] = 0;
        for (int i = 1; i <= n; i++) id[i] = sa[i];
        for (int i = 1; i <= n; i++) ++cnt[rk[id[i]]];
        for (int i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
        for (int i = n; i >= 1; i--) sa[cnt[rk[id[i]]]--] = id[i];
        for (int i = 0; i <= n; i++) oldrk[i] = rk[i];
        int p = 0;
        for (int i = 1; i <= n; i++) {
            if (oldrk[sa[i]] == oldrk[sa[i - 1]] && oldrk[to[sa[i]][w]] == oldrk[to[sa[i - 1]][w]]) rk[sa[i]] = p;
            else rk[sa[i]] = ++p;
        }
        m = p;
        if (p >= n) break;
    }
}

char str[MAXN];
int a[MAXN];
int main() {
    int T, kass = 1;
    FI(T);//scanf("%d", &T);
    while (T--) {
        int n;
        FI(n);// scanf("%d", &n);
        FI(str + 1);//scanf("%s", str + 1);
        for (int i = 1; i <= n; i++) {
            a[i] = str[i] - '0' + 1; // 1,2,..10
            to[i][0] = ((ll) (i - 1) * (i - 1) + 1) % n + 1;
        }

        for (int i = 1; i <= 20; i++) {
            for (int j = 1; j <= n; j++)
                to[j][i] = to[to[j][i - 1]][i - 1];
        }
        run(a, n);

        FO('C'), FO('a'), FO('s'), FO('e'), FO(' '), FO('#'), FO(kass++), FO(':'), FO(
                ' ');// printf("Case #%d: ", kass++);
        int tmp = sa[n];
        for (int i = 1; i <= n; i++) {
            FO(a[tmp] - 1);//printf("%d", a[tmp] - 1);
            tmp = to[tmp][0];
        }
        FO('\n');// printf("\n");
    }
    Flush;
}