#### [Save the world? Save the cat!](https://codeforces.com/gym/106390/problem/B)

**题意：** Amy被困在多元宇宙中了，起源宇宙是 1 号宇宙，这个多元宇宙形状是一棵树，在相邻的宇宙穿梭需要时间 $w_i$ ，你可以使用至多一次跳跃，从 $i$ 跳跃到 $j$ 当 $d_i = d_j$ ， $d_i$ 是节点 i 到达起源宇宙需要穿过的隧道数，请输出从每个宇宙到 1 宇宙的最短时间

如果把这个树展开，发现一次超级跳跃就是在同一层传送，所以一层一层递归，每次维护每层最小值即可

注意必须写两次dfs，不然一层层的不好处理

假如当前在 $u$ ，是第 $i$ 层， ans[v] = min(layer[i + 1], ans[u] + w)

```cpp
void solve(){
    int n;
    cin >> n;
    vector<vector<pii>> p(n + 1);
    int u, v, w;
    fore(i, 1, n) {
        cin >> u >> v >> w;
        p[u].emplace_back(v, w);
        p[v].emplace_back(u, w);
    }
    vector<int> dp(n + 1, 0), deep(n + 1, inf);
    vector<int> ans(n + 1, inf);
    ans[1] = 0;
    deep[1] = 0;

    auto dfs = [&](auto&& dfs, int u, int fa, int t) -> void {
        for(auto[v, w] : p[u]) {
            if(v == fa) continue;
            dp[v] = dp[u] + w;
            deep[t + 1] = min(deep[t + 1], dp[v]);
            dfs(dfs, v, u, t + 1);
        }
    };

    dfs(dfs, 1, 0, 1);

    auto dfs1 = [&](auto&& dfs1, int u, int fa, int t) -> void {
        for(auto[v, w] : p[u]) {
            if(v == fa) continue;
            ans[v] = min(deep[t + 1], ans[u] + w);
            dfs1(dfs1, v, u, t + 1);
        }
    };
    dfs1(dfs1, 1, 0, 1);

    fore(i, 1, n + 1) cout << ans[i] << " \n"[i == n];
}
```

#### [Lazy](https://codeforces.com/gym/106391/problem/B)

**题意：** 给出一个包含 $n$ 个元素的数组，开始可以任意选择一个数字，之后经行 $n - 1$ 轮操作，每次可以选择一个已经选择过的数 $a_u$ 和一个没有被选过的数 $a_v$, 满足 $|a_u - a_v|$ 可以被 $x$ 整除, 问最后是否存在一个操作序列选择到所有的数

直接去挑元素完全处理不了，你不知道从哪个元素开始，后面元素怎么选也不好找。但是可以简化的是，两个数相减可以被 $x$ 整除说明这两个数关于 $x$ 同余

是否可以证明这个序列一定存在呢？用数学归纳法

1. 只有一个元素肯定可以
2. 假设前 $k$ 个元素可以构造出一个合法序列, 证明 $k + 1$ 也可以
3. 现在一共有 $k + 1$ 个数可以选择, 根据鸽巢原理，一定会有两个数此时关于 $x$ 是同余的，所以也可以构造出来

这样就证明了是一定可以找到这个序列的，至于怎么找就是按照上面的方法反推，当找到两个同余的数后挑一个作为新加的数

```cpp
void solve(){
    int n;
    cin >> n;
    cout << "Yes" << endl;
    cout << 1 << endl;
    vector<int> a(n + 1);
    fore(i, 1, n + 1) cin >> a[i];
    vector<int> used(n + 1, false);
    vector<pii> ans;
    for(int i = n - 1; i >= 1; i--) {
        vector<int> vis(n + 1, -1);
        fore(j, 1, n + 1) {
            if(used[j]) continue;
            int r = a[j] % i;
            if(vis[r] != -1) {
                ans.emplace_back(vis[r], j);
                used[j] = true;
                break;
            }else {
                vis[r] = j;
            }
        }
    }
    reverse(ans.begin(), ans.end());
    for(auto[x, y] : ans) cout << x << ' ' << y << endl;
}
```




