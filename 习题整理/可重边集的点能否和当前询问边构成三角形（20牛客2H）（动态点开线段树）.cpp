map<int, int> ma;
SEG tree; // 动态点开线段树维护最小值，记得初始化val[0] = inf;
int root;
void add(int x) {
    ma[x]++;
    if (ma[x] == 1) {
        auto it = ma.lower_bound(x); auto R = it;
        if (++R != ma.end() && R-> second == 1) root = tree.update(root, R->first, R->first- x, 1, MAXR);
        if (it != ma.begin()) root = tree.update(root, x, x - (--it)->first, 1, MAXR);
        else root = tree.update(root, x, inf, 1, MAXR);
    } else if (ma[x] == 2) root = tree.update(root, x, 0, 1, MAXR);
}
void del(int x) {
    auto it = ma.lower_bound(x);
    ma[x]--;
    int L = -inf;
    if (it != ma.begin()) {
        L = (--it) -> first;
        ++it;
    }
    if (ma[x] == 0) {
        if ((++it) != ma.begin() && it->second == 1)
            root = tree.update(root, it->first, it->first-L, 1, MAXR);
        root = tree.update(root, x, inf, 1, MAXR);
        ma.erase(x);
    } else if (ma[x] == 1) root = tree.update(root, x, x-L, 1, MAXR);
}
int ask(int x) {
    auto it = ma.lower_bound(x/2+1);
    if (it == ma.end()) return inf;
    if (it->second > 1) return it->first;
    if (it != ma.begin()) {
        auto L = it; --L;
        if (L ->first + it ->first > x) return it->first;
    }
    if ((++it) != ma.begin()) return it->first;
    return inf;
}

int main() {
    tree.init();
    int q; scanf("%d", &q);
    while (q--) {
        int opt, x; scanf("%d%d", &opt, &x);
        if (opt == 1) add(x);   
        else if (opt == 2) del(x);
        else {
            if (tree.query_min(root, ask(x), MAXR, 1, MAXR) < x) printf("Yes\n");
            else printf("No\n");
        }
    }
}

