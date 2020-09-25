void bfs() {
    queue<node> q;
    q.push(node(1, 1));
    int last = 1;
    while (!q.empty()) {
        node u = q.front(); q.pop();
        int nls = sa.insert(str[u.v]-'A', u.last);
        pos[u.v] = nls;
        for (int i = head[u.v]; ~i; i = e[i].nex) {
            int to = e[i].to;
            q.push(node(to, nls));
        }
    }
}

void dfs(int u, int last = 1) {
    pos[u] = last = sa.insert(str[u] - 'A', last);
    for (int i = head[u]; ~i; i = e[i].nex) {
        int v = e[i].to;
        dfs(v, last);
    }
}
