ll phi(ll n)
{
    ll ans = n;
    for (ll i = 2; i * i <= n; i++){
        if (n % i == 0){
            ans -= ans / i;         //这一步就是对应欧拉函数的通式  
            while (n % i == 0)  //为了保证完全消除我们刚才得到的那个i因子。
                n /= i;            //确保我们下一个得到的i是n的素因子。
        }
    }
    if (n > 1)              //如果还有素因子没有除
        ans -= ans / n;
    return ans;
}
