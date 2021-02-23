/*
	[input] aaabaabaaaab
	[output]
	rank	Suffix			pos(sa)		index
	1 		aaaab 			8			1
	2	 	aaab 			9			2
	3 		aaabaabaaaab 	1			3
	4 		aab 			10			4
	5 		aabaaaab 		5			5
	6 		aabaabaaaab		2			6
	7 		ab 				11			7
	8 		abaaaab 		6			8
	9 		abaabaaaab 		3			9
	10 		b 				12			10
	11 		baaaab 			7			11
	12 		baabaaaab 		4			12
*/
namespace SA {	// private ver.
    int len;
    int sa[MAXN], rk[MAXN << 1], oldrk[MAXN << 1], id[MAXN], cnt[MAXN];

    void run(char s[], int _len) {   // call: run(str, strlen(str+1));
        len = _len;
        int m = max(len, 300);
        // memset(cnt, 0, sizeof(cnt));
        for (int i = 0; i <= m; i++) cnt[i] = 0;
        for (int i = 1; i <= len; i++) ++cnt[rk[i] = s[i]];
        for (int i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
        for (int i = len; i >= 1; i--) sa[cnt[rk[i]]--] = i;
        for (int i = len+1; i <= (len<<1); i++) oldrk[i] = rk[i] = 0;

        for (int w = 1; w <= len; w <<= 1) {
            // memset(cnt, 0, sizeof(cnt));
            for (int i = 0; i <= m; i++) cnt[i] = 0;
            for (int i = 1; i <= len; i++) id[i] = sa[i];
            for (int i = 1; i <= len; i++) ++cnt[rk[id[i] + w]];
            for (int i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
            for (int i = len; i >= 1; i--) sa[cnt[rk[id[i] + w]]--] = id[i];
            for (int i = 0; i <= m; i++) cnt[i] = 0;
            // memset(cnt, 0, sizeof(cnt));
            for (int i = 1; i <= len; i++) id[i] = sa[i];
            for (int i = 1; i <= len; i++) ++cnt[rk[id[i]]];
            for (int i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
            for (int i = len; i >= 1; i--) sa[cnt[rk[id[i]]]--] = id[i];
            // memcpy(oldrk, rk, sizeof(rk));
            for (int i = 0; i <= len; i++) oldrk[i] = rk[i];
            for (int p = 0, i = 1; i <= len; i++) {
                if (oldrk[sa[i]] == oldrk[sa[i - 1]] && oldrk[sa[i] + w] == oldrk[sa[i - 1] + w]) rk[sa[i]] = p;
                else rk[sa[i]] = ++p;
            }
        }
    }
}

namespace SA {  // 77 ver.
    int len;
    int sa[MAXN], rk[MAXN], oldrk[MAXN << 1], id[MAXN], cnt[MAXN], px[MAXN];

    bool cmp(int x, int y, int w) {
        return oldrk[x] == oldrk[y] && oldrk[x + w] == oldrk[y + w];
    }

    void run(char s[], int _len) {   // call: run(str, strlen(str+1));
        int i, m = 300, p, w;
        len = _len;
        // memset(cnt, 0, sizeof(cnt));
        for (i = 1; i <= m; i++) cnt[i] = 0;
        for (i = 1; i <= len; i++) ++cnt[rk[i] = s[i]];
        for (i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
        for (i = len; i >= 1; i--) sa[cnt[rk[i]]--] = i;

        for (w = 1; w <= len; w <<= 1, m = p) {
            for (p = 0, i = len; i > len - w; i--) id[++p] = i;
            for (i = 1; i <= len; i++)
                if (sa[i] > w) id[++p] = sa[i] - w;

            // memset(cnt, 0, sizeof(cnt));
            for (i = 0; i <= m; i++) cnt[i] = 0;
            for (i = 1; i <= len; i++) ++cnt[px[i] = rk[id[i]]];
            for (i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
            for (i = len; i >= 1; i--) sa[cnt[px[i]]--] = id[i];

            // memcpy(oldrk, rk, sizeof(rk));
            for (i = 0; i <= len; i++) oldrk[i] = rk[i];
            for (p = 0, i = 1; i <= len; i++) {
                rk[sa[i]] = cmp(sa[i], sa[i - 1], w) ? p : ++p;
            }
        }
    }
}


