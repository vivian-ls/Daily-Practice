#### 1.[码蹄集OJ-院落管理](https://www.matiji.net/exam/brushquestion/82/4693/305EE97B0D5E361DE6A28CD18C929AF0)

​		题意：给出n个节点，每个节点有一个权值，你需要把每个节点都分配到一个路径里面使得所有路径的和最终都小于给定的k，问最后能否实现这样的分配

​		我们给每一个节点定义一个属性used用来表示这个点以及它部分子树中的点构成的路径是否可以独立，如果为0也就是说它必须靠和父亲相连才可能满足要求，也就是之后加入的must数组，另一个属性may表示这个节点能否和父亲连接。赛时我自己和这个也差不多，但是漏了一个关键点就是当前节点的子节点中必须要和他相连的节点数等于1的时候，可能确实存在另一个子节点dp值是小于0的，并且加上这个值后可以构成一个链满足要求，然后这条链就不在和父亲连接了，但是是不对的，确实不和另一个子节点相连会导致这个节点的值比k大，但是这里只能确定它不是必须和父亲相连，因为有一个兜底的情况存在，但是不代表它不能和父亲相连，不懂就想想k为负数的时候，是不是就不太对了呢？正是这种情况导致了错误，我们开始就直接将它和另一个子节点相连了，导致父节点可能就满足不了要求了。同时这题dfs的写法值得学习

```c++
void solve(){
    int n, k;
    cin >> n >> k;
    vector<int> val(n + 1);
    fore(i, 1, n + 1) cin >> val[i];
    vector<vector<int>> p(n + 1);
    int u, v;
    fore(i, 1, n) {
        cin >> u >> v;
        p[u].emplace_back(v);
        p[v].emplace_back(u);
    }
    vector<int> dp(n + 1), used(n + 1), may(n + 1); // 是不是必须独立，是否能和父亲相连
    int flag = true;
    
    auto dfs = [&](auto &&dfs, int s, int fa) -> bool
    {
        vector<int> must, can;
        for(int to : p[s]) {
            if(to == fa) continue;
            if(dfs(dfs, to, s) == false) return false;
            if(!used[to]) must.push_back(dp[to]);
            else if(may[to]) can.push_back(dp[to]);
        }

        sort(can.begin(), can.end());
        if(must.size() > 2) {
            return false;
        }else if(must.size() == 2) {
            if(must[0] + must[1] + val[s] <= k) {
                used[s] = true;
            }
        }else if(must.size() == 1) {
            may[s] = true;
            dp[s] = val[s] + must[0];
            if(dp[s] <= k) used[s] = true;
            else if(can.size() >= 1 && dp[s] + can[0] <= k) used[s] = true;
        }else{
            may[s] = true;
            dp[s] = val[s];
            if(can.size() >= 1 && can[0] < 0) dp[s] += can[0];
            if(val[s] <= k) used[s] = true;
            else if(can.size() >= 1 && val[s] + can[0] <= k) used[s] = true;
            else if(can.size() >= 2 && val[s] + can[0] + can[1] <= k) used[s] = true;
        }
        if(s == 1 && used[s] == false) return false;
        if(used[s] == false && may[s] == false) return false;
       // cout << s << ' ' << used[s] << ' ' << may[s] << endl;
        return true;
    };
    cout << (dfs(dfs, 1, 0) ? "YES" : "NO") << endl;
}
```

#### 2.[码蹄集OJ-过园数统计](https://www.matiji.net/exam/brushquestion/83/4693/305EE97B0D5E361DE6A28CD18C929AF0)

​		题意：给出n个节点，有的节点权值是1，有的是0，问以每个节点为根时，每个权值为1的节点到这个根的值的种类数量

​		不难想到换根dp，但是我们需要一个容器可以进行集合合并操作以及范围所有数都加一的操作，写的多了自然可以想到bitset正好可以干这个事，合并就是bit1 ^ bit2，加一就是bit1 << 1，每个下标对应的值是一就代表存在这个数，count可以很方便统计，最后是换根的时候我们需要一个g数组用于存储删除这个点为根的子树的所有节点，保留这个节点的图的结果，之后正常转移即可

```c++
const int N = 30005;
int val[N];
vector<vector<int>> p(N);
bitset<30005> dp[N];
bitset<30005> g[N];
int ans[N];

void pre_dfs(int s, int fa) {
    if(val[s] == 1) dp[s][0] = 1;
    for(int to : p[s]) {
        if(to == fa) continue;
        pre_dfs(to, s);
        dp[s] |= (dp[to] << 1);
    }
};

void dfs(int s, int fa){
    vector<int> nxt;
    nxt.push_back(0);
    for(int to : p[s]) {
        if(to == fa) continue;
        nxt.push_back(to);
    }
    int m = nxt.size() - 1;
    vector<bitset<30005>> pre(m + 2), suc(m + 2);
    for (int i = 1; i <= m; i++)
        pre[i] = dp[nxt[i]] | pre[i - 1];
    for (int i = m; i >= 1; i--)
        suc[i] = suc[i + 1] | dp[nxt[i]];
    
    fore(i, 1, m + 1) {
        int to = nxt[i];
        g[to] = (g[s] << 1);
        if(i > 1) g[to] |= (pre[i - 1] << 2);
        if(i < m) g[to] |= (suc[i + 1] << 2);
        if(val[to] == 1)
            g[to][0] = 1;
        ans[to] = (g[to] | dp[to]).count();
    }
    for(int to : p[s]) {
        if(to == fa) continue;
        dfs(to, s);
    }
};
```

#### 3.[码蹄集OJ-誊改文书](https://www.matiji.net/exam/brushquestion/86/4693/305EE97B0D5E361DE6A28CD18C929AF0)

​		题意：给出一个有n个字母的字符串，只由A, B, C组成，每次操作可以实现A - B, A - C, B - C中的一个，问经过m次操作最多可以有多少种最终的可能

​		不难发现，确实可以对A连续进行2次操作最后变成C，但是似乎没有必要，操作次数是有限的，A无论最后需要变成什么都可以一步完成，根本没有必要多浪费一次操作，所以A就只有两种可能，一次变成B或者C，如果对A进行x此操作，A有a个，B有b个（C有多少个都无关，并且AB之间位置也无关），贡献就是$C(a, i) * 2^i * (C(b, m - i) + C(b, m - i - 1) ...)$后面是一个前缀和，因为前一个选了i次，后面可以0 ~ m - i 次吗，注意细节m - i 可能大于b，i 一定能取到m，A/B就算为0，一个都不选，方案也不是0，至少应该是1

```c++
const int N = 1e6 + 5;
int fac[N], inv[N], p[N];
void init(){
    fac[0] = inv[0] = 1;
    fore(i, 1, N + 1) fac[i] = fac[i - 1] * i % mod;
    inv[N] = fpow(fac[N], mod - 2);
    for (int i = N - 1; i >= 1; i--)
        inv[i] = inv[i + 1] * (i + 1) % mod;
    p[1] = 2;
    fore(i, 2, N + 1) p[i] = p[i - 1] * 2 % mod;
}
int A(int n, int m) {
    return fac[n] * inv[n - m] % mod;
}

int C(int n, int m) {
    return fac[n] * inv[m] % mod * inv[n - m] % mod;
}

void solve(){
    int n, m;
    cin >> n >> m;
    string s;
    cin >> s;
    int a = 0, b = 0;
    for(char c : s) {
        a += (c == 'A');
        b += (c == 'B');
    }
    int ans = 0;
    vector<int> pre(b + 1);
    pre[0] = 1;
    fore(i, 1, b + 1) {
        pre[i] = pre[i - 1] + C(b, i);
        pre[i] %= mod;
    }
    fore(i, 0, min(a, m) + 1) {
        int tmp = max(C(a, i) * p[i], 1ll) % mod * pre[min(b, m - i)] % mod;
        ans = (ans + tmp) % mod;
    }
    cout << ans << endl;
}
```

#### 4.[码蹄集OJ-宝玉的考验](https://www.matiji.net/exam/brushquestion/87/4693/305EE97B0D5E361DE6A28CD18C929AF0)

​		题意：给出一个有m条边的图，开始位于1号节点，有一些节点有特殊要求就是必须经过了某些点才能访问这个点，问最后到达n号节点的对短路经是多少

​		题目给出的特殊点的个数很少，可以想到状压，那么只需要在跑dj的时候加入一个状态看能不能到达这个点即可，注意加入vis数组防止重复访问同一个状态多次，剩下就是一些状压操作的细节了，要仔细看看

```c++
struct point{
    int val, cur, mas;
};
struct cmp{
    bool operator()(point a, point b) {
        return a.val > b.val;
    }
};
void init(){
    
}

void solve(){
    int n, m, k, t;
    cin >> n >> m >> k >> t;
    vector<vector<pii>> p(n + 1);
    int u, v, w;
    fore(i, 1, m + 1) {
        cin >> u >> v >> w;
        p[u].emplace_back(v, w);
        p[v].emplace_back(u, w);
    }
    map<int, int> mp, pre;
    fore(i, 1, k + 1) {
        cin >> u;
        mp[u] = i;
    }
    fore(i, 1, t + 1) {
        cin >> u >> v;
        pre[v] |= (1ll << mp[u]);
    }
    vector<vector<int>> dp(n + 1, vector<int>(1ll << (k + 1), lnf));
    vector<vector<int>> vis(n + 1, vector<int>(1ll << (k + 1), false));
    priority_queue<point, vector<point>, cmp> pq;
    if(mp.count(1)) {
        dp[1][1ll << mp[1]] = 0;
        pq.push({0, 1, 1ll << mp[1]});
    }else{
        dp[1][0] = 0;
        pq.push({0, 1, 0});
    }
    while(!pq.empty()) {
        auto [d, s, mas] = pq.top();
        pq.pop();
        if(vis[s][mas]) continue;
        vis[s][mas] = true;
        for(auto[to, w] : p[s]) {
            if(mp.count(to)) {
                if((mas & pre[to]) == pre[to] && dp[s][mas] + w < dp[to][mas | (1ll << mp[to])]) {
                    dp[to][mas | (1ll << mp[to])] = d + w;
                    pq.push({dp[to][mas | (1ll << mp[to])], to, mas | (1ll << mp[to])});
                }
            }else{
                if(dp[s][mas] + w < dp[to][mas]) {
                    dp[to][mas] = d + w;
                    pq.push({dp[to][mas], to, mas});
                }
            }
        }
    }
    int ans = lnf;
    k = (1 << (k + 1)) - 1;
    fore(i, 0, k + 1) ans = min(ans, dp[n][i]);
    if(ans == lnf)
        cout << "impossible" << endl;
    else
        cout << ans << endl;
}
```

#### 5.[码蹄集OJ-黛玉葬花](https://www.matiji.net/exam/brushquestion/89/4693/305EE97B0D5E361DE6A28CD18C929AF0)

​		题意：给出n个字符串，问每对字符串的最长公共前缀长度之和是多少

​		直接用hash计算即可，并不是很难，但是当时没学会qwq，这里使用的是双哈希，实际用但哈希并且自然溢出也能过

```c++
struct PairHash
{
    size_t operator()(pair<ull, ull> &p) const
    {
        auto hash1 = hash<ull>{}(p.first);
        auto hash2 = hash<ull>{}(p.second);
        return hash1 ^ (hash2 << 1);
    }
};

using ull = unsigned long long;
ull base = 131;
ull mod1 = 212370440130137957, mod2 = 1e9 + 7;

ull get_hash1(std::string s)
{
    int len = s.size();
    ull ans = 0;
    for (int i = 0; i < len; i++)
        ans = (ans * base + (ull)s[i]) % mod1;
    return ans;
}

ull get_hash2(std::string s)
{
    int len = s.size();
    ull ans = 0;
    for (int i = 0; i < len; i++)
        ans = (ans * base + (ull)s[i]) % mod2;
    return ans;
}
void solve(){
    int n;
    ull base = 131;
    cin >> n;
    unordered_map<pair<ull, ull>, int, cmp> mp;
    vector<string> s(n + 1);
    fore(i, 1, n + 1) cin >> s[i];
    fore(i, 1, n + 1) {
        int len = s[i].length();
        ull tmp1 = 0, tmp2 = 0;
        fore(j, 0, len) {
            tmp1 = tmp1 * base + (s[i][j] - 'a' + 1) % mod1;
            tmp2 = tmp2 * base + (s[i][j] - 'a' + 1) % mod2;
            mp[{tmp1, tmp2}]++;
        }
    }
    int ans = 0;
    fore(i, 1, n + 1) {
        int len = s[i].length();
        ull tmp1 = 0, tmp2 = 0;
        fore(j, 0, len) {
            tmp1 = tmp1 * base + (s[i][j] - 'a' + 1) % mod1;
            tmp2 = tmp2 * base + (s[i][j] - 'a' + 1) % mod2;
            ans = (ans + mp[{tmp1, tmp2}]) % mod;
        }
    }
    cout << ans << endl;
}
```

