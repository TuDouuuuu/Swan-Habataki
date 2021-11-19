namespace POLY {
    int limit;
    int L, R[MAXN * 3];

    inline vi NTT(vi a, int type) {
        a.resize(limit);
        for (int i = 0; i < limit; i++)
            if (i < R[i]) swap(a[i], a[R[i]]);
        for (int j = 1; j < limit; j <<= 1) {
            int Wn = ksm(type == 1 ? mod_g : mod_g_inv, (mod - 1) / (j << 1));
            for (int k = 0; k < limit; k += (j << 1)) {
                int w = 1;
                for (int i = 0; i < j; i++, w = (ll) w * Wn % mod) {
                    int x = a[i + k], y = (ll) w * a[j + k + i] % mod;
                    a[i + k] = (x + y) % mod;
                    a[j + k + i] = (x - y + mod) % mod;
                }
            }
        }
        if (type == -1) {
            int inv_limit = inv(limit);
            for (int i = 0; i < limit; i++) a[i] = (ll) a[i] * inv_limit % mod;
        }
        return a;
    }

    vi operator*(const vi &ta, const vi &tb) {
        L = 0, limit = 1;
        int n = SZ(ta) - 1, m = SZ(tb) - 1;
        while (limit <= n + m) limit <<= 1, L++;
        for (int i = 0; i < limit; i++) R[i] = (R[i >> 1] >> 1) | ((i & 1) << (L - 1));
        vi nta = NTT(ta, 1), ntb = NTT(tb, 1);
        vi ans(limit);
        for (int i = 0; i < limit; i++) ans[i] = (ll) nta[i] * ntb[i] % mod;
        ans = NTT(ans, -1); ans.resize(n + m + 1);
        return ans;
    }

    vi getInv(const vi &t) {
        vi ans;
        function<void(int)> _getInv = [&](int n) {
            if (n == 0) {
                ans.resize(1); ans[0] = inv(t[0]);
                return;
            }
            _getInv(n >> 1);

            L = 0, limit = 1;
            while (limit <= (n << 1)) limit <<= 1, L++;
            for (int i = 0; i < limit; i++) R[i] = (R[i >> 1] >> 1) | ((i & 1) << (L - 1));

            vi C(limit);
            ans.resize(limit);
            for (int i = 0; i <= n; i++) C[i] = t[i];
            C = NTT(C, 1), ans = NTT(ans, 1);
            for (int i = 0; i < limit; i++)
                ans[i] = ((2 - (ll) ans[i] * C[i] % mod) + mod) % mod * ans[i] % mod;
            ans = NTT(ans, -1); ans.resize(n + 1);
        };
        _getInv(SZ(t) - 1);
        return ans;
    }

    pair<vi, vi > operator/(const vi &ta, const vi &tb) {
        int na = SZ(ta) - 1, nb = SZ(tb) - 1;
        vi Fr(na + 1), Gr(nb + 1);
        for (int i = 0; i <= na; i++) Fr[na - i] = ta[i];
        for (int i = 0; i <= nb; i++) Gr[nb - i] = tb[i];
        Gr.resize(na - nb + 1);
        vi Gr_inv = getInv(Gr);
        Fr = Fr * Gr_inv;

        vi ans1(na - nb + 1);
        for (int i = 0; i <= na - nb; i++) ans1[i] = Fr[na - nb - i];

        vi ans2; ans2 = tb * ans1;
        for (int i = 0; i < nb; i++) ans2[i] = (ta[i] - ans2[i] + mod) % mod;
        ans2.resize(nb);

        return mp(ans1, ans2);
    }

    inline vi getD(const vi &t) {
        vi ans(SZ(t));
        for (int i = 1; i < SZ(t); i++) ans[i - 1] = (ll) i * t[i] % mod;
        return ans;
    }

    inline vi getJ(const vi &t) {
        vi ans(SZ(t));
        for (int i = 1; i < SZ(t); i++) ans[i] = (ll) t[i - 1] * inv(i) % mod;
        return ans;
    }

    vi getLn(const vi &t) {
        vi FD = getD(t), Finv = getInv(t);
        int n = SZ(t) - 1;

        L = 0, limit = 1;
        while (limit <= (n << 1)) limit <<= 1, L++;
        for (int i = 0; i < limit; i++) R[i] = (R[i >> 1] >> 1) | ((i & 1) << (L - 1));

        vi ans(limit);
        FD = NTT(FD, 1), Finv = NTT(Finv, 1);
        for (int i = 0; i < limit; i++) ans[i] = (ll) FD[i] * Finv[i] % mod;
        ans = NTT(ans, -1);

        ans.resize(SZ(t)); ans = getJ(ans);
        return ans;
    }

    vi getExp(const vi &t) {
        vi ans;
        function<void(int)> _getExp = [&](int n) {
            if (n == 0) {
                ans.resize(1); ans[0] = 1;
                return;
            }
            _getExp(n >> 1);
            ans.resize(n + 1);
            vi LnG = getLn(ans);

            L = 0, limit = 1;
            while (limit <= (n << 1)) limit <<= 1, L++;
            for (int i = 0; i < limit; i++) R[i] = (R[i >> 1] >> 1) | ((i & 1) << (L - 1));

            LnG[0] = (t[0] + 1 - LnG[0] + mod) % mod;
            for (int i = 1; i <= n; i++) LnG[i] = (t[i] - LnG[i] + mod) % mod;

            LnG = NTT(LnG, 1), ans = NTT(ans, 1);
            for (int i = 0; i < limit; i++) ans[i] = (ll) ans[i] * LnG[i] % mod;
            ans = NTT(ans, -1); ans.resize(n + 1);
        };
        _getExp(SZ(t) - 1);
        return ans;
    }

    vi getSqrt(const vi &t) {
        vi ans;
        function<void(int)> _getSqrt = [&](int n) {
            if (n == 0) {
                ans.resize(1);
                ans[0] = 1;
                return;
            }
            _getSqrt(n >> 1);

            ans.resize(n + 1);
            vi A = getInv(ans);

            L = 0, limit = 1;
            while (limit <= (n << 1)) limit <<= 1, L++;
            for (int i = 0; i < limit; i++) R[i] = (R[i >> 1] >> 1) | ((i & 1) << (L - 1));

            vi B(limit);
            for (int i = 0; i <= n; i++) B[i] = t[i];

            B = NTT(B, 1), A = NTT(A, 1), ans = NTT(ans, 1);
            for (int i = 0; i < limit; i++) {
                ans[i] = ((ll) A[i] * B[i] % mod + ans[i]) % mod * inv2 % mod;
            }
            ans = NTT(ans, -1); ans.resize(n + 1);
        };
        _getSqrt(SZ(t) - 1);
        return ans;
    }

    vi operator^(const vi &t, int k) {
        vi ans = getLn(t);
        for (auto &e: ans) e = (ll) e * k % mod;
        ans = getExp(ans);
        return ans;
    }

    vi getKsm(const vi &t, int k, int k1, int k2) {
        vi ans(SZ(t));
        int num0 = SZ(t) - 1;
        for (int i = 0; i < SZ(t); i++) {
            if (t[i]) {
                num0 = i;
                break;
            }
        }
        if ((ll) num0 * k2 > (ll) (SZ(t) - 1)) return ans;

        int n = SZ(t) - 1, m = n;
        n -= num0;
        vi F(n + 1);
        for (int i = 0; i <= n; i++) F[i] = t[i + num0];
        int f0 = F[0], inv_f0 = inv(f0);
        for (int i = 0; i <= n; i++) F[i] = (ll) F[i] * inv_f0 % mod;

        vi LnF = getLn(F);
        for (int i = 0; i <= n; i++) LnF[i] = (ll) LnF[i] * k % mod;
        ans = getExp(LnF);

        f0 = ksm(f0, k1);
        for (int i = 0; i <= n; i++) ans[i] = (ll) ans[i] * f0 % mod;

        n = m, num0 = min((ll) num0 * k2, (ll) n);
        ans.resize(SZ(t));
        for (int i = n; i >= num0; i--) ans[i] = ans[i - num0];
        for (int i = num0 - 1; i >= 0; i--) ans[i] = 0;
        return ans;
    }

    struct node {
        int l, r;
        vector<int> val;
    }; vector<node> T;

    vi eval(vi f, int b[], int m) {
        function<void(int)> push_up = [&](int rt) {
            T[rt].val = T[rt << 1].val * T[rt << 1 | 1].val;
        };
        function<void(int, int *, int, int)> build = [&](int rt, int b[], int l, int r) {
            T[rt].l = l, T[rt].r = r;
            if (l == r) {
                T[rt].val.resize(2);
                T[rt].val[0] = 1, T[rt].val[1] = mod - b[l];
                return;
            }
            int mid = (l + r) >> 1;
            build(rt << 1, b, l, mid), build(rt << 1 | 1, b, mid + 1, r);
            push_up(rt);
        };
        T.resize(m << 2);
        build(1, b, 1, m);
        reverse(f.begin(), f.end());
        vector<vi > p(m << 2);

        auto slice = [&](const vi &ta, int d) {
            if (d < SZ(ta))
                return vector<int>(ta.begin(), ta.begin() + d + 1);
            vector<int> ans(ta);
            ans.resize(d + 1);
            return ans;
        };

        p[1] = f * getInv(slice(T[1].val, SZ(f) - 1));
        p[1].resize(SZ(f));
        reverse(p[1].begin(), p[1].end());
        p[1].resize(m);

        auto __mul = [&](const vi &ta, const vi &tb) {
            int n = SZ(ta) - 1, m = SZ(tb) - 1;
            L = 0, limit = 1;
            while (limit <= (n + m)) limit <<= 1, L++;
            for (int i = 0; i < limit; i++) R[i] = (R[i >> 1] >> 1) | ((i & 1) << (L - 1));
            vi nta = NTT(ta, 1), ntb = NTT(tb, 1);
            reverse(ntb.begin() + 1, ntb.end());
            vi ans(limit);
            for (int i = 0; i < limit; i++) {
                ans[i] = (ll) nta[i] * ntb[i] % mod;
            }
            ans = NTT(ans, -1), ans.resize(SZ(ta) - SZ(tb) + 1);
            return ans;
        };

        auto _mul = [&](const vi &ta, const vi &tb1, const vi &tb2) {
            return mp(__mul(ta, tb1), __mul(ta, tb2));
        };

        vi ans;
        function<void(int)> dfs = [&](int rt) {
            if (T[rt].l == T[rt].r) {
                ans.pb(p[rt][0]);
                return;
            }
            tie(p[rt << 1], p[rt << 1 | 1]) = _mul(p[rt], T[rt << 1 | 1].val, T[rt << 1].val);
            dfs(rt << 1), dfs(rt << 1 | 1);
        };
        dfs(1);
        return ans;
    }
}
