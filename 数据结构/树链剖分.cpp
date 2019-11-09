int sum[MAXM*4],add[MAXM*4];
int a[MAXM],n;
int idx;
int first[MAXM];
struct edge{
	int v,next;
}e[MAXM*2];
int f[MAXM],son[MAXM],size[MAXM],dfn[MAXM],dep[MAXM],top[MAXM],seq[MAXM];
int cnt;
int mod;
/*
f�ǽڵ�ĸ���,son���ض���,size���Ըýڵ�Ϊ����������С,dfn�Ǹ��ڵ����±��ϵ����.
seq����dfn�෴������,��ʾ�굽������ű�ʾ��ԭ�ڵ�,top��Ŀǰ�ڵ��������Ķ���.
dep�ǽ������
*/
//---------------------�ӱߺ�Ԥ����--------------------------------
void eadd(int a,int b)
{
	e[idx].v = b;
	e[idx].next = first[a];
	first[a] = idx++;
}
void init()
{
    memset(first,-1,sizeof(first));
    idx = 1;
    cnt = 0;
}
void dfs1(int u,int fa,int depth)
{
	f[u] = fa; size[u] = 1; dep[u] = depth;
	int maxson = -1;
	for(int i = first[u];i != -1;i = e[i].next){
		int v = e[i].v;
		if(v == fa) continue;
		dfs1(v,u,depth+1);
		size[u] += size[v];
		if(size[v]>maxson) son[u] = v,maxson = size[v];
	}
}
void dfs2(int u,int t)
{
	top[u] = t;
	dfn[u] = ++cnt;
	seq[cnt] = a[u];
	if(!son[u]) return;
	dfs2(son[u],t);
	for(int i = first[u];i != -1;i = e[i].next){
		int v = e[i].v;
		if(v != son[u]&&v != f[u]) dfs2(v,v);
    }
}


//--------------------------�߶���----------------------------------
void pushup(int rt)
{
	sum[rt] = (sum[rt<<1]+sum[rt<<1|1])%mod;
}
void build(int l,int r,int rt)
{
	if(l == r){
		sum[rt] = seq[l]%mod;
		return;
	}
	int m = (l+r)>>1;
	build(l,m,rt<<1);
	build(m+1,r,rt<<1|1);
	pushup(rt);
}
void pushdown(int rt,int ln,int rn)
{
	if(add[rt]){
		add[rt<<1] = (add[rt<<1] + add[rt])%mod;
		add[rt<<1|1] = (add[rt<<1|1] + add[rt])%mod;
		sum[rt<<1] = (sum[rt<<1] + add[rt]*ln%mod)%mod;
		sum[rt<<1|1] = (sum[rt<<1|1] + add[rt]*rn%mod)%mod;
		add[rt] = 0;
	}
}
void update(int L,int R,int C,int l,int r,int rt)
{
	if(L <= l&&r <= R){
		sum[rt] = (sum[rt] + C*(r-l+1)%mod)%mod;
		add[rt] = (add[rt] + C)%mod;
		return;
	}
	int m = (l+r)>>1;
	pushdown(rt,m-l+1,r-m);
	if(L <= m) update(L,R,C,l,m,rt<<1);
	if(R >  m) update(L,R,C,m+1,r,rt<<1|1);
	pushup(rt);
}

ll query(int L,int R,int l,int r,int rt)
{
	if(L <= l&&r <= R){
		return sum[rt];
	}
	int m = (l+r)>>1;
	pushdown(rt,m-l+1,r-m);
	ll ans = 0;
	if(L <= m) ans = (ans + query(L,R,l,m,rt<<1))%mod;
	if(R >  m) ans = (ans + query(L,R,m+1,r,rt<<1|1))%mod;
	return ans;
}


//----------------------------���ϼӡ��������---------------------
void tadd(int x,int y,int k)
{
    while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]]) swap(x,y);
        update(dfn[top[x]],dfn[x],k,1,n,1);
        x = f[top[x]];
    }
    if(dep[x]>dep[y]) swap(x,y);
    update(dfn[x],dfn[y],k,1,n,1);
}
ll tsum(int x,int y)
{
    ll ans = 0;
    while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]]) swap(x,y);
        ans = (ans + query(dfn[top[x]],dfn[x],1,n,1))%mod;
        x = f[top[x]];
    }
    if(dep[x]>dep[y]) swap(x,y);
    ans = (ans + query(dfn[x],dfn[y],1,n,1))%mod;
    return ans;
}


int main()
{
	int m;
	int num;//���ڵ����
	scanf("%d%d%d%d",&n,&m,&num,&mod);
	init();
	for(int i = 1;i <= n;i++){
        scanf("%d",&a[i]);
	}
	for(int i = 1;i <= n-1;i++){
        int u,v;
        scanf("%d%d",&u,&v);
        eadd(u,v);
        eadd(v,u);
	}
	dfs1(num,0,1);
	dfs2(num,num);
	build(1,n,1);
	for(int i = 1;i <= m;i++){
        int op;
        scanf("%d",&op);
        if(op == 1){//������x��y�ڵ����·�������нڵ��ֵ������z
            int x,y,z;
            scanf("%d%d%d",&x,&y,&z);
            tadd(x,y,z%mod);
        }
        else if(op == 2){//������x��y�ڵ����·�������нڵ��ֵ֮��
            int x,y;
            scanf("%d%d",&x,&y);
            printf("%lld\n",tsum(x,y));
        }
        else if(op == 3){//����xΪ���ڵ�����������нڵ�ֵ������z
            int x,z;
            scanf("%d%d",&x,&z);
            update(dfn[x],dfn[x]+size[x]-1,z%mod,1,n,1);
        }
        else if(op == 4){//����xΪ���ڵ�����������нڵ�ֵ֮��
            int x;
            scanf("%d",&x);
            printf("%lld\n",query(dfn[x],dfn[x]+size[x]-1,1,n,1)%mod);
        }
	}
	return 0;
}
