int height[MAXN];
namespace SA {	// private ver.
    int len;
    int sa[MAXN], rk[MAXN << 1], oldrk[MAXN << 1], id[MAXN], cnt[MAXN];

    void run(char s[], int _len) {}   // step1 call: run(str, strlen(str+1));

    void get_height(char s[]) {	// step2 call: get_height(str)
        int k = 0;
        for (int i = 1; i <= len; i++) rk[sa[i]] = i;
        for (int i = 1; i <= len; i++) {
            if (rk[i] == 1) continue;
            if (k) --k;
            int j = sa[rk[i] - 1];
            while (j + k <= len && i + k <= len && s[i + k] == s[j + k]) k++;
            height[rk[i]] = k;
        }
    }
}
const int MAXL = 22;
namespace RMQ { // ST, O(1) get LCP
    int mm[MAXN], best[MAXL][MAXN];

    void init(int n) {	// step3 call: init(strlen(str+1))
        mm[0] = -1;
        for (int i = 1; i <= n; i++)
            mm[i] = ((i & (i - 1)) == 0) ? mm[i - 1] + 1 : mm[i - 1];
        for (int i = 1; i <= n; i++)best[0][i] = i;
        for (int i = 1; i <= mm[n]; i++)
            for (int j = 1; j + (1 << i) - 1 <= n; j++) {
                int a = best[i - 1][j];
                int b = best[i - 1][j + (1 << (i - 1))];
                if (height[a] < height[b])best[i][j] = a;
                else best[i][j] = b;
            }
    }

    int askRMQ(int a, int b) {
        int t = mm[b - a + 1];
        b -= (1 << t) - 1;
        a = best[t][a];
        b = best[t][b];
        return height[a] < height[b] ? a : b;
    }
	
	/*
		get_SA.cpp example's index
		get_LCP(2, 4) => 2
	*/
    int get_LCP(int a, int b) {
        if (a == b)return INF;
        if (a > b)swap(a, b);
        return height[askRMQ(a + 1, b)];
    }

}
