


int nex[MAXN];
// x为模式串， y为文本串
// call: scanf("%s %s", a+1, b+1); kmp(b+1, strlen(b+1), a+1, strlen(a+1));
int kmp(char x[], int x_len, char y[], int y_len) {
    int i, j;
    int ans = 0;
    get_next(x, x_len, nex);
    for (j = -1, i = 0; i < y_len; i++) {
        while (~j && x[j + 1] != y[i])j = nex[j];
        if (x[j + 1] == y[i])j++;
        if (j == x_len - 1) {
            printf("%d\n", i-x_len+2);  // 出现的位置，可选，从1开始计数
            ans++, j = nex[j];
        }
    }
    for (i=0; i < x_len; i++) printf("%d ", nex[i]+1);  // 每个前缀的最长border的长度
    return ans;
}