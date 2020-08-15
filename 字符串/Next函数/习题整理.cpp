int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%s", str + 1);
        int len;
        get_next(str, len = strlen(str + 1), nex);  // 方法2
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