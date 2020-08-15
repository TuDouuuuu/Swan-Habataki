/*
    input   output
    abcd    1
    aaaa    4
    ababab  3
*/
int main() {
    while (~scanf("%s", s + 1)) {
        if (s[1] == '.')break;
        int len;
        get_next(s + 1, len = strlen(s + 1), nex + 1);  // 方法1
        printf("%d\n", len % (len - nex[len] - 1) ? 1 : len / (len - nex[len] - 1));
    }
}