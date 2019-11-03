ll powmod(ll a,ll b,ll mod){
    ll P=1;
    a=a%mod;
    while(b){
        if(b&1) P=(P*(a%mod))%mod;
        a=(a*a)%mod;
        b>>=1;
    }
    return P; 
}