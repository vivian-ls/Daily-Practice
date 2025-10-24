#### [J. Best division](https://codeforces.com/gym/102409/problem/J)

**题意：** 现在又一大块巧克力长度为L，存在N个分割点，你需要将他们分成四段使其最大的和最小的的差值最小

四块一共是三个分段点，开始想到了枚举中间的分段点，但是没想到两边怎么处理，实际上就是在分段点先前移动后如果还是不够一半就接着移动，直到再移动一格就会超过一半

但是这里并不是这个断点就是最好的，也可以是这一个的再前一个，这也一共又两个啊，前后加起来也就4种，枚举即可，并且这个题目有一个很好的性质就是每一段的长度就是这个端点的位置减去前一个断点的位置

```cpp
void solve(){
    int n, len;
    cin >> n >> len;
    vector<int> pos(n + 1);
    pos[0] = 0, pos[n] = len;
    fore(i, 1, n) cin >> pos[i];
    int p1 = 1, p2 = 3;
    int ans = len;
    fore(i, 2, n - 1) {
        while(pos[p1 + 1] <= pos[i] - pos[p1 + 1]) p1++;
        while(pos[p2 + 1] - pos[i] <= pos[n] - pos[p2 + 1]) p2++;

        for(int d1 = p1; d1 <= p1 + 1; d1++) {
            for(int d2 = p2; d2 <= p2 + 1; d2++) {
                int ma = max({pos[d1], pos[i] - pos[d1], pos[d2] - pos[i], pos[n] - pos[d2]});
                int mi = min({pos[d1], pos[i] - pos[d1], pos[d2] - pos[i], pos[n] - pos[d2]});
                ans = min(ans, ma - mi);
            }
        }
    }
    cout << ans << endl;
}
```

#### [D. Xor the graph](https://codeforces.com/gym/102419/problem/D) 🔥

**题意：** 给出一个n个点m条边的图，每个点有一个权值，你可以执行一次下面的操作，选择k个点，将这些所有点的权值都 ^ 上x，问这样能否使得最后所有边连接的两个点的权值都互不相同，不能输出-1，否则输出这些点以及x的值

实际上没有必要建整个图，只把有冲突的边留下即可，对这个新的图进行dfs，搜索的过程中记录下当前的状态，最后留下的图中每一个连通块点的权值都是相同的，你不能说我修改这个点的值，但是这个点周围的点也修改了，这样没有意义。可以发现不满足要求的就是环的长度为奇数时

最后那个x怎么找呢？x的范围并不大，用一个vis数组记录下哪些数选不了，枚举到第一个可以的就行

```cpp
void solve(){
    int n, m;
    cin >> n >> m;
    vector<int> val(n + 1);
    fore(i, 1, n + 1) cin >> val[i];
    vector<vector<int>> p(n + 1);
    vector<vector<int>> adj(n + 1);
    int u, v;
    fore(i, 1, m + 1) {
        cin >> u >> v;
        if(val[u] == val[v]) {
            p[u].emplace_back(v);
            p[v].emplace_back(u);
        }
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    vector<int> vis(n + 1, false), st(n + 1, 0);
    vector<int> ch;
    vector<int> can(1ll << 20, true);
    int flag = true;

    auto dfs = [&](auto&& dfs, int s, int cur = 0) -> void {
        vis[s] = true;
        if(p[s].size() == 0) return; 
        if(cur == 0) ch.emplace_back(s);
        st[s] = cur;
        for(int to : p[s]) {
            if(vis[to]) {
                if(st[to] == cur) flag = false;
                continue;
            }   
            dfs(dfs, to, cur ^ 1);
        }
    };
    fore(i, 1, n + 1) {
        if(vis[i]) continue;
        dfs(dfs, i, 0);
    }
    if(flag == false) {
        cout << -1 << endl;
    }else{
        for(int x : ch) {
            for(int to : adj[x]) can[val[to] ^ val[x]] = false;
        }
        int flag = false, x;
        fore(i, 0, (1ll << 20)) {
            if(can[i]) {
                x = i, flag = true;
                break;
            }
        }
        if(flag == false) {
            cout << -1 << endl;
        }else{
            cout << ch.size() << ' ' << x << endl;
            for(int x : ch) cout << x << ' ';
            cout << endl;
        }
    }
}
```
