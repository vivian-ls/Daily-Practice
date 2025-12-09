#### [D. John and President](https://codeforces.com/gym/104328/problem/D)

**题意：** 给出一颗有n个节点的数，每个点有一个权值，你需要输出能否找到一条链，链上的所有数都可以被一个常数x整除，并且这个链的长度大于 n/2，如果找不到输出no，找到输出yes

最后找到的x一定是质数最优，可以直接看范围内所有质数是否满足条件

对n个数来说，质因子次数之和最多是 $nlogM$ ，所以出现次数大于 n/2 的质数最多只有 $logM$ 个，所以复杂度是 $nlogM$ 的

统计最长链可以树形dp计算，每次只算这个点往下的最长链，最后符合要求的点可以挑两条链组合在一起。这里不用考虑向上的，后续一样会被计算

```cpp[]
void solve(){
    int n;
    cin >> n;
    vector<int> val(n + 1);
    fore(i, 1, n + 1) cin >> val[i];
    vector<vector<int>> adj(n + 1);
    int u, v;
    fore(i, 1, n) {
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    map<int, int> mp;
    fore(i, 1, n + 1) {
        int v = val[i];
        for(int p : prime) {
            if(p * p > v) break;
            if(v % p == 0) {
                while(v % p == 0) v /= p;
                mp[p] += 1;
            }
        }
        if(v > 1) mp[v] += 1;
    }
    vector<int> dp(n + 1);
    int p, max_len = 0;
    auto dfs = [&](auto &&dfs, int s, int fa) -> void
    {
        dp[s] = (val[s] % p == 0);
        int first = 0, second = 0;
        for(int to : adj[s]) {
            if(to == fa) continue;
            dfs(dfs, to, s);
            if(dp[to] > first) {
                second = first, first = dp[to];
            }else if(dp[to] > second) {
                second = dp[to];
            }
        }
        if(dp[s] == 0) return;
        dp[s] += first;
        max_len = max(max_len, dp[s] + second);
    };
    for(auto[cur, cnt] : mp) {
        if(cnt <= n / 2) continue;
        max_len = 0, p = cur;
        dfs(dfs, 1, -1);
        if(max_len > n / 2) {
            cout << "Yes" << endl;
            return;
        }
    }
    cout << "No" << endl;
}
```

#### [B. GPS Hack](https://codeforces.com/gym/104094/problem/B)

**题意：** 给出一个图，每条边都有一个权值，再给出一个起点和终点以及从起点到终点花费的时间，开始你位于起点s，GPS会在每个节点处告诉你按照最短路走的话应该选择那一条路，如果有多个选择就会随机给一个，但是现在有黑客出现了，他有一个修改显示的机会，修改后你到达d的时间就可能不是最短的了，你最后花了t分钟到达，问一共有多少种可能的路线

开始我们少想了一步，对于一对点我们只算了到u最短路为dis[x]有多少路线，但是v往后走也可能有很多条路时间是一样的

我们在跑dj的时候按照点遍历的顺序放到node数组中，dis计算的是每个点到终点d的对短路，从终点d开始计算到其他点的最短路径条数可以很容易用dp维护，因为node节点是有序的，后面的点到d的距离一定更大，但是反过来从s出发我们计算的就是从s到d的最短路的条数，只有最短路径上的点的数据才会被计算

最后遍历每条边，只要符合要求就把左右两侧的路径条数相乘

```cpp[]
void solve(){
    int n, m;
    cin >> n >> m;
    int st, ed, T;
    cin >> st >> ed >> T;
    vector<vector<pii>> p(n + 1);
    int u, v, w;
    fore(i, 1, m + 1) {
        cin >> u >> v >> w;
        p[u].emplace_back(v, w);
        p[v].emplace_back(u, w);
    }
    vector<int> dis(n + 1, inf);
    vector<int> vis(n + 1, false);
    vector<int> node;
    dis[ed] = 0;
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.emplace(0, ed);
    while(!pq.empty()) {
        auto [d, s] = pq.top();
        pq.pop();
        if(vis[s]) continue;
        vis[s] = true;
        node.emplace_back(s);
        for(auto[to, w] : p[s]) {
            if(dis[to] > d + w) {
                dis[to] = d + w;
                pq.emplace(dis[to], to);
            }
        }
    }
    vector<int> from(n + 1), to(n + 1);
    from[st] = to[ed] = 1;

    for(int u : node) {
        for(auto[v, w] : p[u]) {
            if(dis[v] - dis[u] == w)
                to[v] = (to[v] + to[u]) % mod;
        }
    }

    reverse(node.begin(), node.end());
    for(int u : node) {
        for(auto[v, w] : p[u]) {
            if(dis[u] - dis[v] == w)
                from[v] = (from[v] + from[u]) % mod;
        }
    }

    if(dis[st] == T) {
        cout << to[st] << endl;
        return;
    }

    int ans = 0;
    fore(u, 1, n + 1) {
        if(from[u] == 0) continue;
        for(auto[v, w] : p[u]) {
            if(dis[st] - dis[u] + w + dis[v] == T && u != ed)
                ans = (ans + from[u] * to[v]) % mod;
        }
        // 这里细节是到了终点不能再折返，确定u, v是通过走最短路到达的
    }
    cout << ans << endl;
}
```
