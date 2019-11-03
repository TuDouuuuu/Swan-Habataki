typedef __int128 ll;
void exgcd(ll a,ll b,ll &g,ll &x,ll &y)
{
    if (b == 0) {
        g = a;
        x = 1;
        y = 0;
        return;
    }
    exgcd(b,a%b,g,y,x);
    y-=(a/b)*x;
}
bool china_flag;
ll a1,a2,n1,n2;
ll abs(ll x) {return x>0?x:-x;}
void china()
{
    ll d =a2-a1;
    ll g,x,y;
    exgcd(n1,n2,g,x,y);
    if (d%g==0)
    {
        x = ((x*d/g)%(n2/g)+(n2/g))%(n2/g);
        a1=x*n1+a1;
        n1=(n1*n2)/g;
    }
    else china_flag=true;
}
int n;
long long as[111];//n
long long ns[111];//从0开始
ll realchina()
{
    a1 = as[0];
    n1 = ns[0];
    for (ll i=1;i<n;i++)
    {
        a2 = as[i];
        n2 = ns[i];
        china();
        if(china_flag)  return -1;
    }
    return a1;
}