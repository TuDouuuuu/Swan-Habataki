/*
    input: aababaababb
    output: 7
            1 2 1
            1 10 5
            2 6 2
            4 9 3
            6 7 1
            7 10 2
            10 11 1
*/
namespace RUNS {
#define ull unsigned long long
#define tiii tuple<int, int, int>
    const ull seed = 19260817;
    ull ha[MAXN], based[MAXN];

    void init_hash(char s[], int n) {
        based[0] = 1;
        for (int i = 1; i <= n; i++) based[i] = based[i - 1] * seed;
        for (int i = 1; i <= n; i++) ha[i] = ha[i-1] * seed + s[i] - 'a' + 3;
    }
    inline ull getha(int l, int r) {
        return ha[r] - ha[l - 1] * based[r - l + 1];
    }

    inline int LCP(char s[], int n, int ta, int tb) {
        if (s[ta] != s[tb]) return 0;
        int L = 1, R = min(n - ta + 1, n - tb + 1);
        while (L < R) {
            int mid = (L + R + 1) >> 1;
            if (getha(ta, ta + mid - 1) == getha(tb, tb + mid - 1)) L = mid;
            else R = mid - 1;
        }
        return L;
    }
    inline int LCS(char s[], int n, int ta, int tb) {
        if (s[ta] != s[tb]) return 0;
        int L = 1, R = min(ta, tb);
        while (L < R) {
            int mid = (L + R + 1) >> 1;
            if (getha(ta - mid + 1, ta) == getha(tb - mid + 1, tb)) L = mid;
            else R = mid - 1;
        }
        return L;
    }

    int b1[MAXN], b2[MAXN];
    vector<tiii > getRuns(char s[], int n) {
        init_hash(s, n);

        auto cmp1 = [&](int ta, int tb) {
            int lcp = LCP(s, n, ta, tb);
            return s[ta + lcp] < s[tb + lcp];
        };

        auto cmp2 = [&](int ta, int tb) {
            int lcp = LCP(s, n, ta, tb);
            if (ta + lcp == n + 1) return false;
            return s[ta + lcp] < s[tb + lcp];
        };

        vector<tiii > ans;

        auto add = [&](int ta, int tb) {
            int L = LCS(s, n, ta - 1, tb), len = tb - ta + 1;
            if (L <= len) {
                int R = LCP(s, n, ta, tb + 1);
                if (L + R >= len) ans.pb({ta - L, tb + R, len});
            }
        };
        for (int i = n; i >= 1; i--) {
            b1[i] = b2[i] = i + 1;
            while (b1[i] < n && cmp1(i, b1[i])) b1[i] = b1[b1[i]];
            while (b2[i] < n && cmp2(b2[i], i)) b2[i] = b2[b2[i]];
            add(i, b1[i] - 1);
            if (b1[i] != b2[i]) add(i, b2[i] - 1);
        }
        sort(ans.begin(), ans.end());
        ans.erase(unique(ans.begin(), ans.end()), ans.end());
        return ans;
    }
}

using RUNS::getRuns;
char s[MAXN];
int main() {
    scanf("%s", s + 1); int n = strlen(s + 1);
    vector<tiii> res = getRuns(s, n);
    printf("%d\n", SZ(res));
    for (auto [l, r, p]: res) { // l = 左端点, r = 右端点, p = 最小周期
        printf("%d %d %d\n", l, r, p);
    }
}