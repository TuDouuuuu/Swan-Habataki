/*  [input]         [output]
    7 5
    4 3 4 2 3 1 4
    1 4             Yes             
    2 2 3           No
    3 3 2 1         No
    4 4 1 3 2       Yes
    4 3 4 0 0       Yes
*/
const int MAXN = 5e3 + 5;
const ll seed1 = 233;
const ll seed2 = 19260817;
int arr[MAXN], brr[MAXN], pos[MAXN];

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        int n, q; scanf("%d%d", &n, &q);
        vector<ll> v1[MAXN], v2[MAXN], t1[MAXN], t2[MAXN];
        for (int i = 1; i <= n; i++) pos[i] = 0; // init pos
        for (int i = 1; i <= n; i++) scanf("%d", &arr[i]);
        for (int i = 1; i <= n; i++) {
            ll hash1 = 0, hash2 = 0;
            int cnt = 0;
            for (int j = i; j >= 1; j--) {
                if (pos[arr[j]] <= j) {
                    pos[arr[j]] = j;
                    cnt++;
                    hash1 = hash1 * seed1 + arr[j] + 3;
                    hash2 = hash2 * seed2 + arr[j] + 3;
                    v1[cnt].push_back(hash1);
                    v2[cnt].push_back(hash2);
                }
                if (j == 1) {
                    t1[cnt].push_back(hash1);
                    t2[cnt].push_back(hash2);
                }
            }
        }
        while (q--) {
            int m; scanf("%d", &m);
            for (int i = 1; i <= m; i++) scanf("%d", &brr[i]);
            if (!brr[m]) {  // have other 0
                while(!brr[m] && m) m--;
                if (!m) {
                    printf("Yes\n");
                    continue;
                }
                ll hash1 = 0, hash2 = 0;
                for (int i = 1; i <= m; i++) hash1 = hash1 * seed1 + brr[i] + 3;
                for (int i = 1; i <= m; i++) hash2 = hash2 * seed2 + brr[i] + 3;
                int flag = 0;
                for (int i = 0; i < SZ(t1[m]); i++) {
                    if (t1[m][i] == hash1 && t2[m][i] == hash2) {
                        flag = 1; break;
                    }
                }
                if (flag) printf("Yes\n");
                else printf("No\n");
            } else {
                ll hash1 = 0, hash2 = 0;
                for (int i = 1; i <= m; i++) hash1 = hash1 * seed1 + brr[i] + 3;
                for (int i = 1; i <= m; i++) hash2 = hash2 * seed2 + brr[i] + 3;
                int flag = 0;
                for (int i = 0; i < SZ(v1[m]); i++) {
                    if (v1[m][i] == hash1 && v2[m][i] == hash2) {
                        flag = 1; break;
                    }
                }
                if (flag) printf("Yes\n");
                else printf("No\n");
            }
        }
    }
}