#define _EXT_CODECVT_SPECIALIZATIONS_H 1
#define _EXT_ENC_FILEBUF_H 1
#undef __MINGW32__

#include<bits/stdc++.h>
#include<bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;
typedef long long ll;

class PBDS {
private:
    typedef tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update> Tree;
    Tree T;
public:
    void insert(ll x, int id) { // 插入x数，需传入第几次操作进行简单处理
        T.insert((x << 20) + id);    // 简单的处理
    }

    void remove(ll x) { // 删除x数(若有多个相同的数，因只删除一个)
        T.erase(T.lower_bound(x << 20));
    }

    ll get_rank(ll x) { // 查询x数的排名(排名定义为比当前数小的数的个数+1)
        return T.order_of_key(x << 20) + 1;
    }

    ll get_val(ll x) {  // 查询排名为x的数
        return *T.find_by_order(x - 1) >> 20;
    }

    ll get_pre(ll x) {  // 求x的前驱(前驱定义为小于x，且最大的数)
        return *--T.lower_bound(x << 20) >> 20;
    }

    ll get_next(ll x) { // 求x的后继(后继定义为大于x，且最小的数)
        return *T.lower_bound((x + 1) << 20) >> 20;
    }
} rbt;  // 注意不能叫tree, 否则会冲突