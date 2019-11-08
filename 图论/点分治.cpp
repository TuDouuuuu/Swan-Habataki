/*
    HYSBZ - 2152 计算两个点之间所有边上数的和加起来恰好是3的倍数的个数的概率
*/
const int SIZE=20050;
struct edge{//邻接表存数据
    int to,nex,w;
}e[SIZE*2];
int n,cnt,ans,rt,sum;
int head[SIZE],son[SIZE],f[SIZE],d[SIZE],t[5];
bool vis[SIZE];
void add(int x,int y,int w){//邻接表插入
    e[++cnt].to=y;e[cnt].nex=head[x];head[x]=cnt;e[cnt].w=w;
    e[++cnt].to=x;e[cnt].nex=head[y];head[y]=cnt;e[cnt].w=w;
}
void Get_Root(int x,int fa){
    son[x]=1;f[x]=0;
    for(int i=head[x];i;i=e[i].nex){
        if(!vis[e[i].to] && e[i].to != fa){
            Get_Root(e[i].to,x);
            son[x]+=son[e[i].to];
            f[x]=max(f[x],son[e[i].to]);
        }
    }
    f[x]=max(f[x],sum-son[x]);
    if(f[x]<f[rt])rt=x;
}
void Get_Deep(int x,int fa){
    t[d[x]]++;
    for(int i=head[x];i;i=e[i].nex)
        if(!vis[e[i].to] && e[i].to !=fa){
            d[e[i].to]=(d[x]+e[i].w)%3;
            Get_Deep(e[i].to,x);
        }
}
int cal(int x,int now){
    t[0]=t[1]=t[2]=0;
    d[x]=now;Get_Deep(x,0);
    return t[1]*t[2]*2+t[0]*t[0];
}
void find(int x){
    ans+=cal(x,0);
    vis[x]=1;
    for(int i=head[x];i;i=e[i].nex){
        if(!vis[e[i].to]){
            ans-=cal(e[i].to,e[i].w);
            rt=0;sum=son[e[i].to];
            Get_Root(e[i].to,0);
            find(rt);
        }
    }
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<n;i++){
        int u,v,w;scanf("%d%d%d",&u,&v,&w);w%=3;
        add(u,v,w);
    }
    f[0]=sum=n;
    Get_Root(1,0);
    find(rt);
    int t=__gcd(ans,n*n);
    printf("%d/%d",ans/t,n*n/t);
}