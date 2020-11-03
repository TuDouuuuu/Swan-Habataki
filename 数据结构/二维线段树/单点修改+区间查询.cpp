class SEG2D {   public:
    int n;
    int maxx[MAXN << 2][MAXN << 2], minn[MAXN << 2][MAXN << 2];
    void init(int _n) { n = _n; }
    inline void subPush_up(int frt, int rt) {
        maxx[frt][rt] = max(maxx[frt][rt << 1], maxx[frt][rt << 1 | 1]);
        minn[frt][rt] = min(minn[frt][rt << 1], minn[frt][rt << 1 | 1]);
    }
    inline void push_up(int frt, int rt) {
        maxx[frt][rt] = max(maxx[frt << 1][rt], maxx[frt << 1 | 1][rt]);
        minn[frt][rt] = min(minn[frt << 1][rt], minn[frt << 1 | 1][rt]);
    }

    inline void subBuild(int frt, int fl, int fr, int rt, int l, int r) {
        if (l == r) {
            if (fl == fr) maxx[frt][rt] = minn[frt][rt] = a[fl][l];
            else push_up(frt, rt);
            return;
        }
        int mid = (l + r) >> 1;
        subBuild(frt, fl, fr, rt << 1, l, mid), subBuild(frt, fl, fr, rt << 1 | 1, mid + 1, r);
        subPush_up(frt, rt);
    }
    void build(int rt, int l, int r) {
        if (l == r) {
            subBuild(rt, l, r, 1, 1, n);
            return;
        }
        int mid = (l + r) >> 1;
        build(rt << 1, l, mid), build(rt << 1 | 1, mid + 1, r);
        subBuild(rt, l, r, 1, 1, n);
    }

    inline void subUpdate(int frt, int fl, int fr, int rt, int x, int y, int v, int be, int en) {
        if (be == en) {
            if (fl == fr) maxx[frt][rt] = minn[frt][rt] = v;
            else push_up(frt, rt);
            return;
        }
        int mid = (be + en) >> 1;
        if (y <= mid) subUpdate(frt, fl, fr, rt << 1, x, y, v, be, mid);
        else subUpdate(frt, fl, fr, rt << 1 | 1, x, y, v, mid + 1, en);
        subPush_up(frt, rt);
    }
    void update(int rt, int x, int y, int v, int be, int en) {
        if (be == en) {
            subUpdate(rt, be, en, 1, x, y, v, 1, n);
            return;
        }
        int mid = (be + en) >> 1;
        if (x <= mid) update(rt << 1, x, y, v, be, mid);
        else update(rt << 1 | 1, x, y, v, mid + 1, en);
        subUpdate(rt, be, en, 1, x, y, v, 1, n);
    }

    inline pii push_pii(const pii &ta, const pii &tb) {
        return mp(max(ta.first, tb.first), min(ta.second, tb.second));
    }
    inline pii subQuery(int frt, int rt, int x1, int x2, int y1, int y2, int be, int en) {
        if (y1 <= be && en <= y2) return mp(maxx[frt][rt], minn[frt][rt]);
        int mid = (be + en) >> 1;
        pii ans = mp(-inf, inf);
        if (y1 <= mid) ans = push_pii(ans, subQuery(frt, rt << 1, x1, x2, y1, y2, be, mid));
        if (y2 > mid) ans = push_pii(ans, subQuery(frt, rt << 1 | 1, x1, x2, y1, y2, mid + 1, en));
        return ans;
    }
    pii query(int rt, int x1, int x2, int y1, int y2, int be, int en) { // x1 <= x2, y1 <= y2
        if (x1 <= be && en <= x2) return subQuery(rt, 1, x1, x2, y1, y2, 1, n);
        int mid = (be + en) >> 1;
        pii ans = mp(-inf, inf);
        if (x1 <= mid) ans = push_pii(ans, query(rt << 1, x1, x2, y1, y2, be, mid));
        if (x2 > mid) ans = push_pii(ans, query(rt << 1 | 1, x1, x2, y1, y2, mid + 1, en));
        return ans;
    }
} tree;