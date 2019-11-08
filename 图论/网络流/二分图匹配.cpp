int dfs(int u)
{
    for(int i = first[u];i!=-1;i = e[i].next){
        int v = e[i].to;
        if(!vis[v]){
            vis[v] = 1;
            if(linker[v]==-1||dfs(linker[v])){
                linker[v] = u;
                return 1;
            }
        }
    }
    return 0;
}
int hungary()
{
    int res =  0;
    memset(linker,-1,sizeof(linker));
    for(int  u = 1; u <= n;u++){
        memset(vis,0,sizeof(vis));
        if(dfs(u)){
            res++;
        }
    }
    return res;
}