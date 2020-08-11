/*
    input       output
    clinton     0
    homer
    riemann     rie 3
    marjorie
*/
int main() {
    while (~scanf("%s%s", a + 1, b + 1)) {
        int la = strlen(a + 1), lb = strlen(b + 1);
        strcat(a + 1, b + 1);
        int len = la + lb;
        get_next(a + 1, len, nex + 1);
        int k;
        for (k = nex[len]; k >= la || k >= lb; k = nex[k+1]);
        if (k == -1) puts("0");
        else {
            for (int i = 0; i <= k; i++)printf("%c", a[i+1]);
            printf(" %d\n", k + 1);
        }
    }
}