/*
  input                           output
  5 5
  25957 6405 15770 26287 26465 
  2 2 1                           6405
  3 4 1                           15770
  4 5 1                           26287
  1 2 2                           25957
  4 4 1                           26287
*/
class HJT { public:
    int ch[MAXN * 70][2], sum[MAXN * 70];
    int tot = 0;
    inline void push_up(int rt) {
        sum[rt] = sum[ch[rt][0]] + sum[ch[rt][1]];
    }
    int update(int rt, int pos, int val, int be, int en) {
        int nrt = ++tot;
        ch[nrt][0] = ch[nrt][1] = sum[nrt] = 0;
        if (be == en) {
            sum[nrt] = sum[rt] + val;
            return nrt;
        }
        int mid = (be + en) >> 1;
        if (pos <= mid) {
            ch[nrt][0] = update(ch[rt][0], pos, val, be, mid);
            ch[nrt][1] = ch[rt][1];
        } else {
            ch[nrt][0] = ch[rt][0];
            ch[nrt][1] = update(ch[rt][1], pos, val, mid + 1, en);
        }
        push_up(nrt);
        return nrt;
    }
    int query(int lrt, int rrt, int k, int be, int en) {
        if (be >= en) return be;
        int delta = sum[ch[rrt][0]] - sum[ch[lrt][0]];
        int mid = (be + en) >> 1;
        if (delta >= k) return query(ch[lrt][0], ch[rrt][0], k, be, mid);
        else return query(ch[lrt][1], ch[rrt][1], k - delta, mid + 1, en);
    }
} tree;

int ai[MAXN], root[MAXN];
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &ai[i]);
        Discrete::insert(ai[i]);
    }
    Discrete::init();
    root[0] = 0;
    for (int i = 1; i <= n; i++) {
        root[i] = tree.update(root[i-1], Discrete::val2id(ai[i]), 1, 1, Discrete::blen);
    }
    while(m--) {
        int l, r, k;
        scanf("%d%d%d", &l, &r, &k);
        printf("%d\n", Discrete::id2val(tree.query(root[l-1], root[r], k, 1, Discrete::blen)));
    }
}
