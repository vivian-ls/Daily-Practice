
#### [Volcanic Islands](https://codeforces.com/gym/106404/problem/H)

**题意：** 现在一共有 $n$ 个火山岛，每个火山岛都会在 $a_i$ 时刻喷发，火山岛之间由 $m$ 座桥连接。如果火山喷发会烧毁所有与之相连的桥，并且会产生岩浆在桥梁结构中扩散，如果扩散到一个新的岛屿，那么它也会被烧毁。桥梁的长度是 $w_i$ ，羊王开始在 1 号岛屿，问它是否可以安全到达 $n$ 号岛屿。

如果我们知道每个岛什么时候被烧毁也就可以通过一个带限制的最短路求出能够到达

定义 $d_i$ 是每座岛屿第一次被来自其他岛屿的岩浆侵袭的时刻，上面的时间 $t = min(d_i, a_i)$

这个 $d_i$ 也就是求一个多源最短路，一共有多个起点，问到达某个节点的最短时间，正好是这个题目的意思

具体做法就是设置一个超级原点，超级原点到每个基础原点的距离就是可以从这个点出发的时间，这里火山喷发是 $a_i$ 时刻，也就是这个 $a_i$ 最后直接跑一个单元最短路即可

tips : 新建的边可以不用物理建出来，可以在加入队列的时候处理

```cpp
void solve(){
    int n, m;
    cin >> n >> m;
    vector<vector<pii>> p(n + 1);
    vector<int> a(n + 1);
    fore(i, 1, n + 1) cin >> a[i];
    int u, v, w;
    fore(i, 1, m + 1) {
        cin >> u >> v >> w;
        p[u].emplace_back(v, w);
        p[v].emplace_back(u, w);
    }

    priority_queue<pii, vector<pii>, greater<pii>> pq;
    vector<int> vis(n + 1, false);
    fore(i, 1, n + 1) pq.emplace(a[i], i);
    while(!pq.empty()) {
        auto[d, u] = pq.top(); pq.pop();
        if(vis[u]) continue;
        vis[u] = true;
        for(auto [v, w] : p[u]) {
            if(a[u] + w < a[v]) {
                a[v] = a[u] + w;
                pq.emplace(a[v], v);
            }
        }
    }

    vector<int> dis(n + 1, inf);
    fill(vis.begin(), vis.end(), false);
    dis[1] = 0;
    pq.emplace(0, 1);
    while(!pq.empty()) {
        auto[d, u] = pq.top(); pq.pop();
        if(vis[u]) continue;
        vis[u] = true;
        for(auto[v, w] : p[u]) {
            if(dis[u] + w < dis[v] && dis[u] + w <= a[v]) {
                dis[v] = dis[u] + w;
                pq.emplace(dis[v], v);
            }
        }
    }

    cout << (dis[n] == inf ? "No\n" : "Yes\n");
}
```

#### [J. Balancing](https://codeforces.com/gym/106404/problem/J)

**题意：** 给出一个 $n \times m$ 的数字矩阵，每个位置可能有一个值或者没有值，也就是为0，每次询问都会给出一个小的矩形，问从这个矩形中选出三个数是否可能存在一组数满足 $a < b + c$ 

每个位置的值最大是 $10^6$ 假如存在很多数但是不满足，把所有的数从小到大排列，最优的情况也是 1, 1, 2, 3, 5 这是一个斐波那契数列，30个数的时候就会超过最大值，所以只有在数量小于30个的时候需要手动查找是否可以，否则一定是可以找出来的

具体的，用二维前缀和维护出每个区间元素的数量，并且对于每一行维护出下一个数的位置

```cpp
void solve(){
    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n + 1, vector<int>(m + 1));
    vector<vector<int>> cnt(n + 1, vector<int>(m + 1));
    fore(i, 1, n + 1) fore(j, 1, m + 1) {
        cin >> a[i][j];
        if(a[i][j]) cnt[i][j] = 1;
    }

    fore(i, 1, n + 1) fore(j, 1, m + 1) cnt[i][j] += cnt[i - 1][j];
    fore(i, 1, n + 1) fore(j, 1, m + 1) cnt[i][j] += cnt[i][j - 1];

    vector<vector<int>> nxt(n + 1, vector<int>(m + 1, -1));
    fore(i, 1, n + 1) {
        for(int j = m; j >= 1; j--) {
            if(j != m) nxt[i][j] = nxt[i][j + 1];
            if(a[i][j]) nxt[i][j] = j;
        }
    }

    auto cal = [&](int x1, int x2, int y1, int y2) -> int {
        return cnt[x2][y2] - cnt[x2][y1 - 1] - cnt[x1 - 1][y2] + cnt[x1 - 1][y1 - 1];
    };

    int q;
    cin >> q;
    while(q--) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        int sum = cal(x1, x2, y1, y2);
        if(sum > 30) {
            cout << "Yes" << endl;
            continue;;
        }
        vector<int> tmp;
        fore(x, x1, x2 + 1) {
            int y = nxt[x][y1];
            while(y != -1 && y <= y2) {
                tmp.emplace_back(a[x][y]);
                if(y == y2) break;
                y = nxt[x][y + 1];
            }
        }
        sort(tmp.begin(), tmp.end());
        int flag = false;
        int sz = tmp.size();
        for(int i = 0; i < sz - 2; i++) {
            if(tmp[i] + tmp[i + 1] > tmp[i + 2]) flag = true;
        }
        cout << (flag ? "Yes" : "No") << endl;
    }
}
```
