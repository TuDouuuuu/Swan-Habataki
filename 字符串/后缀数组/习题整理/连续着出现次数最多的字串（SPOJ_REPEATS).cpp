/*  babbabaabaabaabab RES = 4   */
char str[MAXN]; int ra[MAXN];
int main() {
    int T; scanf("%d", &T);
    while (T--) {
        int n;Mscanf("%d", &n);
        char qwq[3];
        for (int i = 1; i <= n; i++) scanf("%s", qwq), str[i] = qwq[0];
        SA::run(str, n);
        for (int i = 1; i <= n; i++) ra[SA::sa[i]] = i;
        SA::get_height(str);

        RMQ::init(n);
        int res = 0;
        for (int len = 1; len <= n; len++) {    // enum len
            for (int i = 1; i + len <= n; i += len) {
                int lcp = get_LCP(ra[i], ra[i + len]);
                int ans = lcp / len + 1;
                int _len = len - lcp % len;
                if (i - _len > 0) ans += get_LCP(ra[i - _len], ra[i + len - _len]) > _len ? 1 : 0;
                res = max(ans, res);
            }
        }
        printf("%d\n", res);
    }
}