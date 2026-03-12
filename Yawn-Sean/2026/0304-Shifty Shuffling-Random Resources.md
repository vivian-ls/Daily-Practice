#### [Shifty Shuffling](https://codeforces.com/gym/104574/problem/E)

**题意:** 现在有一副扑克牌，一共52张4种花色。每种花色用 1 ~ 13 表示，问能否通过完美洗牌使得所有的 1 都在前半堆牌中。完美洗牌指的是前一半和后一半交叉摆放，前一半第一个作为开始

手玩可以知道情况不会很多，洗牌若干次后就会复原，所以枚举每一种情况即可，当回到初始状态时停止

```cpp
void solve(){
    vector<int> a(53);
    vector<int> ori;
    fore(i, 1, 52 + 1) {
        cin >> a[i];
        if(a[i] == 1) ori.emplace_back(i);
    }
    vector<int> tmp1 = ori, tmp2 = ori;
    while(true) {
        int flag = true;
        fore(i, 0, 4) {
            if(tmp1[i] > 26) flag = false;
            if(tmp1[i] <= 26) tmp2[i] = tmp1[i] * 2 - 1;
            else tmp2[i] = (tmp1[i] - 26) * 2;
        }
        if(flag) {
            cout << "YES" << endl;
            return;
        }
        tmp1 = tmp2;
        if(tmp1 == ori) {
            cout << "NO" << endl;
            return;
        }
    }
}
```

#### [Random Resources](https://codeforces.com/gym/103316/problem/J)

**题意：** 一个星球上共有 $n$ 个地区，每个地区的矿物数量是 $w_i$ 。你每次会随机选择两个地区 $u, v$ 然后到 $u~v$ 唯一路径上的所有地区采集矿物，最终收获是 $max(w_i) - min(w_j))$ 请你输出采集到的矿物的期望是多少

直接去算这个 $max(w_i) - min(w_j))$ 这个东西的期望肯定是算不了的，可以根据期望的可加性化简， $E(max - min) = E(max) - E(min)$

如何求 $E(max)$ ? 发现还可以化简成 $\frac{sum}{\binom{n}{2}}$ ，求出sum即可

要算每个数作为最大值的贡献，可以从小到大枚举，假设当前地区是 $u$ ，枚举所有 $u$ 的相邻节点 $v$ 。但是这个 $vis[v]$ 必须是 true，作用是保证当前是整个路线中的最大值。每次贡献就是 $size[u] * size[v] * val[u]$ ，算完后记得 merge 一下，这就是算 max 的操作，算 min 也是如此，顺序换一下即可

```cpp
void solve(){
    int n;
    cin >> n;
    vector<int> val(n + 1);
    fore(i, 1, n + 1) cin >> val[i];
    vector<vector<int>> p(n + 1);
    int u, v;
    fore(i, 1, n) {
        cin >> u >> v;
        p[u].emplace_back(v);
        p[v].emplace_back(u);
    }
    vector<int> order(n + 1);
    iota(order.begin(), order.end(), 0);
    sort(order.begin() + 1, order.end(), [&](int i, int j) {
        return val[i] < val[j];
    });

    int ans = 0;
    DSU dsu1(n);
    vector<int> vis(n + 1, false);
    fore(i, 1, n + 1) {
        int u = order[i];
        for(int v : p[u]) {
            if(!vis[v]) continue;
            ans = (ans + dsu1.size(u) * dsu1.size(v) % mod * val[u] % mod) % mod;
            dsu1.merge(u, v);
        }
        vis[u] = true;
    }
    
    DSU dsu2(n);
    fore(i, 1, n + 1) vis[i] = false;
    for(int i = n; i >= 1; i--) {
        int u = order[i];
        for(int v : p[u]) {
            if(!vis[v]) continue;
            ans = (ans + mod - dsu2.size(u) * dsu2.size(v) % mod * val[u] % mod) % mod;
            dsu2.merge(u, v);
        }
        vis[u] = true;
    }
    cout << ans * fpow(n * (n - 1) / 2, mod - 2, mod) % mod << endl;
}
```
