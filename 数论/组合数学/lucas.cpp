//n, m 较大， mod较小且为素数 
ll lucas(ll n, ll m) {
	if(m == 0) {
		return 1;
	}
	else {
		return c(n % mod, m % mod) * lucas(n / mod, m / mod) % mod;
	}
}
