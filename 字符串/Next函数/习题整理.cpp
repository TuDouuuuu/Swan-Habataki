/*
    [NOI2014]动物园
    对于字符串SS的前ii个字符构成的子串，既是它的后缀同时又是它的前缀，并且该后缀与该前缀不重叠，将这种字符串的数量记作num[i]
    res为(num[i]+1)的乘积
    时间复杂度：O(n)
*/
int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%s", str + 1);
        int len;
        get_next(str, len = strlen(str + 1), nex);
        for (int i = 1; i <= len; i++) {
            val[i] = (val[nex[i]] + 1) % mod;
        }
        ll res = 1ll;
        for (int i = 2, j = 0; i <= len; i++) {
            while (j && str[j + 1] != str[i]) j = nex[j];
            if (str[j + 1] == str[i]) j++;
            while (j * 2 > i) j = nex[j];   // 去除重叠的
            num[i] = val[j];
            // res = (res * ((ll) val[j] + 1ll)) % mod;
        }
        printf("%lld\n", res);
    }
}