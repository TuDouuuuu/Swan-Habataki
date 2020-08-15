/* 
    kmp+矩阵加速
    求长度为n的不包含长度为m的子串的串个数
    input   4 3 100
            111
    output  81
*/
int nex[MAXN];
mat get_g(char x[], int x_len) {
    get_next(x, x_len, nex);
    mat g = mat(x_len, x_len);
    for (int i = 0; i < x_len; i++) {
        for (char ch = '0'; ch <= '9'; ch++) {
            int j = i;
            while (j && x[j+1] != ch) j = nex[j];
            if (x[j+1] == ch) j++;
            g.v[i][j] = (ll)(g.v[i][j] + 1ll) % mod;
        }
    }
    return g;
}
int n, m;
char str[MAXN];
int main() {
    scanf("%d%d%lld", &n, &m, &mod);
    scanf("%s", str + 1);
    mat g = get_g(str, strlen(str+1));
    g = g^n; 
    mat f(m, 1);
    f.v[0][0] = 1;
    f =f*g;
    ll res = 0;
    for (int i = 0; i < m; i++) {
        res = (ll)(res + f.v[0][i]) % mod;
    }
    printf("%lld\n", res);
}