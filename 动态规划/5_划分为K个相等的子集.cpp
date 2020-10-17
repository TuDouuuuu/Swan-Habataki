/*
  nums = [4, 3, 2, 3, 5, 2, 1], k = 4
  return true
*/
bool canPartitionKSubsets(vector<int> &nums, int k) { // 调用函数
    int sum = 0;
    for (int i = 0; i < nums.size(); ++i) {
        sum += nums[i];
    }
    if (sum % k != 0) return false; //不能被整除,返回
    int target = sum / k;
    sort(nums.begin(), nums.end(), greater<int>());//从大到小排序,在计算dfs中的sum时,从最大的元素开始累加可以减少递归的次数
    if (target < nums[0]) return false;//不加这一句会超时
    vector<int> mark(nums.size(), 0);//标记数组,标记该元素已经被使用过,减少重复次数
    return dfs(nums, mark, 0, k, target);
}

bool dfs(vector<int> &nums, vector<int> &mark, int sum, int k, int target) {
    if (k == 0) return true;//找到了k个子集
    if (sum == target) return dfs(nums, mark, 0, k - 1, target);//找到了一个和为target的子集,sum置0,k减去一
    for (int i = 0; i < nums.size(); ++i) {//依次循环计算sum
        if (mark[i]) continue;//如果该元素已经被其他子集占有,则直接跳过
        if (sum > target) return false;//sum比target大,则直接返回false
        //将该元素标记为使用过
        mark[i] = 1;
        if (dfs(nums, mark, sum + nums[i], k, target)) return true;//一直递归知道找到k个子集时,返会true
        mark[i] = 0;//回溯后,该元素不符合要求,将该元素的使用标志置为0
    }
    return false;//遍历完整个数组都不能找到符合要求的子集
}
