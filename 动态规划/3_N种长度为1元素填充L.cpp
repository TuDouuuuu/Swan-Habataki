/*
  input N = 3, L = 3, K = 1
  output 6 [1, 2, 3]，[1, 3, 2]，[2, 1, 3]，[2, 3, 1]，[3, 1, 2]，[3, 2, 1].
  input N = 2, L = 3, K = 0
  output 6 [1, 1, 2]，[1, 2, 1]，[2, 1, 1]，[2, 2, 1]，[2, 1, 2]，[1, 2, 2]
  input N = 2, L = 3, K = 1
  output [1, 2, 1]，[2, 1, 2]
*/
vector<vector<long long>> dp;
// 空间复杂度O（NL）
int numMusicPlaylists(int N, int L, int K) {
    dp.resize(L + 1);
    for (int i = 0; i <= L; i++) dp[i].resize(N + 1);
    dp[0][0] = 1;
    for (int i = 1; i <= L; i++) {
        for (int j = 1; j <= N; j++) {
            dp[i][j] = (dp[i][j] + dp[i - 1][j - 1] * (long long) (N - j + 1)) % mod;
            dp[i][j] = (dp[i][j] + dp[i-1][j] * max(j - K, 0)) % mod;
        }
    }
    return dp[L][N];
}
// 空间复杂度O（L）
int numMusicPlaylists(int N, int L, int K) {
    dp.resize(2);
    for (int i = 0; i < 2; i++) dp[i].resize(N + 1);
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j <= N; j++) dp[i][j] = 0;
    }
    dp[0][0] = 1;
    int flag = 0;
    for (int i = 1; i <= L; i++) {
        dp[!flag][0] = 0;
        for (int j = 1; j <= N; j++) {
            dp[!flag][j] = 0;
            dp[!flag][j] = (dp[!flag][j] + dp[flag][j - 1] * (long long) (N - j + 1)) % mod;
            dp[!flag][j] = (dp[!flag][j] + dp[flag][j] * max(j - K, 0)) % mod;
        }
        flag = !flag;
    }
    return dp[flag][N];
}
