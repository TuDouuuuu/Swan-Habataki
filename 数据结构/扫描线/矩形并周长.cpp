struct Line {
    int x, y1, y2;
    int mark;
    Line() {}
    Line(int _x, int _y1, int _y2, int _mark) {
        x = _x, y1 = _y1, y2 = _y2, mark = _mark;
    }
    bool operator<(const Line &tb) const {
        if (x == tb.x) return mark > tb.mark; // 如果出现了两条高度相同的扫描线，也就是两矩形相邻,那么需要先扫底边再扫顶边，否则就会多算这条边
        return x < tb.x;
    }
} line[MAXN << 1];

class Seg_Tree { public:
    struct SegTree {
        int l, r, sum, len, c;
//  c表示区间线段条数
        bool lc, rc;
//  lc, rc分别表示左、右端点是否被覆盖
//  统计线段条数(tree[x].c)会用到
    } tree[MAXN << 3];

    void build_tree(int x, int l, int r) {
        tree[x].l = l, tree[x].r = r;
        tree[x].lc = tree[x].rc = false;
        tree[x].sum = tree[x].len = 0;
        tree[x].c = 0;
        if (l == r) return;
        int mid = (l + r) >> 1;
        build_tree(x<<1, l, mid);
        build_tree(x<<1|1, mid + 1, r);
    }

    void pushup(int x) {
        int l = tree[x].l, r = tree[x].r;
        if (tree[x].sum) {
            tree[x].len = b[r + 1] - b[l];
            tree[x].lc = tree[x].rc = true;
            tree[x].c = 1;
//      做好相应的标记
        } else {
            tree[x].len = tree[x<<1].len + tree[x<<1|1].len;
            tree[x].lc = tree[x<<1].lc, tree[x].rc = tree[x<<1|1].rc;
            tree[x].c = tree[x<<1].c + tree[x<<1|1].c;
//      如果左儿子左端点被覆盖，那么自己的左端点也肯定被覆盖；右儿子同理
            if (tree[x<<1].rc && tree[x<<1|1].lc) tree[x].c -= 1;
//      如果做儿子右端点和右儿子左端点都被覆盖，
//      那么中间就是连续的一段，所以要 -= 1
        }
    }

    void edit_tree(int x, int L, int R, int c) {
        int l = tree[x].l, r = tree[x].r;
        if (b[l] >= R || b[r + 1] <= L) return;
        if (L <= b[l] && b[r + 1] <= R) {
            tree[x].sum += c;
            pushup(x);
            return;
        }
        edit_tree(x<<1, L, R, c), edit_tree(x<<1|1, L, R, c);
        pushup(x);
    }
}tree;

int main() {
    int n; scanf("%d", &n);
    init();
    for (int i = 1; i <= n; i++) {
        int x1, y1, x2, y2;
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        push(y1), push(y2);
        line[2 * i - 1] = Line(x1, y1, y2, 1);
        line[2 * i] = Line(x2, y1, y2, -1);
    }
    n <<= 1;
    sort(line + 1, line + 1 + n);
    build(); tree.build_tree(1, 1, blen-1);
    ll res = 0; int pre = 0;
    for (int i = 1; i < n; i++) {
        tree.edit_tree(1, line[i].y1, line[i].y2, line[i].mark);
        res += 1ll * abs(pre - tree.tree[1].len);
        pre = tree.tree[1].len;
        res += 2ll * tree.tree[1].c * (line[i + 1].x - line[i].x);
    }
    res += 1ll * (line[n].y2 - line[n].y1);
    printf("%lld\n", res);
}