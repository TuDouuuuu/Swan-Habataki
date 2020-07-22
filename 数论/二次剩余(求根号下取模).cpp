ll w;
ll mod;
struct num{
    ll x, y;
};
num mul(num a, num b) {
    num ans = {0, 0};
    ans.x = ((a.x * b.x % mod + a.y * b.y % mod * w % mod) % mod + mod) % mod;
    ans.y = ((a.x * b.y % mod + a.y * b.x % mod) % mod + mod) % mod;
    return ans;
}
ll powwi(num a, ll k) {
    num ans = {1, 0};
    while(k) {
        if(k & 1) ans = mul(ans, a);
        a = mul(a, a);
        k >>= 1;
    }
    return ans.x % mod;
}
ll powmod(ll a, ll b) {
    ll res = 1;
    a = a % mod;
    while(b) {
        if(b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}
ll solve(ll n) { 
    n %= mod;
    if(mod == 2) return n;
    if(powmod(n, (mod - 1) / 2) == mod - 1) return -1;
    ll a;
    while(1) {
        a = rand() % mod;
        w = ((a * a % mod - n) % mod + mod) % mod;
        if(powmod(w, (mod - 1) / 2) == mod - 1) break;
    }
    num x = {a, 1};
    return powwi(x, (mod + 1) / 2);
}
int main() {
	srand(time(0));
    int t;
    scanf("%d",&t);
    while(t--) {
        ll n;
        scanf("%lld%lld",&n,&mod);
        if(!n) {
        	printf("0\n");
			continue;
		}
        ll ans1=solve(n),ans2;
        if(ans1==-1) printf("不存在\n");
        else {
            ans2=mod - ans1;
            if(ans1 > ans2) swap(ans1,ans2);
            if(ans1 == ans2) printf("%lld\n",ans1);//解相等 
            else 
				printf("%lld %lld\n",ans1,ans2);
        }
    }
}
