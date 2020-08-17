/*
    input   output
    1       Case 1: 1 1 1
    341
*/
char str[MAXN];
int z[MAXN];
int main() {
    int T; scanf("%d", &T);
    int kase = 1;
    while (T--) {
        scanf("%s", str + 1);
        int len = strlen(str + 1);
        for (int i = 1; i <= len; i++) str[len + i] = str[i];
        getLCP(str + 1, len * 2, z + 1);
        int L = 0, E = 0, G = 0;
        for (int i = 1; i <= len; i++) {
            if (z[i] >= len) E++;
            else if (str[z[i]+1] > str[z[i]+i]) L++;
            else G++;
        }
        printf("Case %d: ", kase++);
        printf("%d %d %d\n", L/E, E/E, G/E);
    }
}