/*
    input: ABCABDABCD
    index   0   1   2   3   4   5   6   7   8   9   10
    x[]     A   B   C   A   B   D   A   B   C   D   \0
    nxt[]   -1  -1  -1  0   1   -1  0   1   2   -1  0
*/
// call: scanf("%s", str+1); get_next(str+1, strlen(str+1), nex+1);
void get_next(char x[], int x_len, int nxt[]) {
    int i, j;
    for (nxt[0] = j = -1, i = 1; i < x_len; nxt[i++] = j) {
        while (~j && x[j + 1] != x[i])j = nxt[j];
        if (x[j + 1] == x[i])j++;
    }
}

/*
    input: ABCABDABCD
    index   1   2   3   4   5   6   7   8   9   10  11
    x[]     A   B   C   A   B   D   A   B   C   D   \0
    nxt[]   0   0   0   1   2   0   1   2   3   0   0
*/
// call: scanf("%s", str+1); get_next(str, strlen(str+1), nex);
void get_next(char x[], int x_len, int nxt[]) {
    nxt[1] = 0;
    for (int i = 2, j = 0; i <= x_len; i++) {
        while (j && x[j + 1] != x[i]) j = nxt[j];
        if (x[j + 1] == x[i]) ++j;
        nxt[i] = j;
    }
}