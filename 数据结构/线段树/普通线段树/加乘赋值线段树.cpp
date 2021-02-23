class Seg_tree { public:
    struct node {
        int l, r; ll sum1, sum2, sum3;
    }T[SIZE<<2];
    ll add[SIZE<<2], set[SIZE<<2], mul[SIZE<<2];
    void push_up(int rt) {
        T[rt].sum1 = (T[rt<<1].sum1 + T[rt<<1|1].sum1) % MOD;
        T[rt].sum2 = (T[rt<<1].sum2 + T[rt<<1|1].sum2) % MOD;
        T[rt].sum3 = (T[rt<<1].sum3 + T[rt<<1|1].sum3) % MOD;
    }
    void build(int l, int r, int rt) {
        add[rt] = set[rt] = 0;
        mul[rt] = 1;
        T[rt].l = l, T[rt].r = r;
        if(l == r) {
            T[rt].sum1 = T[rt].sum2 = T[rt].sum3 = 0;
            return ;
        }
        int mid = (l + r) >> 1;
        build(l, mid, rt<<1); build(mid+1, r, rt<<1|1);
        push_up(rt);
    }
    void push_down(int rt, int len) {
        if (set[rt]) {
            set[rt<<1] = set[rt<<1|1] = set[rt];
            add[rt<<1] = add[rt<<1|1] = 0;
            mul[rt<<1] = mul[rt<<1|1] = 1;
            ll tmp = ((set[rt] * set[rt]) % MOD) * set[rt] % MOD;
            T[rt<<1].sum1 = ((len - (len>>1)) % MOD) * (set[rt] % MOD) % MOD;
            T[rt<<1|1].sum1 = ((len>>1) % MOD) * (set[rt] % MOD) % MOD;
            T[rt<<1].sum2 = ((len - (len>>1)) % MOD) * ((set[rt] * set[rt]) % MOD) % MOD;
            T[rt<<1|1].sum2 = ((len>>1) % MOD) * ((set[rt] * set[rt]) % MOD) % MOD;
            T[rt<<1].sum3 = ((len - (len>>1)) % MOD) * tmp % MOD;
            T[rt<<1|1].sum3 = ((len>>1) % MOD) * tmp % MOD;
            set[rt] = 0;
        }
        if (mul[rt] != 1) {
            mul[rt<<1] = (mul[rt<<1] * mul[rt]) % MOD;
            mul[rt<<1|1] = (mul[rt<<1|1] * mul[rt]) % MOD;
            if(add[rt<<1]) add[rt<<1] = (add[rt<<1] * mul[rt]) % MOD;
            if(add[rt<<1|1]) add[rt<<1|1] = (add[rt<<1|1] * mul[rt]) % MOD;
            ll tmp = ((mul[rt] * mul[rt]) % MOD * mul[rt]) % MOD;
            T[rt<<1].sum1 = (T[rt<<1].sum1 * mul[rt]) % MOD;
            T[rt<<1|1].sum1 = (T[rt<<1|1].sum1 * mul[rt]) % MOD;
            T[rt<<1].sum2 = (T[rt<<1].sum2 % MOD) * ((mul[rt] * mul[rt]) % MOD) % MOD;
            T[rt<<1|1].sum2 = (T[rt<<1|1].sum2 % MOD) * ((mul[rt] * mul[rt]) % MOD) % MOD;
            T[rt<<1].sum3 = (T[rt<<1].sum3 % MOD) * tmp % MOD;
            T[rt<<1|1].sum3 = (T[rt<<1|1].sum3 % MOD) * tmp % MOD;
            mul[rt] = 1;
        }
        if (add[rt]) {
            add[rt<<1] += add[rt];
            add[rt<<1|1] += add[rt];
            ll tmp = (add[rt] * add[rt] % MOD) * add[rt] % MOD;
            T[rt<<1].sum3 = (T[rt<<1].sum3 + (tmp * (len - (len>>1)) % MOD) + 3 * add[rt] * ((T[rt<<1].sum2 + T[rt<<1].sum1 * add[rt] % MOD)) % MOD);
            T[rt<<1|1].sum3 = (T[rt<<1|1].sum3 + (tmp * (len>>1) % MOD) + 3 * add[rt] * ((T[rt<<1|1].sum2 + T[rt<<1|1].sum1 * add[rt] % MOD)) % MOD);
            T[rt<<1].sum2 = (T[rt<<1].sum2 + ((add[rt] * add[rt] % MOD) * (len - (len>>1)) % MOD) + (2 * T[rt<<1].sum1 * add[rt] % MOD)) % MOD;
            T[rt<<1|1].sum2 = (T[rt<<1|1].sum2 + ((add[rt] * add[rt] % MOD) * (len>>1) % MOD) + (2 * T[rt<<1|1].sum1 * add[rt] % MOD)) % MOD;
            T[rt<<1].sum1 = (T[rt<<1].sum1 + (len - (len>>1)) * add[rt]) % MOD;
            T[rt<<1|1].sum1 = (T[rt<<1|1].sum1 + (len>>1) * add[rt]) % MOD;
            add[rt] = 0;
        }
    }
    void update(int l, int r, int op, int rt, int c) {
        if(l <= T[rt].l && T[rt].r <= r) {
            if(op == 3) {
                set[rt] = c;
                add[rt] = 0;
                mul[rt] = 1;
                T[rt].sum1 = ((T[rt].r - T[rt].l + 1) * c) % MOD;
                T[rt].sum2 = ((T[rt].r - T[rt].l + 1) * ((c * c) % MOD)) % MOD;
                T[rt].sum3 = ((T[rt].r - T[rt].l + 1) * (((c * c) % MOD) * c % MOD)) % MOD;
            }
            else if(op == 2) {
                mul[rt] = (mul[rt] * c) % MOD;
                if(add[rt]) add[rt] = (add[rt] * c) % MOD;
                T[rt].sum1 = (T[rt].sum1 * c) % MOD;
                T[rt].sum2 = (T[rt].sum2 * (c * c % MOD)) % MOD;
                T[rt].sum3 = (T[rt].sum3 * ((c * c % MOD) * c % MOD)) % MOD;
            }
            else if(op == 1){
                add[rt] += c;
                ll tmp = (((c * c) % MOD * c) % MOD * (T[rt].r - T[rt].l + 1)) % MOD;
                T[rt].sum3 = (T[rt].sum3 + tmp + 3 * c * ((T[rt].sum2 + T[rt].sum1 * c) % MOD)) % MOD;
                T[rt].sum2 = (T[rt].sum2 + (c * c % MOD * (T[rt].r - T[rt].l + 1) % MOD) + 2 * T[rt].sum1 * c) % MOD;
                T[rt].sum1 = (T[rt].sum1 + (T[rt].r - T[rt].l + 1) * c) % MOD; 
            }
            return ;
        }
        push_down(rt, T[rt].r - T[rt].l + 1);
        int mid = (T[rt].l + T[rt].r) >> 1;
        if (l > mid) update(l, r, op, rt<<1|1, c);
        else if(r <= mid) update(l, r, op, rt<<1, c);
        else {
            update(l, r, op, rt<<1, c); update(l, r, op, rt<<1|1, c);
        }
        push_up(rt);
    }
    ll query(int l, int r, int op, int rt) {
        if (l <= T[rt].l && T[rt].r <= r) {
            if (op == 1) return T[rt].sum1 % MOD;
            else if(op == 2) return T[rt].sum2 % MOD;
            else return T[rt].sum3 % MOD;
        }
        push_down(rt, T[rt].r - T[rt].l + 1);
        int mid = (T[rt].l + T[rt].r) >> 1;
        if(l > mid) return query(l, r, op, rt<<1|1);
        else if(r <= mid) return query(l, r, op, rt<<1);
        else return (query(l, r, op, rt<<1) + query(l, r, op, rt<<1|1)) % MOD;
    }
}tree;
int main() {
    int n, m;
    while (~scanf("%d %d", &n, &m)) {
        if(n == 0 && m == 0) break;
        tree.build(1, n, 1);
        while (m--) {
            int op, a, b, c; scanf("%d %d %d %d", &op, &a, &b, &c);
            if(op == 4) printf("%lld\n", tree.query(a, b, c, 1));
            else tree.update(a, b, op, 1, c);
        }
    }
}