#### [D. Colorful Paths](https://codeforces.com/gym/104855/problem/D)

**题意：** 给出一个有 $n$ 个点和 $m$ 条边的图，第 $i$ 条边的颜色是 $a_i$，如果一条路径（不一定是一条简单的路径）没有两条相同颜色的连续边，我们就称它为彩色路径。查找所有节点 $x$ ，使得存在从 1 到 $x$ 的彩色路径。

注意这里是图而不是树，进行 dfs 处理的时候必须判断什么时候才可以继续往深递归

题目是相邻的边颜色不同即可，可以发现如果有两种不同的颜色都可以到达同一个点，那么就一定可以往后走。后续再有新的颜色也不用处理了，这样每个点最多只会遍历 2 次

只需要记录上一条边的颜色即可

```cpp
void solve(){
    int n, m;
    cin >> n >> m;
    int u, v, col;
    vector<vector<pii>> p(n + 1);
    fore(i, 1, m + 1) {
        cin >> u >> v >> col;
        p[u].emplace_back(v, col);
    }

    vector<vector<int>> dp(n + 1, vector<int>(2, -1));
    dp[1][0] = dp[1][1] = 0;

    auto dfs = [&](auto&& dfs, int u, int cur) -> void {
        for(auto[v, col] : p[u]) {
            if(col == dp[u][cur]) continue;
            if(dp[v][0] == -1) {
                dp[v][0] = col;
                dfs(dfs, v, 0);
            }else if(col == dp[v][0]) {
                continue;
            }else if(dp[v][1] == -1) {
                dp[v][1] = col;
                dfs(dfs, v, 1);
            }
        }
    };

    dfs(dfs, 1, 0);
    fore(i, 1, n + 1) {
        if(dp[i][0] != -1) cout << i << ' ';
    }
    cout << endl;
}
```

#### [E. javelins](https://codeforces.com/gym/106151/problem/E)

**题意：** 运动场上共有 $n$ 个标靶，每个标靶有一个基础难度 $a_i$ 和疲劳系数 $b_i$ ，如果是第 $j$ 次击中某个标靶，花费的能量是 $a_i + (j - 1) * b_i$ ，问在总能量不超过 $B$ 的情况下最多击中的标靶数以及因此花费的能量

如果确定了最后要选择哪些标靶的话，肯定是按 $b_i$ 从大到小排序累加就是结果，但是选哪些呢就要用到 dp 了

定义 dp[i][j] : 考虑到第 $i$ 个标靶，选了 $j$ 个，dp[i][j] = min(dp[i - 1][j], dp[i - 1][j - 1] + cost)

最后遍历所有的 dp[n][i] 即可，代码压了一维，不然会超空间

```cpp
void solve(){
    int n, sum;
    cin >> n >> sum;
    vector<int> a(n + 1), b(n + 1);
    fore(i, 1, n + 1) cin >> a[i];
    fore(i, 1, n + 1) cin >> b[i];

    vector<int> order(n + 1);
    iota(order.begin(), order.end(), 0);
    sort(order.begin() + 1, order.end(), [&](int i, int j) {
        return b[i] > b[j];
    });

    int ans = 0, maxn = -1;
    vector<int> dp(n + 1, inf);
    dp[0] = 0;

    fore(i, 1, n + 1) {
        for(int j = i; j >= 1; j--) {
            int cost = a[order[i]] + b[order[i]] * (j - 1);
            if(dp[j - 1] + cost <= sum) 
                dp[j] = min(dp[j], dp[j - 1] + cost);
        }
    }
    
    for(int i = n; i >= 0; i--) {
        if(dp[i] <= sum) {
            cout << i << ' ' << dp[i] << endl;
            return;
        }
    }
}
```
