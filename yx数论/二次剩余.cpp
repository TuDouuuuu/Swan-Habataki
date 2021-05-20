mt19937 mt(114514);
int rnd(int l, int r) {
    return uniform_int_distribution<int>(l, r)(mt);
}

namespace Quadratic_residue {
    int Wn, w, p;
    struct cp {
        int x, y;
        cp(double _r = 0, double _i = 0) : x(_r), y(_i) {}
    };
    cp operator*(const cp &ta, const cp &tb) {
        return cp(((ll) ta.x * tb.x % p + (ll) ta.y * tb.y % p * w % p) % p,
                  ((ll) ta.y * tb.x % p + (ll) ta.x * tb.y % p) % p);
    }
    inline cp powmod_cp(cp base, int times, int p) {
        cp ans = cp(1, 0);
        while (times) {
            if (times & 1) ans = ans * base;
            base = base * base;
            times >>= 1;
        }
        return ans;
    }
    void Qr(int n, int _p, int &x0, int &x1) {
        if (n == 0) {
            x0 = x1 = 0;
            return;
        }
        p = _p;
        if (powmod(n, (p - 1) >> 1, p) == p - 1) {
            x0 = -1, x1 = -1;
            return;
        }
        while (1) {
            Wn = rnd(0, p - 1), w = ((ll) Wn * Wn % p - n + p) % p;
            if (powmod(w, (p - 1) >> 1, p) == p - 1) break;
        }
        cp ans = powmod_cp(cp(Wn, 1), (p + 1) >> 1, p);
        x0 = min(ans.x, p - ans.x), x1 = max(ans.x, p - ans.x);
    }
}
using Quadratic_residue::Qr;

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        int n, p; scanf("%d%d", &n, &p);
        int x0, x1;
        Qr(n, p, x0, x1);
        if (x0 == -1 && x1 == -1) printf("Hola!"); // 无解
        else if (x0 == x1) printf("%d", x0); // 两解相同
        else printf("%d %d", x0, x1);   // mod p意义下的解
        printf("\n");
    }
}