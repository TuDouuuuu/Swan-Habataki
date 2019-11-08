struct edge{
    int v,next,w;
}e[MAXM*2];
void add(int a,int b,int c)
{
    e[idx].v = b;e[idx].w = c;
    e[idx].next = first[a];
    first[a] = idx++;
}
void init()
{
    memset(first,-1,sizeof(first));
    idx = 1;
}