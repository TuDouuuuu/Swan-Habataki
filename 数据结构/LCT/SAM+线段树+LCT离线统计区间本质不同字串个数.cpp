/*
    input       output
    aababc
    3   
    1 2         2
    2 4         5
    3 6         9
*/
namespace SAM_SEG_LCT {
    SEG seg, SAM sam;   // 后缀自动机长度为两倍
    class LCT { public:
        int val[MAXN], lazy[MAXN];
        int st_top, st[MAXN];   // stack操作
        int fa[MAXN], ch[MAXN][2];

        inline bool isroot(int x) { // 判断x是否为一个splay的根
            return ch[fa[x]][0] != x && ch[fa[x]][1] != x;
        }
        inline void push_up(int x) {    }
        inline void push_down(int x) {
            int l = ch[x][0], r = ch[x][1];
            if (lazy[x]) {
                if (l) val[l] = lazy[x], lazy[l] = lazy[x];
                if (r) val[r] = lazy[x], lazy[r] = lazy[x];
                lazy[x] = 0;
            }
        }
        inline void rotate(int x) { // x向上旋转
            int y = fa[x], z = fa[y], l, r;
            if (ch[y][0] == x) l = 0;
            else l = 1;
            r = l ^ 1;
            if (!isroot(y)) {
                if (ch[z][0] == y) ch[z][0] = x;
                else ch[z][1] = x;
            }
            fa[x] = z, fa[y] = x;
            fa[ch[x][r]] = y;
            ch[y][l] = ch[x][r];
            ch[x][r] = y;
            push_up(y), push_up(x);
        }
        inline void splay(int x) {  // 使得x成为当前splay中的根
            st_top = 0;
            st[++st_top] = x;
            for (int i = x; !isroot(i); i = fa[i]) st[++st_top] = fa[i];
            for (int i = st_top; i; i--) push_down(st[i]);
            while (!isroot(x)) {
                int y = fa[x], z = fa[y];
                if (!isroot(y)) {
                    if (ch[y][0] == x ^ ch[z][0] == y) rotate(x);
                    else rotate(y);
                }
                rotate(x);
            }
        }

        void access(int x, int p) { //把x到根节点的路径搞成一个splay，主要是这里修改
            int y = 0;
            while (x) {
                splay(x);
                if (int k = val[x]) seg.change(1, k - sam.maxlen[x] + 1, k - sam.maxlen[fa[x]], -1);
                ch[x][1] = y, y = x, x = fa[x];
            }
            val[y] = p, lazy[y] = p;
            seg.change(1, 1, p, 1); // 线段树区间修改chang(rt, L, R, val);
        }

        void build() {
            st_top = 0;
            fa[1] = ch[1][0] = ch[1][1] = val[1] = lazy[1] = 0;
            fa[0] = ch[0][0] = ch[0][1] = val[0] = lazy[0] = 0;
            for (int i = 2; i <= sam.rt; i++) {
                val[i] = lazy[i] = 0;
                ch[i][0] = ch[i][1] = 0;
                fa[i] = sam.link[i];
            }
        }
    } lct;
}

using namespace SAM_SEG_LCT;
struct Query {
    int l, r, id;
    bool operator<(const Query &tb) const { return r < tb.r;}
} query[MAXN];

char str[MAXN]; int endpos[MAXN];   ll res[MAXN];
int main() {
    scanf("%s", str + 1);   int len = strlen(str + 1);
    sam.init(); int sam_last = 1;
    for (int i = 1; i <= len; i++) sam_last = endpos[i] = sam.insert(str[i] - 'a', sam_last);
    lct.build(), seg.build(1, 1, len);

    int q;  scanf("%d", &q);
    for (int i = 1; i <= q; i++) scanf("%d%d", &query[i].l, &query[i].r), query[i].id = i;
    sort(query + 1, query + 1 + q);

    int pos = 1;
    for (int i = 1; i <= q; i++) {
        while (pos <= query[i].r) lct.access(endpos[pos], pos), pos++;
        res[query[i].id] = seg.query(1, query[i].l, query[i].r);
    }
    for (int i = 1; i <= q; i++) printf("%lld\n", res[i]);  // 输出答案
}