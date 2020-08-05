//最大公约      //建议直接__gcd()
ll gcd(ll a, ll b) {
	return b ? gcd(b, a % b) : a;
ll lcm(ll a, ll b) {
	return a * b / gcd(a, b);//可能会爆，快速乘
}//最大公倍
