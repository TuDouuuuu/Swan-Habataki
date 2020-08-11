//����ʽ
int c[N][N];
void init() {
	for(int i = 0; i < N; i++) {
		c[i][0] = c[i][1] = 1;
		for(int j = 1; j < i; j++) {
			c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
		}
	}
} 
//��ʽ��
ll powmod(ll a, ll b){
	ll res = 1;
	a %= mod;
	while(b) {
		if(b & 1) {
			res = res * a % mod;
		}
		b >>= 1;
		a = a * a % mod;
	}
	return res % mod;
}
ll fac[N], inv[N];
void init() {
	fac[0] = 1;
	for(int i = 1; i < N; i++) {
		fac[i] = fac[i - 1] * i % mod;
	}
	inv[N - 1] = powmod(fac[N - 1], mod - 2);
	for(int i = N - 2; i >= 0; i--) {
		inv[i] = inv[i + 1] * (i + 1) % mod;
	}
}
ll c(ll n, ll m) { // ���ݷ�Χ�ܴ󲻹� 
	if(m > n) {
		return 0;
	}
	if(m == 0) return 1;
	if(n < N) return fac[n] * inv[m] % mod * inv[n - m] % mod;
	//c(m,k) = m!/(k! * (m - k))= m-k+1~m/(k!)
	ll res = inv[m];
	for(int i = n - m + 1; i <= n; i++) {
		res = res * i % mod;
	}
	return res;
} 
