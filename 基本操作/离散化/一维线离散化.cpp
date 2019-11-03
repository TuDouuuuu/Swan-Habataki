struct LINE{
    int l,r;
}line[SIZE*16];
int lisan[SIZE*16];
void Discrete(int N){//bl存的是编号为[1,N]的线,在每个线段的尾部插入一个断点
    int lisantot=0;
    for(int i=1;i<=N;i++){
        lisan[lisantot++]=line[i].l;
        lisan[lisantot++]=line[i].r;
        lisan[lisantot++]=line[i].r+1;
    }
    sort(lisan,lisan+lisantot);
    int lisanlen=unique(lisan,lisan+lisantot)-lisan;
    for(int i=1;i<=N;i++){
        line[i].l=lower_bound(lisan,lisan+lisanlen,line[i].l)-lisan+1;
        line[i].r=lower_bound(lisan,lisan+lisanlen,line[i].r)-lisan+1;
    }
}