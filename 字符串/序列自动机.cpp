/*
    input       output
    aabbcc      2 4 2 4
    abcabc
    aabbcc      -1 -1 2 -1
    aabbcc
*/
char str1[MAXN], str2[MAXN];
int nex[MAXC], na[MAXN][MAXC], nb[MAXN][MAXC];
int dp[MAXN][MAXN]; // 记得开大两倍
int main() {
    scanf("%s%s", str1 + 1, str2 + 1);
    int len1 = strlen(str1 + 1), len2 = strlen(str2 + 1);
    int last = 1;
    for (int i = 1; i <= len2; i++) last = sa.insert(str2[i] - 'a', last);  // 调用后缀自动机
    for (int i = 0; i < 26; i++) nex[i] = len1 + 1;
    for (int i = len1; i >= 0; i--) {
        memcpy(na[i], nex, sizeof(nex));
        nex[str1[i] - 'a'] = i;
    }
    for (int i = 0; i < 26; i++) nex[i] = len2 + 1;
    for (int i = len2; i >= 0; i--) {
        memcpy(nb[i], nex, sizeof(nex));
        nex[str2[i] - 'a'] = i;
    }
    int res = MAXN;
    for (int l = 1; l <= len1; l++) {
        for (int r = l, u = 1; r <= len1; r++) {
            u = sa.trans[u][str1[r] - 'a'];
            if (!u) {
                res = min(res, r - l + 1);
                break;
            }
        }
    }
    printf("%d\n", res == MAXN ? -1 : res); // str1的一个最短的子串，它不是str2的子串。
    res = MAXN;
    for (int l = 1; l <= len1; l++) {
        for (int r = l, u = 0; r <= len1; r++) {
            u = nb[u][str1[r] - 'a'];
            if (u == len2 + 1) {
                res = min(res, r - l + 1);
                break;
            }
        }
    }
    printf("%d\n", res == MAXN ? -1 : res); // str1的一个最短的子串，它不是str2的子序列。
    for (int i = len1; i >= 0; i--) {
        for (int j = 1; j <= sa.rt; j++) {
            dp[i][j] = MAXN;
            for (int ch = 0; ch < MAXC; ch++) {
                int u = na[i][ch], v = sa.trans[j][ch];
                if (u <= len1) dp[i][j] = min(dp[i][j], dp[u][v] + 1);
            }
        }
    }
    printf("%d\n", dp[0][1] == MAXN ? -1 : dp[0][1]);   // str1的一个最短的子序列，它不是str2的子串。
    memset(dp, 0, sizeof(dp));
    for (int i = len1; i >= 0; i--) {
        for (int j = 0; j <= len2; j++) {
            dp[i][j] = MAXN;
            for (int ch = 0; ch < MAXC; ch++) {
                int u = na[i][ch], v = nb[j][ch];
                if (u <= len1) dp[i][j] = min(dp[i][j], dp[u][v] + 1);
            }
        }
    }
    printf("%d\n", dp[0][0] == MAXN ? -1 : dp[0][0]);   // str1的一个最短的子序列，它不是str2的子序列。
}