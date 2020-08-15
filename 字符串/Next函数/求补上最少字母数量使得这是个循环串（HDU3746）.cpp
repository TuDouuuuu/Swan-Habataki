/*
    input:  output
    3
    aaa     0
    abca    2
    abcde   5
*/
int main() {
    int T, len;
    scanf("%d", &T);
    while (T--) {
        scanf("%s", s + 1);
        get_next(s + 1, len = strlen(s + 1), nex + 1);  // 方法1
        int L = len - (nex[len] + 1);
        if (L < len && len % L == 0) puts("0");
        else printf("%d\n", L - len % L);
    }
}