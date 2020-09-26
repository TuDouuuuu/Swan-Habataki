/*
  input:S = "babgbag", T = "bag"
  output:5
*/
ll dp[10][MAXN];
ll fun(const string &S, int slen, const string &T, int tlen) {
    for (int i = 0; i <= tlen + 1; i++) dp[i][0] = 0;
    for (int i = 0; i <= slen + 1; i++) dp[0][i] = 1;
    for (int i = 1; i <= tlen + 1; i++) {
        for (int j = 1; j <= slen + 1; j++) {
            if (T[i - 1] == S[j - 1]) dp[i][j] = (dp[i - 1][j - 1] + dp[i][j - 1]) % mod;
            else dp[i][j] = dp[i][j - 1];
        }
    }
    return dp[tlen][slen];
}
