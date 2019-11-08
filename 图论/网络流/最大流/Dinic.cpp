//1.用BFS建立分层图 
//2.用DFS的方法寻找一条由源点到汇点的路径,获得这条路径的流量x. 
//根据这条路径修改整个图,将所经之处正向边流量减少x,反向边流量增加x 
//重复步骤2,直到DFS找不到新的路径时,重复步骤1
//时间复杂度O(n^2*m)
int bfs()
{
    memset(dis,-1,sizeof(dis));
    queue<node> q;
    q.push(node(1,0));
    dis[1] = 0;
    while(!q.empty()){
        node cur = q.front();
        q.pop();
        for(int i = first[cur.id];i!=-1;i = e[i].next){
            if(e[i].w == 0) continue;
            if(dis[e[i].v] == -1){
                dis[e[i].v] = cur.cost+1;
                q.push(node(e[i].v,dis[e[i].v]));
            }
        }
    }
    if(dis[n] == -1) return 0;
    return 1;
}
int dfs(int x,int low)
{
    if(x == n) return low;
    for(int i = first[x];i!=-1;i = e[i].next){
        int a = 0;
        if(e[i].w > 0&&dis[e[i].v] == dis[x]+1&&(a = dfs(e[i].v,min(low,e[i].w)))){
            e[i].w -= a;
            add(e[i].v,x,a);
            return a;
        }
    }
    return 0;
}
int main()
{
    init();
    scanf("%d%d",&n,&m);
    for(int i = 1;i <= m;i++){
      int u,v,w;
      scanf("%d%d%d",&u,&v,&w);
      add(u,v,w);
    }
    ll ans = 0;
    int sum;
    while(bfs()){
      while(sum = dfs(1,INF)){
        ans += sum;
      }
    }
    printf("Max flow: %lld\n",ans);
    return 0;
}