/*
  nums = [7,2,5,10,8], m = 2
  res = 18
*/
vector<int> dp, sum;
int splitArray(vector<int> &nums, int m) {
    int n = (int) nums.size();
    dp.resize(n), sum.resize(n);
    sum[0] = nums[0];
    for (int i = 1; i < n; i++) sum[i] = sum[i - 1] + nums[i];
    for (int i = 0; i < n; i++) dp[i] = sum[i];
    for (int i = 2; i <= m; i++) {
        int pos = n - 1;
        for (int j = n - 1; j >= 1; j--) {
            while (pos >= 0 && dp[pos] >= sum[j] - sum[pos]) {
                pos--;
            }
            if (pos >= 0) dp[j] = min(dp[j], max(dp[pos], sum[j] - sum[pos]));
            if (pos < n - 1) dp[j] = min(dp[j], max(dp[pos + 1], sum[j] - sum[pos + 1]));
        }
    }
    return dp[n - 1];
}
