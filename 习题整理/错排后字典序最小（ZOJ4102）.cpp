/*
    input       output
    4 1 3 2     1 2 4 3
    1 1 2 3     2 3 1 1
    1 1 1       Impossible
*/
int a[MAXN], ban[MAXN], todo[MAXN];
int res[MAXN];  // 字典序最小的存在res中
int main() {
    priority_queue<pii > pq;
    vector<int> vec;
    int n;  scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (int i = 1; i <= n; i++) ban[i] = todo[i] = 0;

    int flag = 1;
    for (int i = 1; i <= n; i++) ban[a[i]]++, todo[a[i]]++;
    for (int i = 1; i <= n; i++) {
        if (ban[i]) {
            vec.push_back(i);
            pq.push(mp(ban[i] + todo[i], i));
            if (ban[i] + todo[i] > n) {
                flag = 0;   break;
            }
        }
    }
    if (!flag) {    printf("Impossible\n"); continue;   }

    int pos = 0;
    for (int i = 1; i <= n; i++) {
        pii u = pq.top();   pq.pop();
        while (u.first != ban[u.second] + todo[u.second]) u = pq.top(), pq.pop();
        if (u.first == n - i + 1 && u.second != a[i]) {
            res[i] = u.second;
        } else {
            pq.push(u);
            for (int j = pos; j < SZ(vec); j++) {
                if (vec[j] != a[i] && todo[vec[j]] > 0) {
                    res[i] = vec[j];    break;
                }
            }
        }
        todo[res[i]]--; ban[a[i]]--;
        pq.push(mp(todo[res[i]] + ban[res[i]], res[i]));
        pq.push(mp(todo[a[i]] + ban[a[i]], a[i]));
        if (todo[vec[pos]] == 0) pos++;
    }
}