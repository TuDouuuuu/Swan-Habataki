//矩阵快速幂
class mat{
public:
    int n,m;
    ll v[maxn][maxn];
    mat(int n,int m):n(n),m(m){}
    void init()
    {   
        memset(v,0,sizeof(v));
    }
    void init1()
    {
        for(int i=0;i<maxn;i++)
            for(int j=0;j<maxn;j++)
                v[i][j]=(i==j); //单位矩阵
    }
    mat operator* (const mat B) const//矩阵乘法 A(n,k)*B(k,m)=C(n,m);
    {
        mat C(n,B.m);
        C.init();
        for(int i=0;i<n;i++)
        for(int j=0;j<B.m;j++)
        for(int k=0;k<m;k++)
            C.v[i][j]=(C.v[i][j]+v[i][k]*B.v[k][j])%Mod;//Mod
        return C;
    }
    mat operator ^ (int t)//矩阵快速幂 n=m时可用 
    {
        mat ans(n,n),now(n,n);
        ans.init1();
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                now.v[i][j]=v[i][j];
        while(t>0)
        {
            if(t&1) ans=ans*now;
            now=now*now;
            t>>=1;
        }
        return ans;
    }
};