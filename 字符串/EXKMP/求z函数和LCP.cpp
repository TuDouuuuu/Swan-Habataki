/*
    index       1   2   3   4   5   6   7   8
    char a[]    a   a   a   a   b   a   a   '\0'
    extend[]    4   3   2   1   0   2   1
    char b[]    a   a   a   a   a   '\0'
    z[]         5   4   3   2   1   
*/
// call: scanf("%s", a+1); getLCP(a+1, strlen(a+1), z+1);
void getLCP(char T[], int T_len, int z[]) {
    int i, len = T_len;
    z[0] = len;
    for (i = 0; i < len - 1 && T[i] == T[i + 1]; i++);
    z[1] = i;
    int a = 1;
    for (int k = 2; k < len; k++) {
        int p = a + z[a] - 1, L = z[k - a];
        if ((k - 1) + L >= p) {
            int j = max((p - k + 1), 0);
            while (k + j < len && T[k + j] == T[j])j++;
            z[k] = j, a = k;
        } else z[k] = L;
    }
}

// call: scanf("%s%s", a+1, b+1); exkmp(a+1, strlen(a+1), b+1, strlen(b+1), ex+1, z+1);
void exkmp(char S[], int S_len, char T[], int T_len, int extend[], int z[]) {
    getLCP(T, T_len, z);
    int a = 0;
    int MinLen = min(S_len, T_len);
    while (a < MinLen && S[a] == T[a])a++;
    extend[0] = a, a = 0;
    for (int k = 1; k < S_len; k++) {
        int p = a + extend[a] - 1, L = z[k - a];
        if ((k - 1) + L >= p) {
            int j = max((p - k + 1), 0);
            while (k + j < S_len && j < T_len && S[k + j] == T[j])j++;
            extend[k] = j;
            a = k;
        } else extend[k] = L;
    }
}