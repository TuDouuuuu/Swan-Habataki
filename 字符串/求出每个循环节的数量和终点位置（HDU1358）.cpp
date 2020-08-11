/*
    input   output
    3       2 2
    aaa     3 3

    12              2 2
    aabaabaabaab    6 2
                    9 3
                    12 4
*/
int main() {
    int n;
    int cas = 0;
    while (~scanf("%d", &n) && n) {
        scanf("%s", str+1);
        get_next(str+1, n, nex+1);
        for (int i = 2; i <= n; i++) {
            if (nex[i] != -1 && (i % (i - nex[i] - 1) == 0))
                printf("%d %d\n", i, i / (i - nex[i] - 1));
        }
        puts("");
    }
}