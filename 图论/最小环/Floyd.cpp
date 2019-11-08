int pos[MAXN][MAXN];//pos[i][j]:i到j的最短路的路径
vector<int> path;//最小环路径
int ans;//最小环
//ans == INF  说明无环
void getpath(int x,int y)
{
    if(!pos[x][y]) return;
    getpath(x,pos[x][y]);
    path.push_back(pos[x][y]);
    getpath(pos[x][y],y);
}
void floyd()
{
    ans = INF;
    memcpy(dist,g,sizeof(dist));
    for(int k = 1;k <= n;k++){
        for(int i = 1;i < k;i++){
            for(int j = i+1;j < k;j++){
                if(dist[i][j]+g[j][k]+g[k][i]<ans){
                    ans = dist[i][j]+g[j][k]+g[k][i];
                    ans.clear();
                    ans.push_back(i);
                    getpath(i,j);
                    ans.push_back(j);
                    ans.push_back(k);
                }
            }
        }
        for(int i = 1;i <= n;i++){
            for(int j = 1;j <= n;j++){
                if(dist[i][k]+dist[k][j]<dist[i][j]){
                    dist[i][j] = dist[i][k]+dist[k][j];
                    pos[i][j] = k;
                }
            }
        }
    }
}