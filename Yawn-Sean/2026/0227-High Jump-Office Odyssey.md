#### [J. High Jump](https://codeforces.com/gym/104158/problem/J)

**题意：** 共有 $n$ 个人在比赛跳高，每个人最多可以跳多高已经给出了，一共有 $k$ 个初始高度都是1的高台，所有人开始都站在高台1上面。比赛一共有 $m$ 轮，每轮会将 $l, r$ 这个范围内的障碍物增加 $x$ 个高度，问每轮调整后有多少人可以获胜

实际上我们不用真的把区间内每个障碍物的高度都真的增加 $x_i$ ，每次都只会影响两次跳跃，如果 $h_i$ 代表 $a_{i + 1} - a_i$ ，那么影响的就是 $h_{l - 1}, h_r$

这样每次只要找到区间最大值即可，可以用线段树维护。按每个人可以跳的高度从小到大排序后二分找到第一个恰好可以跳过的人

tips : 统计这个数目可以用 vec.end() - lower_bound(...)，这样可以算出有多少人满足条件

```cpp
class SegTree{
private:
    int n;
    vector<int> a, info;
    void build(int i, int l, int r) {
        if(l == r)
            info[i] = a[l];
        else {
            int mid = (l + r) >> 1;
            build(i << 1, l, mid);
            build(i << 1 | 1, mid + 1, r);
            info[i] = max(info[i << 1], info[i << 1 | 1]);
        }
    }
    void set(int pos, int val, int l, int r, int i) {  
        if(pos < 1 || pos > n) return;
        if(l == r) {
            a[pos] = val;
            info[i] = val;
            return;
        }
        int mid = (l + r) >> 1;
        if(pos <= mid) set(pos, val, l, mid, i << 1);
        else set(pos, val, mid + 1, r, i << 1 | 1);
        info[i] = max(info[i << 1], info[i << 1 | 1]);
    }
    int query(int jobl, int jobr, int l, int r, int i) {
        if(jobl <= l && jobr >= r) return info[i];
        int mid = (l + r) >> 1, left = 0, right = 0;
        if(jobl <= mid) left = query(jobl, jobr, l, mid, i << 1);
        if(jobr > mid) right = query(jobl, jobr, mid + 1, r, i << 1 | 1);
        return max(left, right);
    }
public:
    SegTree(int n) : n(n), info((n << 2) + 1), a(n + 1, 0) {}
    void set(int pos, int val) { set(pos, val, 1, n, 1);}
    int query(int jobl, int jobr) {return query(jobl, jobr, 1, n, 1);}
    int get(int pos) {return a[pos];}
};

void solve(){
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> h(n + 1);
    fore(i, 1, n + 1) cin >> h[i];

    sort(h.begin() + 1, h.end());
    SegTree seg(k + 5);
    int l, r, x;
    fore(i, 1, m + 1) {
        cin >> l >> r >> x;
        if(l > 1) seg.set(l - 1, seg.get(l - 1) + x);
        seg.set(r, seg.get(r) - x);
        cout << h.end() - lower_bound(h.begin() + 1, h.end(), seg.query(1, k)) << endl;
    }
}
```

#### [K. Office Odyssey](https://codeforces.com/gym/104158/problem/K)

**题意：** 办公室一共有 $n$ 个房间和 $n - 1$ 个通道，共有 $m$ 个人参与办公室轮椅竞速，每个人的起点和终点都是 $s_i$ 和 $e_i$ 。如果两个人的路线经过同一个走廊或者房间说明这一对路线会产生冲突，找出一共有多少对路径有冲突

这个图是一棵树，必须知道的结论是在树上两个路径有交点，一定存在一条路径的 LCA 在另一条路径上

利用这个性质，统计当前路径上所有的点分别是多少条路径的 LCA 就可以得出与这条路径冲突的路径个数

这样算什么时候会重复呢？对于两条不相同的相交路径 $a, b$ 只会被统计一次， 处理 LCA 较深的路径时不会统计到更浅的路径。1.每条路径会多算一次自己 2.有多个路径 LCA 是同一个点时会重复统计，实际算出的是真实结果的两倍。结合以上两种，假如有 $k$ 个路径的 LCA 相同，多算的有 $\frac{k \times (k + 1)}{2}$

可以最后减去这些多算的但是要注意每个点只处理一次，更好的方式是在统计 cnt 的时候直接减掉，具体看代码

```cpp
const int MAXN = 2e5;
int deep[MAXN + 5], st[MAXN + 5][22 + 1];
class LCA{
private:
    int n, maxp;
    vector<vector<int>> adj;
    
public:
    LCA(int n) : n(n) {
        maxp = (int)log2(n);
        adj.resize(n + 1);
    }
    void add(int u, int v) { adj[u].emplace_back(v); }

    void dfs(int s, int f) {
        deep[s] = deep[f] + 1;
        st[s][0] = f;
        for (int p = 1; (1 << p) <= deep[s]; p++) st[s][p] = st[st[s][p - 1]][p - 1];
        for(int to : adj[s]) {
            if(to == f) continue;
            dfs(to, s);
        }
    }
    
    int find(int a, int b) {
        if(deep[a] < deep[b]) swap(a, b);
        for (int p = maxp; p >= 0; p--) {
            if(deep[st[a][p]] >= deep[b])
                a = st[a][p];
        }
        if(a == b) return a;
        for (int p = maxp; p >= 0; p--) {
            if(st[a][p] != st[b][p])
                a = st[a][p], b = st[b][p];
        }
        return st[a][0];
    }
};

void solve(){
    int n, m;
    cin >> n >> m;
    LCA lca(n);
    vector<vector<int>> p(n + 1);
    int u, v;
    fore(i, 1, n) {
        cin >> u >> v;
        p[u].emplace_back(v);
        p[v].emplace_back(u);
        lca.add(u, v);
        lca.add(v, u);
    }
    lca.dfs(1, 0);
    vector<pii> route(m + 1);
    vector<int> cnt(n + 1), l(m + 1), par(n + 1);
    int ans = 0;
    fore(i, 1, m + 1) {
        cin >> u >> v;
        route[i] = {u, v};
        l[i] = lca.find(u, v);
        cnt[l[i]]++;
        ans -= cnt[l[i]];
    }

    auto dfs = [&](auto&& dfs, int u, int fa) -> void {
        for(int v : p[u]) {
            if(v == fa) continue;
            par[v] = u;
            cnt[v] += cnt[u];
            dfs(dfs, v, u);
        }
    };
    dfs(dfs, 1, 0); 
    
    fore(i, 1, m + 1) {
        auto[u, v] = route[i];
        ans += cnt[u] + cnt[v] - cnt[l[i]];
        if(l[i] != 1) ans -= cnt[par[l[i]]];
    }
    cout << ans << endl;
}
```
