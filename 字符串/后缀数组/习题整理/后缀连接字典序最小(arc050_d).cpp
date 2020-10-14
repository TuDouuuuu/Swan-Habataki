/*
    input   ouput
    3       1 3 2
    arc
    2
    zz      1 2 / 2 1
    5       
    abaab   3 1 4 2 5
*/
using RMQ::get_LCP; using SA::rk;
int num[MAXN]; 
int N; char str[MAXN];
bool cmp(int x, int y) {
    if (x < y) {
        int lcp = get_LCP(rk[x], rk[y]);
        if (lcp < N - y + 1) {  // part 1
            if (str[x + lcp] < str[y + lcp]) return 1;
            else return 0;
        }
        lcp = get_LCP(rk[x + (N - y + 1)], rk[x]);
        if (str[x + (N - y + 1) + lcp] < str[x + lcp]) return 1;
        else return 0;
    } else {
        int lcp = get_LCP(rk[x], rk[y]);
        if (lcp < N - x+ 1) {  // part 1
            if (str[x + lcp] < str[y + lcp]) return 1;
            else return 0;
        }
        lcp = get_LCP(rk[y + (N - x + 1)], rk[y]);
        if (str[y + lcp] < str[y+ (N - x + 1) + lcp]) return 1;
        else return 0;
    }
}
int main() {
    scanf("%d", &N); scanf("%s", str + 1);
    SA::run(str, N); SA::get_height(str);
    RMQ::init(N);
    for (int i = 1; i <= N; i++) num[i] = i;
    sort(num+1, num+1+N, cmp);
    for (int i = 1; i <= N; i++) {
        printf("%d\n", num[i]);
    }
}