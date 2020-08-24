class FHQ {
public:
    const int MAXM = 50 * MAXN; // 50倍注意！
    int ch[MAXM][2];
    int dat[MAXM], siz[MAXM], val[MAXM];
    int tot, root;

    void init() {   // 初始化
        tot = 0;
        root = 0;
        siz[0] = val[0] = 0;
    }

    inline void push_up(int rt) {   // 传递信息
        siz[rt] = siz[ch[rt][0]] + siz[ch[rt][1]] + 1;
    }

    inline int New(int v) { // 新建一个节点，value = v
        val[++tot] = v;
        dat[tot] = rand();
        siz[tot] = 1;
        ch[tot][0] = ch[tot][1] = 0;
        return tot;
    }

    inline int Copy(int rt) {   // 复制点的信息
        int newnode = ++tot;
        val[tot] = val[rt], dat[tot] = dat[rt], siz[tot] = siz[rt];
        ch[tot][0] = ch[rt][0], ch[tot][1] = ch[rt][1];
        return newnode;
    }

    inline int merge(int x, int y) {    // 合并
        if (!x || !y) return x + y;
        if (dat[x] < dat[y]) {
            int newnode = Copy(x);
            ch[newnode][1] = merge(ch[newnode][1], y);
            push_up(newnode);
            return newnode;
        } else {
            int newnode = Copy(y);
            ch[newnode][0] = merge(x, ch[newnode][0]);
            push_up(newnode);
            return newnode;
        }
    }

    inline void split(int rt, int v, int &x, int &y) { // 按照权值进行分裂
        if (!rt) x = y = 0;
        else {
            if (val[rt] <= v) {
                x = Copy(rt);
                split(ch[x][1], v, ch[x][1], y);
                push_up(x);
            } else {
                y = Copy(rt);
                split(ch[y][0], v, x, ch[y][0]);
                push_up(y);
            }
        }
    }

    void del(int &rt, int v) {  // 删除value为v的数
        int x = 0, y = 0, z = 0;
        split(rt, v, x, z);
        split(x, v - 1, x, y);
        y = merge(ch[y][0], ch[y][1]);
        rt = merge(x, merge(z, y));
    }

    void insert(int &rt, int v) {   // 插入value为v的数
        int x = 0, y = 0, z = 0;
        split(rt, v, x, y);
        z = New(v);
        rt = merge(x, merge(z, y));
    }

    int get_val(int rt, int k) {    // 得到第k大的数（从小到大）的value
        if (k == siz[ch[rt][0]] + 1) return val[rt];
        else if (k <= siz[ch[rt][0]]) return get_val(ch[rt][0], k);
        else return get_val(ch[rt][1], k - siz[ch[rt][0]] - 1);
    }

    int get_Kth(int &rt, int v) {   // 查询v的排名
        int x, y;
        split(rt, v - 1, x, y);
        int ans = siz[x] + 1;
        rt = merge(x, y);
        return ans;
    }

    int get_pre(int &rt, int v) {   // 求前驱，若不存在返回-2147483647
        int x, y, ans;
        split(rt, v - 1, x, y);
        if (!x) return -2147483647;
        ans = get_val(x, siz[x]);
        rt = merge(x, y);
        return ans;
    }

    int get_next(int &rt, int v) {  // 求后驱，若不存在返回2147483647
        int x, y, ans;
        split(rt, v, x, y);
        if (!y) return 2147483647;
        ans = get_val(y, 1);
        rt = merge(x, y);
        return ans;
    }
} tree;

int root[MAXN];

int main() {
    int q;
    scanf("%d", &q);
    tree.init();
    for (int i = 1; i <= q; i++) {
        int ver, opt, x;
        scanf("%d%d%d", &ver, &opt, &x);
        root[i] = root[ver];
        switch (opt) {
            // 插入x
            case 1: tree.insert(root[i], x); break; 
            // 删除x（若有多个相同的数，应只删除一个，如果没有请忽略该操作）
            case 2: tree.del(root[i], x); break; 
            // 查询x的排名（排名定义为比当前数小的数的个数+1）
            case 3: printf("%d\n", tree.get_Kth(root[i], x)); break;
            // 查询排名为x的数
            case 4: printf("%d\n", tree.get_val(root[i], x)); break;
            // 求x的前驱（前驱定义为小于x，且最大的数，如不存在输出-2147483647）
            case 5: printf("%d\n", tree.get_pre(root[i], x)); break;
            // 求x的后继（后继定义为大于x，且最小的数，如不存在输出2147483647）
            default: printf("%d\n", tree.get_next(root[i], x));
        }
    }

}