/*
    input               output
    ababcababababcabab  2 4 9 18
    aaaaa               1 2 3 4 5
*/
int main() {
    while (~scanf("%s", s + 1)) {
        int cnt = 0;
        int len;
        get_next(s + 1, len = strlen(s + 1), nex + 1);
        for (int t = nex[len]; ~t; t = nex[t+1]) {
            if (s[t+1] == s[len]) ans[cnt++] = t + 1;
        }
        for (int i = cnt - 1; i >= 0; i--)printf("%d ", ans[i]);
        printf("%d\n", len);
    }
}