1. [CF1383A String Transformation 1 - 洛谷](https://www.luogu.com.cn/problem/CF1383A)
   题意：有两个字符串a, b，每次选择a中若干个相同的字母将 x 其修改为 y ，满足x < y，问最少多少次操作使得a = b，不可能输出-1

   将题目抽象成图的形式就是当存在a -> b，b -> c时a -> c 之间不再连边，用一个并查集维护即可，答案就是合并的次数

```c++
void solve() {
    int n;
    cin >> n;
    string a, b;
    cin >> a >> b;
    int ans = 0;
    DSU dsu(25);
    fore(i, 0, n) {
        if(a[i] > b[i]) {
            cout << -1 << endl;
            return;
        }
        if(dsu.merge(a[i] - 'a', b[i] - 'a')) ans++;
    }
    cout << ans << endl;
}
```

2. [Problem - 1360E - Codeforces](https://codeforces.com/problemset/problem/1360/E)
   题意：给一个n * n的网格，上侧和左侧分别有一排大炮，大炮会发射一个字符'1'，碰到边界或者其他的字符时停止移动，现给出一个最终的矩阵，问这样的矩阵能否被形成

   注意到只需判断前n - 1行和n - 1列的每一个'1'右侧和下侧是否有'1'即可

```c++
void solve() {
    int n;
    cin >> n;
    vector<string> a(n + 1);
    fore(i, 1, n + 1) {
        cin >> a[i];
        a[i] = " " + a[i];
    }
    fore(i, 1, n) fore(j, 1, n) {
        if(a[i][j] == '0') continue;
        if(a[i + 1][j] == '0' && a[i][j + 1] == '0') {
            cout << "NO" << endl;
            return;
        }
    }
    cout << "YES" << endl;
}
```

3. [Problem - 1365D - Codeforces](https://codeforces.com/problemset/problem/1365/D)
   题意：给出一个n * m的网格，里面有四种字符，'.', '#', 'G', 'B'，分别表示空地，墙壁，好人，坏人，你可以在任意空地放置墙壁，问最后能否使得所有好人都能够到达(n, m)，但是所有坏人都无法到达

   发现遇到坏人，那么最好就是在他四周都放上墙壁，不放就想的是不封住旁边的路，使得好人可以走，但是坏人因此也可以走这条路到终点了，所以最后还是得封上，所以不如开始就封上墙壁，最后从终点开始dfs，记录可以到达的点即可

```c++
void solve() {
    int n, m;
    cin >> n >> m;
    vector<string> a(n + 1);
    fore(i, 1, n + 1) {
        cin >> a[i];
        a[i] = " " + a[i];
    }
    fore(x, 1, n + 1) fore(y, 1, m + 1) {
        if(a[x][y] != 'B') continue;
        fore(i, 0, 4) {
            int xx = x + dx[i], yy = y + dy[i];
            if(xx < 1 || xx > n || yy < 1 || yy > m) continue;
            if(a[xx][yy] == '.') a[xx][yy] = '#';
            if(a[xx][yy] == 'G') {
                cout << "NO" << endl;
                return;
            }
        }
    }
    int flag = false;
    vector<vector<int>> vis(n + 1, vector<int>(m + 1, false));
    auto dfs = [&](auto &&dfs, int x, int y) -> void {
        vis[x][y] = true;
        fore(i, 0, 4) {
            int xx = x + dx[i], yy = y + dy[i];
            if(xx < 1 || xx > n || yy < 1 || yy > m) continue;
            if(a[xx][yy] == '#') continue;
            if(vis[xx][yy]) continue;
            dfs(dfs, xx, yy);
        }
    };
    if(a[n][m] != '#') dfs(dfs, n, m);
    fore(i, 1, n + 1) fore(j, 1, m + 1) {
        if(a[i][j] != 'G') continue;
        if(vis[i][j] == false) {
            cout << "NO" << endl;
            return;
        }
    }
    cout << "YES" << endl;
}
        
```

4. [Problem - 1204C -Anna, Svyatoslav and Maps](https://codeforces.com/problemset/problem/1204/C)
   题意：给出一个有n个顶点的图(邻接矩阵)，给出一个长为m的顶点序列，问这个序列最多可以删除多少个点，使得剩下的经过这些点的最短路序列和给出的m相同，例如原本给出1, 2, 3三个点，如果1->3的最短路必须经过2，那么这个2就可以删除，输出最后剩下点的个数以及这些点是什么

   题目n很小并且我们可能需要知道任意两个点之间的最短路，所以先跑一边floyd，然后遍历2 ~ m - 1之间的所有点，点k不能被删除的条件就是dis[u][v] < dis[u][x] + dis[x][v]，因为变了的话中间经过的点也就变了，用一个类似双指针的做法即可

```c++
void solve() {
    int n;
    cin >> n;
    vector<vector<int>> p(n + 1);
    vector<vector<int>> f(n + 1, vector<int>(n + 1, inf));
    fore(i, 1, n + 1) f[i][i] = 0;
    string s;
    fore(i, 1, n + 1) {
        cin >> s;
        fore(j, 0, n) if (s[j] == '1') {
            p[i].emplace_back(j + 1);
            f[i][j + 1] = 1;
        }
    }
    int m;
    cin >> m;
    vector<int> a(m + 1), ans;
    fore(i, 1, m + 1) cin >> a[i];

    fore(k, 1, n + 1) fore(i, 1, n + 1) fore(j, 1, n + 1)
        f[i][j] = min(f[i][j], f[i][k] + f[k][j]);

    ans.push_back(a[1]);
    int pre = a[1], cur = 0;
    fore(i, 2, m) {
        if(f[pre][a[i]] + f[a[i]][a[i + 1]] > f[pre][a[i + 1]]) {
            pre = a[i];
            ans.push_back(a[i]);
        }
    }
    ans.push_back(a[m]);
    cout << ans.size() << endl;
    for(int x : ans) cout << x << ' ';
    cout << endl;
}
```

5. [Problem - 1263D - Secret Passwords](https://codeforces.com/problemset/problem/1263/D)
   题意：给出n个由小写字母组成的字符串密码，a, b两个密码是等价的当且仅当某个字母同时出现在a, b中，或者存在c分别与a, b等价，输入等价的密码也可以进入系统，问最少需要多少次才能保证可以进入系统，已知这n个密码中只有一个密码是原始密码

   容易想到并查集，先用一个数组维护出某个字母在哪几个字符串中出现了，最后将这些并查集都合并，最后并查集块数就是答案

```c++
void solve() {
    int n;
    cin >> n;
    string s;
    vector<vector<int>> a(30);
    fore(i, 1, n + 1) {
        cin >> s;
        fore(j, 0, s.length()) a[s[j] - 'a' + 1].push_back(i);
    }
    DSU dsu(n + 1);
    fore(i, 1, 26 + 1) {
        fore(j, 1, a[i].size()) dsu.merge(a[i][j], a[i][0]);
    }
    int ans = 0;
    fore(i, 1, n + 1) ans += (dsu.find(i) == i);
    cout << ans << endl;
}
```

6. [Problem - 1324F - Maximum White Subtree](https://codeforces.com/problemset/problem/1324/F)
   题意：给出一个有n个点的树，每个有一个权值，为1则是白色，0就是黑色，求以每个点为根时最大的 cnt_1 - cnt_0 

   这种根不确定或者要求每个根的答案或者最大值的题目应考虑换根dp，我们把白色记为1，黑色记为-1，明显的是以1为根时$dp[1] = color_1 + \sum_{u\in p[1]}max(0, dp[u])$，但是每一个根都这么算肯定超时，记ans[i]为以 i 为时的答案，考虑跟的转移有$ans[i] = ans[f] - max(max(dp[i], 0), 0) + dp[i]$，这样就完成了转移，时间复杂度O(n)

```c++
void solve() {
    int n;
    cin >> n;
    vector<int> val(n + 1);
    fore(i, 1, n + 1) {
        cin >> val[i];
        if(val[i] == 0)
            val[i] = -1;
    }
    vector<vector<int>> p(n + 1);
    int u, v;
    fore(i, 0, n - 1) {
        cin >> u >> v;
        p[u].emplace_back(v);
        p[v].emplace_back(u);
    }
    vector<int> dp(n + 1), ans(n + 1);
    auto dfs1 = [&](auto &&dfs1, int s, int fa) -> void
    {
        dp[s] += val[s];
        for(int to : p[s]) {
            if(to == fa) continue;
            dfs1(dfs1, to, s);
            dp[s] += max(0ll, dp[to]);
        }
    };
    dfs1(dfs1, 1, 0);
    ans[1] = dp[1];
    auto dfs = [&](auto &&dfs, int s, int fa) -> void {
        for(int to : p[s]) {
            if(to == fa) continue;
            ans[to] = max(ans[s] - max(dp[to], 0ll), 0ll) + dp[to];
            dfs(dfs, to, s);
        }
    };
    dfs(dfs, 1, 0);
    fore(i, 1, n + 1) cout << ans[i] << " \n"[i == n];
}
```

7. [P3478 [POI 2008] STA-Station - 洛谷](https://www.luogu.com.cn/problem/P3478)
   题意：给出一个有n个点的树，输出一个根的编号，使得所有点的深度之和最大

   和第6题一样，一眼就是换根dp，并且转移方程非常简单，记录dp[i]表示以1为根时，i 的节点的深度之和，ans[i]为答案换根转移方程就是$ans[cur] = ans[fa] - dp[cur] + (n - dp[cur])$，列一个表达式可以发现，结果的变化就是cur的所有节点深度-1，$g_{fa}$的所有节点深度+1, $g_{fa}$表示删除fa的子树但保留fa的子图

```c++
void solve() {
    int n;
    cin >> n;
    vector<vector<int>> p(n + 1);
    int u, v;
    fore(i, 0, n - 1) {
        cin >> u >> v;
        p[u].emplace_back(v);
        p[v].emplace_back(u);
    }
    vector<int> dp(n + 1, 0);
    auto pdfs = [&](auto &&pdfs, int s, int fa) -> void
    {
        dp[s] = 1;
        for(int to : p[s]) {
            if(to == fa) continue;
            pdfs(pdfs, to, s);
            dp[s] += dp[to];
        }
    };
    pdfs(pdfs, 1, 0);
    fore(i, 1, n + 1) dp[i] -= 1;
  //  fore(i, 1, n + 1) cout << dp[i] << " \n"[i == n];
    vector<int> ans(n + 1);
    fore(i, 1, n + 1) ans[1] += dp[i];
    auto dfs = [&](auto &&dfs, int s, int fa) -> void {
        for(int to : p[s]) {
            if(to == fa) continue;
            ans[to] = ans[s] + n - 2 * dp[to];
            dfs(dfs, to, s);
        }
    };
    dfs(dfs, 1, 0);
    int maxn = -1, dir;
    fore(i, 1, n + 1) {
        if(ans[i] > maxn) {
            maxn = ans[i];
            dir = i;
        }
    }
    cout << dir << endl;
}
```

8. [P1273 有线电视网 - 洛谷](https://www.luogu.com.cn/problem/P1273)
   题意：给出n,m，表示有n个节点和m个用户终端，转播站编号为1 ~ n - m，第一个是根节点，用户终端编号为 n - m + 1 ~ n，接下来每行对应一个终端，k表示有多少个子节点，每一对a, c表示节点编号和传输费用，最后一行是每个用户愿意为此付的钱，问在不亏本的情况下最多可以使得多少用户可以观看比赛

   给出的有边权，实际都加到节点上就行，例如存在$u\to v$这条边，val[v] = w + a[v]（用户付的钱），剩下的就是一个树上背包问题，定义$dp[i][j]$表示考虑前 i 个节点，让 j 个用户收到信号的最少花费，不难发现给出的图所有用户都是叶子节点，剩下的都是转播站，所以当前节点是叶子节点的时候明显的转移方程就是选或者不选，$dp[i][j] = max(dp[i - 1][j - 1] + val[i], dp[i - 1][j])$，但是当前节点不是叶子节点时递推就变化很大，因为此时选择这个物品并不会增加 j 的值，并且如果不选择这个节点，那么它的所有子节点也选不了，这个可以用dfs的后续遍历快速实现，$dp[i][j] = max(dp[i - 1][j] + val[i], dp[i - sz[i]][j])$，为什么这里是dp[i - 1][j]，二不是j - 1就是因为此时选择不会增加j的值，对他没有影响
   [[笔记]树形dp - 2/4（树上背包类） - Sinktank - 博客园](https://www.cnblogs.com/Sinktank/p/18185282)

```c++
void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> val(n + 1);
    vector<vector<int>> p(n + 1);
    vector<int> sz(n + 1), id(n + 1);
    int a, c, k;
    fore(i, 1, n - m + 1) {
        cin >> k;
        while(k--) {
            cin >> a >> c;
            p[i].emplace_back(a);
            val[a] = -c;
        }
    }
    fore(i, 1, m + 1) {
        cin >> a;
        val[n - m + i] += a;
    }
    int tot = 0;
    auto dfs = [&](auto &&dfs, int s, int fa = 0) -> void
    {
        sz[s] = 1;
        for(int to : p[s]) {
            if(to == fa) continue;
            dfs(dfs, to, s);
            sz[s] += sz[to];
        }
        id[++tot] = s;
    };
    dfs(dfs, 1);
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, -inf));
    fore(i, 0, n + 1) dp[i][0] = 0;
    fore(i, 1, n + 1) {
        int u = id[i];
        fore(j, 1, m + 1) {
            if(u >= n - m + 1)
                dp[i][j] = max(dp[i - 1][j - 1] + val[u], dp[i - 1][j]);
            else
                dp[i][j] = max(dp[i - 1][j] + val[u], dp[i - sz[u]][j]);
        }
    }
    for(int i = m; i >= 1; i--) {
        if(dp[n][i] >= 0) {
            cout << i << endl;
            return;
        }
    }
}
```

9. [codeforces.com/problemset/problem/1369/D](https://codeforces.com/problemset/problem/1369/D)
   题意：给出一个阶段数n，输出最后有多少个爪形连通块，$a\to b, a\to c, a\to d$这种形状的，level 1 开始只有一个节点，问阶段n有多少个爪，升级按照下面规则，没有子节点加一个子节点，有一个子节点加两个子节点，有两个即以上跳过
   画个图可以发现一个基本的递推关系就是$f[n] = f[n - 1] + 2 * f[n - 2]$但是这样不对，发现如果n是3的倍数的时候会额外多增加一个点，所以得 +(n==3)
   
   ```c++
   int ans[2000005];
   void solve() {
       ans[0] = ans[1] = ans[2] = 0;
       ans[3] = 1;
       fore(i, 4, 2000005) {
           ans[i] = ans[i - 1] + (2 * ans[i - 2] % mod) + (i % 3 == 0);
           ans[i] %= mod;
       }
       int n, t;
       while(t--) {
           cin >> n;
           cout << (ans[n] * 4 % mod) << endl;
       }
   }
   ```

10. [CF1399E1 Weights Division (easy version) - 洛谷](https://www.luogu.com.cn/problem/CF1399E1)
    题意：给出一个有边权的树，你可以执行无数次操作将其中一条边的边权 w = w / 2，记S为从根节点1开始到所有叶子节点走过的边权之和，问最少要多少次操作可以使得S不大于题目给定的sum
    一眼就能看出来是一个优先队列问题，关键在与是什么优先，显然不应该是说 w * cnt 大的优先（例如53 * 2 > 15 * 7，但是明显减小后面的更优），所以我们优先级的判定应该是 $(w - w / 2) * cnt$，还有一个要注意的就是怎么统计每条边走过了多少次，当时写写了好久，这个要仔细看看
    
    ```c++
    void solve() {
        int n, sum;
        cin >> n >> sum;
        vector<vector<pii>> p(n + 1);
        int u, v, w;
        fore(i, 1, n) {
            cin >> u >> v >> w;
            p[u].emplace_back(v, w);
            p[v].emplace_back(u, w);
        }
        map<pii, int> mp;
        auto dfs = [&](auto &&dfs, int s, int fa) -> void {
            if(p[s].size() == 1){
                mp[{fa, s}] = 1;
            }
            for(auto[to, w] : p[s]) {
                if(to == fa) continue;
                dfs(dfs, to, s);
                mp[{fa, s}] += mp[{s, to}];
            }
    
        };
        dfs(dfs, 1, 0);
    
        priority_queue<tuple<int, int, int>> pq; // 贡献值，边权，次数
        int S = 0;
        auto dfs1 = [&](auto &&dfs1, int s, int fa) -> void {
            for(auto[to, w] : p[s]) {
                if(to == fa) continue;
                S += w * mp[{s, to}];
                pq.emplace((w - w / 2) * mp[{s, to}], w, mp[{s, to}]);
                dfs1(dfs1, to, s);
            }
        };
        dfs1(dfs1, 1, 0); 
        int ans = 0;
        while(S > sum) {
            auto[val, w, cnt] = pq.top();
            pq.pop();
            S -= val, w /= 2;
            pq.emplace((w - w / 2) * cnt, w, cnt);
            ans++;
        }
        cout << ans << endl;
    }
    ```

11. [CF1388C Uncle Bogdan and Country Happiness - 洛谷](https://www.luogu.com.cn/problem/CF1388C)
    题意：给出一个有n个点的树，1号节点表示公司其他表示职员的家，下班后所有职员都会回家，开始时心情可能好也可能坏，每走过一条公路心情可以变坏，但是不能变好，现在给出每个节点经过所有人员的幸福度，问这样的情况是否存在
    因为要知道经过一个节点的总人数，所以我们得从叶子节点开始思考，关键在于往上走的过程中和题目的要求就反过来了，心情只能变好，但是不能变坏，所以初始我们设置所有人心情都是坏的即可，也就是开心的人为0，dp数组在dfs过程中维护pair表示总人数和高兴的人的个数，每次到一个节点检查是否满足：高兴的人数不小于不小于子节点高兴人数之和，并且不超过总人数
    
    ```c++
    void solve() {
        int n, m;
        cin >> n >> m;
        vector<int> pp(n + 1), wf = pp;
        fore(i, 1, n + 1) cin >> pp[i];
        fore(i, 1, n + 1) cin >> wf[i];
        vector<vector<int>> p(n + 1);
        int u, v;
        fore(i, 1, n) {
            cin >> u >> v;
            p[u].emplace_back(v);
            p[v].emplace_back(u);
        }
        vector<pii> dp(n + 1);
        int flag = true;
        auto dfs = [&](auto &&dfs, int s, int fa) -> void
        {
            dp[s] = {pp[s], 0}; // 总人数，开心的人数
            for(int to : p[s])
            {
                if(to == fa) continue;
                dfs(dfs, to, s);
                dp[s].first += dp[to].first;
                dp[s].second += dp[to].second;
            }
           // cout << s << ' ' << dp[s].first << ' ' << dp[s].second << endl;
            int x = (dp[s].first + wf[s]);
            if(x & 1) flag = false;
            x /= 2;
            if(x < dp[s].second || x > dp[s].first)
                flag = false;
            dp[s].second = x;
        };
        dfs(dfs, 1, 0);
        cout << (flag ? "YES" : "NO") << endl;
    }
    ```

12. [CF1387B1 Village (Minimum) - 洛谷](https://www.luogu.com.cn/problem/CF1387B1)
    题意：给出一个有n个节点的树，每个边的边权都是1，每个节点都居住着一个村民，问让所有居民都搬到新家所需的最小花费是多少
    从叶子节点开始，如果自己没有被交换过，那么和自己的父亲换位置，如果是根节点没有父亲就随便和一个子节点交换即可
    
    ```c++
    void solve() {
        int n;
        cin >> n;
        vector<vector<int>> p(n + 1);
        int u, v;
        fore(i, 1, n) {
            cin >> u >> v;
            p[u].emplace_back(v);
            p[v].emplace_back(u);
        }
        vector<int> ans(n + 1);
        int cnt = 0;
        fore(i, 1, n + 1) ans[i] = i;
        auto dfs = [&](auto &&dfs, int s, int fa) -> void {
            for(int to : p[s]) {
                if(to == fa) continue;
                dfs(dfs, to, s);
            }
            if(s == 1) {
                if(ans[s] == s) {
                    cnt += 2;
                    swap(ans[s], ans[p[s][0]]);
                }
                return;
            }
            if(ans[s] == s) {
                cnt += 2;
                swap(ans[s], ans[fa]);
            }
        };
        dfs(dfs, 1, 0);
        cout << cnt << endl;
        fore(i, 1, n + 1) cout << ans[i] << " \n"[i == n];
    }
    ```

13. [CF1385E Directing Edges - 洛谷](https://www.luogu.com.cn/problem/CF1385E)
    题意：给出一个有n个点，m条边的图，里面有的边是有向的，有的是无向的，你需要给这些无向边指定一个方向使得整个图是有向且无环的
    有向无环图(DAG)有一个性质就是topo序小的节点指向topo序大的节点，可以先把所有有向边收集起来跑一个topo排序，之后对于每一条无向边判断是否有 topo[u] < topo[v] ，有则输出$u\to v$否则输出$v\to u$即可
    
    ```c++
    void solve() {
        int n, m;
        cin >> n >> m;
        int op, u, v;
        vector<vector<int>> p(n + 1);
        vector<pii> und;
        vector<int> ind(n + 1, 0);
        fore(i, 0, m) {
            cin >> op >> u >> v;
            if(op == 0) {
                und.emplace_back(u, v);
            }else{
                ind[v]++;
                p[u].emplace_back(v);
            }
        }
        vector<int> topo(n + 1);
        queue<int> q;
        fore(i, 1, n + 1) topo[i] = inf;
        int cur = 0;
        fore(i, 1, n + 1) if (ind[i] == 0) q.push(i);
        while(!q.empty()) {
            int u = q.front();
            q.pop();
            topo[u] = ++cur;
            for(int v : p[u]) {
                ind[v] -= 1;
                if(ind[v] == 0)
                    q.push(v);
            }
        }
        if(cur != n) {
            cout << "No" << endl;
        }else{
            cout << "Yes" << endl;
            fore(i, 1, n + 1) {
                for(int to : p[i])
                    cout << i << ' ' << to << endl;
            }
            for(auto[u, v] : und) {
                if(topo[u] < topo[v])
                    cout << u << ' ' << v << endl;
                else
                    cout << v << ' ' << u << endl;
            }
        }
    }
    ```

14. [CF1336A Linova and Kingdom - 洛谷](https://www.luogu.com.cn/problem/CF1336A)
    题意：给出含有n个节点的一棵树，1号节点表示首都，其他表示城市，现在要在k个城市发展工业，剩下的城市则发展旅游业，每个工厂都会派一名使者到首都，使者每经过一个旅游城市则增加一点心情，问心情总和最大是多少
    首先不难发现，选择的节点可能是当前最优的条件之一就是该节点的子节点都被选过了，不然肯定子节点更优啊，所以我们跑一边dfs记录下每个节点的深度和子树的大小，每个节点自己增加的贡献就是 $dep[i] - 1$但是同时会将所有子树节点的值减一，所以综合贡献就是$dep[i] - 1 - (sz[i] - 1)$，之后排序即可
    
    ```c++
    void solve() {
        int n, k;
        cin >> n >> k;
        vector<vector<int>> p(n + 1);
        int u, v;
        fore(i, 1, n) {
            cin >> u >> v;
            p[u].emplace_back(v);
            p[v].emplace_back(u);
        }
        vector<int> sz(n + 1);
        vector<int> dep(n + 1);
        vector<int> vis(n + 1, false);
        auto dfs = [&](auto &&dfs, int s, int fa) -> void
        {
            dep[s] = dep[fa] + 1;
            sz[s] = 1;
            for(int to : p[s]) {
                if(to == fa) continue;
                dfs(dfs, to, s);
                sz[s] += sz[to];
            }
        };
        dfs(dfs, 1, 0);
        vector<int> val(n + 1);
        fore(i, 1, n + 1) val[i] = dep[i] - 1 - (sz[i] - 1);
        sort(val.begin() + 1, val.end(), greater());
        int ans = 0;
        fore(i, 1, k + 1) ans += val[i];
        cout << ans << endl;
    }
    ```

15. [CF1187E Tree Painting - 洛谷](https://www.luogu.com.cn/problem/CF1187E)
    题意：给出一个有n个节点的树，初始所有节点都是白色，你可以选择从任意一个节点开始将其涂成黑色，之后只能选择与黑色相邻的白色节点将其涂成黑色，每次涂色前都会计算将被涂色的白色节点所在的白色联通块的大小，让最终的值加上这个大小，你的目标是最大化这个值
    明显的换根dp，但是开始没看出来，当我们需要计算以每个节点为根的情况时就应该考虑这个，发现从一个根转移到另一个根值的变化可以很容易得出，和之前一题很像
    
    ```c++
    void solve() {
        int n;
        cin >> n;
        vector<vector<int>> p(n + 1);
        vector<int> sz(n + 1);
        vector<int> dp(n + 1);
        int u, v;
        fore(i, 1, n) {
            cin >> u >> v;
            p[u].emplace_back(v);
            p[v].emplace_back(u);
        }
        auto dfs1 = [&](auto &&dfs1, int s, int fa) -> void
        {
            sz[s] = 1;
            for(int to : p[s]) {
                if(to == fa) continue;
                dfs1(dfs1, to, s);
                sz[s] += sz[to];
            }
            dp[1] += sz[s];
        };
        dfs1(dfs1, 1, 0);
    
        auto dfs = [&](auto &&dfs, int s, int fa) -> void {
            for(int to : p[s]) {
                if(to == fa) continue;
                dp[to] = dp[s] - sz[to] + n - sz[to];
                dfs(dfs, to, s);
            }
        };
        dfs(dfs, 1, 0);
        int maxn = -1;
        fore(i, 1, n + 1) {
            maxn = max(maxn, dp[i]);
        }
        cout << maxn << endl;
    }
    
    ```

16. [CF1249F Maximum Weight Subset - 洛谷](https://www.luogu.com.cn/problem/CF1249F)
    题意：给出一棵树，你可选择任意个点，但是必须满足两两之间的距离大于k，每个点有一个权值，输出最大的值的总和
    不难想到树上最大独立集问题，只是稍有变化，定义dp[u][k]为在以u为根的子树中，任意一个选择过的子节点到u的距离至少为k的结果的最大值，所以我们向上递归时枚举这个k也就是深度即可，dep == 0时有$dp[s][0]  = val[s] + dp[to][k - 1]$，为什么是k - 1？是因为到子节点距离为k - 1的话，到当前节点u的距离不就是k了吗，重点在于后面的怎么转移由于这些转移相当于是同时进行，但是实际是一个一个来的，所以不能直接修改数组，需要引入中间变量 dis = dp[to][dep - 1]; $dis += dis[v][max(dep - 1, k - dep - 1)]$，解释：v代表u的子节点，但是不是之前选择的to，为什么有一个max是根据状态定义来的
    
    ```c++
    void solve(){
        int n, k;
        cin >> n >> k;
        k += 1;
        vector<int> val(n + 1);
        fore(i, 1, n + 1) cin >> val[i];
        vector<vector<int>> p(n + 1);
        int u, v;
        fore(i, 1, n) {
            cin >> u >> v;
            p[u].emplace_back(v);
            p[v].emplace_back(u);
        }
        vector<vector<int>> dp(n + 1, vector<int>(k + 1));
        auto dfs = [&](auto &&dfs, int s, int fa) -> void
        {
            dp[s][0] = val[s];
            for(int to : p[s]) {
                if(to == fa) continue;
                dfs(dfs, to, s);
            }
    
            for (int dep = 0; dep < k; dep++) {
                if(dep == 0) {
                    for(int to : p[s]) {
                        if(to == fa) continue;
                        dp[s][0] += dp[to][k - 1];
                    }
                }else{
                    for(int to : p[s]) {
                        if(to == fa) continue;
                        int dis = dp[to][dep - 1];
                        for(int now : p[s]) {
                            if(now == to || now == fa) continue;
                            dis += dp[now][max(dep - 1, k - dep - 1)];
                        }
                        dp[s][dep] = max(dis, dp[s][dep]);
                    }
                }
            }
    
            for (int i = k - 2; i >= 0; i--) {
                dp[s][i] = max(dp[s][i], dp[s][i + 1]);
            }
        };
        dfs(dfs, 1, 0);
        cout << dp[1][0] << endl;
    }
    ```

17. [CF1304E 1-Trees and Queries - 洛谷](https://www.luogu.com.cn/problem/CF1304E)
    题意：给出一棵n个点的树，有q次询问，每次给出a, b, x, y, k，表示将x, y 连接起来后，a, b 之间有没有一条长为 k 的路径，每一个点或者边可以经过多次
    首先如果如果路径存在必须满足 $dis <= k $ 并且 $dis$ 和 $k$ 的奇偶性相同，新加入的边如果要影响结果那么就必须经过它，所以很自然就是有三条路径 1. a - b   2. a - x - y - b   3. a - y - x - b 后面两个奇偶性是一样的，唯一区别就是路径长度可能一个大于k一个小于k，用lca即可
    
    ```c++
    int dep[100005], st[100005][22 + 1];
    class LCA {
    public:
        int maxp, n;
        vector<vector<int>> adj;
        LCA(int n) : n(n), maxp((int)log2(n)), adj(n + 1) {}
        void add(int u, int v) { adj[u].emplace_back(v); }
        void dfs(int s, int fa) {
            dep[s] = dep[fa] + 1;
            st[s][0] = fa;
            for (int p = 1; (1ll << p) <= dep[s]; p++) {
                st[s][p] = st[st[s][p - 1]][p - 1];
            }
            for(int to : adj[s]) {
                if(to == fa) continue;
                dfs(to, s);
            }
        }
        int find(int a, int b) {
            if(dep[a] < dep[b]) swap(a, b);
            for(int p = maxp; p >= 0; p--) {
                if(dep[st[a][p]] >= dep[b])
                    a = st[a][p];
            }
            if(a == b) return a;
            for (int p = maxp; p >= 0; p--) {
                if(st[a][p] != st[b][p]) {
                    a = st[a][p], b = st[b][p];
                }
            }
            return st[a][0];
        }
        int dis(int a, int b) {
            return dep[a] + dep[b] - 2 * dep[find(a, b)];
        }
    };
    void solve(){
        int n, q, x, y, a, b, k;
        cin >> n;
        LCA lca(n);
        int u, v;
        fore(i, 1, n) {
            cin >> u >> v;
            lca.add(u, v);
            lca.add(v, u);
        }
        lca.dfs(1, 0);
        cin >> q;
        while(q--) {
            cin >> x >> y >> a >> b >> k;
            int ans1 = lca.dis(a, b);
            int ans2 = lca.dis(a, x) + 1 + lca.dis(y, b);
            int ans3 = lca.dis(a, y) + 1 + lca.dis(x, b);
            if((ans1 <= k && (ans1 - k) % 2 == 0) || (ans2 <= k && (ans2 - k) % 2 == 0) || (ans3 <= k && (ans3 - k) % 2 == 0)) {
                cout << "Yes" << endl;
            }else
                cout << "No" << endl;
        }
    }
    ```

18. [CF1322C Instant Noodles - 洛谷](https://www.luogu.com.cn/problem/CF1322C)
    题意：给定一张点数为 2n 的二分图，其中右侧的点有点权 ai​。从左侧选择一个非空点集 S，设 f(S) 表示右侧点中至少于左侧点有连边的点的点权和。求对所有的集合 S，f(S) 的 gcd。
    有一个结论是$gcd(a, b, c, d) = gcd(gcd(a, b), gcd(c, d)$所以对于右侧的每一个点对我们可以单独计算，简单一点说就是给出右侧的两个点的点权a, b，这个点对对结果有什么贡献？设T(s)是左侧和s有连边的点的集合，T(a) == T(b) 时这两个数是不可分开计算的，如果选了a，那么b也一定在同一个f(x)中被计算，所以此时这两个点就可以合并为一个大点，点的值为两个值的和，如果T(a) != T(b)呢？可能存在的情况有$gcd(a, b), gcd(a, b + a), gcd(a + 1, b)$但是这些其实都是gcd(a, b)，所以我们只需要处理那个重复的T(i) 即可，这个可以用加法hash实现
    
    ```c++
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    void solve(){
        int n, m;
        cin >> n >> m;
        vector<int> has(n + 1);
        vector<int> val(n + 1), buc(n + 1);
        fore(i, 1, n + 1) {
            cin >> val[i];
            has[i] = rng();
            buc[i] = 0;
        }
        int u, v;
        fore(i, 1, m + 1) {
            cin >> u >> v;
            buc[v] += has[u];
        }
        map<int, int> mp;
        fore(i, 1, n + 1) {
            mp[buc[i]] += val[i];
        }
        int res = 0;
        for(auto[x, y] : mp) {
            if(x == 0) continue;
            res = res ? gcd(res, y) : y;
        }
        cout << res << endl;
    }
    ```

19. [CF1328E Tree Queries - 洛谷](https://www.luogu.com.cn/problem/CF1328E)
    题意：给出一棵树，每次询问都给出k个点的编号，问是否存在一条从根节点1出发的路径使得这些节点要么在路径上，要么距离路径的距离是1
    翻译一下题目要求就是这个路径必须经过 x,  fa[x],  p[x] 中的一个，也就是必须经过父节点了，每次按深度将每个节点的父节点排序后看当前节点是否在上一个节点的子树中即可，dfn可以解决这个问题
    
    ```c++
    void solve(){
        int n, m;
        cin >> n >> m;
        vector<vector<int>> p(n + 1);
        int u, v;
        fore(i, 1, n) {
            cin >> u >> v;
            p[u].emplace_back(v);
            p[v].emplace_back(u);
        }
        vector<int> dep(n + 1), f(n + 1), dfn(n + 1), sz(n + 1);
        int tot = 0;
        auto dfs = [&](auto &&dfs, int s, int fa) -> void
        {
            f[s] = fa;
            sz[s] = 1;
            dep[s] = dep[fa] + 1;
            dfn[s] = ++tot;
            for(int to : p[s]) {
                if(to == fa) continue;
                dfs(dfs, to, s);
                sz[s] += sz[to];
            }
        };
        dfs(dfs, 1, 1);
        int k;
        while(m--) {
            cin >> k;
            vector<int> tmp(k + 1);
            int x;
            fore(i, 1, k + 1) {
                cin >> x;
                tmp[i] = f[x];
            }
            sort(tmp.begin() + 1, tmp.end(), [&](int a, int b)
                 { return dep[a] < dep[b]; });
            int flag = true;
            fore(i, 2, k + 1) {
                if(dfn[tmp[i]] >= dfn[tmp[i - 1]] && dfn[tmp[i]] <= dfn[tmp[i - 1]] + sz[tmp[i - 1]] - 1) continue;
                flag = false;
            }
            cout << (flag ? "Yes" : "No") << endl;
        }
    }
    ```

20. [CF1399E2 Weights Division (hard version) - 洛谷](https://www.luogu.com.cn/problem/CF1399E2)
    题意：给出一个数，每个边有一个权值和一个cost（1， 2），表示操作一次的费用，每次操作可以选择一条边将其权值w / 2，问使得从根节点到其他所有节点经过的权值之和小于给定的s最少花费是多少
    如果没有cost贪心完全可以，这里贪心就显得不太正确了，因为可能在cost = 2的操作确实贡献大，但是其实只需操作一个cost为1的边即可，这种就只能遍历了，记录两个数组，分别表示对所有cost为 c 的边操作 i 次后得到的值是多少，用一个双指针即可维护，有单调性
    
    ```c++
    void solve(){
        int n, s;
        cin >> n >> s;
        vector<vector<pii>> p(n + 1);
        vector<int> w(n), c(n);
        int a, b;
        fore(i, 1, n) {
            cin >> a >> b >> w[i] >> c[i];
            p[a].emplace_back(b, i);
            p[b].emplace_back(a, i);
        }
        vector<int> cnt(n);
        auto dfs = [&](auto &&dfs, int s, int fa) -> void {
            if(p[s].size() == 1)
                cnt[fa] = 1;
            for(auto[to, id] : p[s]) {
                if(id == fa) continue;
                dfs(dfs, to, id);
                cnt[fa] += cnt[id];
            }
        };
        dfs(dfs, 1, 0);
    
        auto fun = [&](int x) -> vector<int>
        {
            int sum = 0;
            priority_queue<pii> pq;
            fore(i, 1, n) {
                if(c[i] != x) continue;
                pq.emplace((w[i] - w[i] / 2) * cnt[i], i);
                sum += w[i] * cnt[i];
            }
            vector<int> ans;
            ans.push_back(sum);
            while(sum > 0 && !pq.empty()) {
                auto[val, id] = pq.top();
                pq.pop();
                sum -= val;
                ans.push_back(sum);
                w[id] /= 2;
                pq.emplace((w[id] - w[id] / 2) * cnt[id], id);
            }
            return ans;
        };
        vector<int> val_1 = fun(1);
        vector<int> val_2 = fun(2);
        int ans = inf;
        int pos = val_2.size() - 1;
        for (int i = 0; i < val_1.size(); i++) {
            while(pos > 0 && val_1[i] + val_2[pos - 1] <= s) pos--;
            if(val_1[i] + val_2[pos] <= s)
                ans = min(ans, i + pos * 2);
        }
        cout << ans << endl;
    }
    ```

