/*  
    input   output
    4       6
    abab
    6       12
    ababab  
*/
int get_next(char x[], int x_len, int nxt[], int i, int j) {
    while (~j && x[j + 1] != x[i])j = nxt[j];
    if (x[j + 1] == x[i])j++;
    nxt[i++] = j;
    return j;
}

char str[MAXN];
int nex[MAXN], val[MAXN];

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        scanf("%s", str + 1);
        int len = strlen(str + 1);
        int last = -1;
        nex[1] = -1;
        int res = 0;
        for (int i = 1; i <= len; i++) {
            last = get_next(str + 1, len, nex + 1, i, last);
            if (nex[i] < 0) val[i] = 1;
            else val[i] = (val[nex[i] + 1] + 1) % mod;
            res = (res + val[i]) % mod;
        }
        printf("%d\n", res);
    }
}