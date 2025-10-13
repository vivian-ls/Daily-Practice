1. [D-Grammar Test (grammar)_"影石Insta360杯"2025牛客暑期多校训练营10](https://ac.nowcoder.com/acm/contest/108307/D)

	​		题意：给出长度为n的bool数组，对于所有 i 从1 ~ n - 1，执行下面操作，问最后使得x, y值互换的这样的数组有多少个，下面前一个表示a[i]，后一个表示a[i + 1]，(1, 1) : x = x ^ x, (1, 0) : x = x ^ y,  (0,  1) : y = y ^ x, (0, 0) : y = y ^ y;

	​		不难发现如果这个序列在任何时候只要出现(1, 1) 或者(0, 0)其中一个的值就完全丢失了，不可能达成最后的条件，所以1, 0必须是交替出现，最后发现序列是每6个一个周期循环，且我们需要的结果在第四个，所以 n % 6 == 4 就输出2，其余输出0即可，代码就不写了

2. [E-Sensei and Affection (affection)_"影石Insta360杯"2025牛客暑期多校训练营10](https://ac.nowcoder.com/acm/contest/108307/E)

	​		题意：给出长度为n的序列，分别表示每位学生的好感度，每次操作可以选择一个 l, r 使得区间所有学生好感度加一，问最少多少次操作可以使得好感度种类只有m种(1或者2)

	​		如果m = 1那么就是一个明显的差分问题了，考虑记$a_0 = 0, a_{n + 1} = 0;d_i = a_i - a_{i - 1},(i \in (1, n + 1))$，每次操作就是在d里选一个正数一个负数然后正数减一负数加一（差分数组维护的核心思想，记住这个就没有问题），最后次数也就是$\sum_1^{n + 1}max(0, d_i)$也就是所有正数的和，但是正数和负数其实绝对值是相等的，也会写成先取绝对值相加最后除以2的方法

	```c++
	void solve(){
	    int n, m;
	    cin >> n >> m;
	    vector<int> a(n + 2);
	    fore(i, 1, n + 1) cin >> a[i];
	    if(m == 1) {
	        int maxn = 0;
	        fore(i, 1, n + 1) maxn = max(maxn, a[i]);
	        int ans = 0;
	        fore(i, 1, n + 1) a[i] = maxn - a[i];
	        fore(i, 1, n + 2) ans += abs(a[i] - a[i - 1]);
	        cout << ans / 2 << endl;
	        return;
	    }
	    int maxn = 0, minn = inf;
	    fore(i, 1, n + 1) maxn = max(maxn, a[i]), minn = min(minn, a[i]);
	    int ans = inf;
	    fore(x, minn, 200 + 1) {
	        fore(y, max(maxn, x), 200 + 1) {
	            array<int, 2> f{inf, inf};
	            if(a[1] <= x) f[0] = x - a[1];
	            f[1] = y - a[1];
	            fore(i, 2, n + 1) {
	                array<int, 2> g{inf, inf};
	                if(a[i] <= x) g[0] = min(f[1] + max((x - a[i]) - (y - a[i - 1]), 0ll),
	                                         f[0] + max((x - a[i]) - (x - a[i - 1]), 0ll));
	                g[1] = min(f[0] + max(y - a[i] - (x - a[i - 1]), 0ll),
	                           f[1] + max(y - a[i] - (y - a[i - 1]), 0ll));
	                f = g;
	            }
	            ans = min(ans, min(f[0], f[1]));
	        }
	    }
	    cout << ans << endl;
	}
	```


3. [I-Matrix (matrix)_"影石Insta360杯"2025牛客暑期多校训练营10](https://ac.nowcoder.com/acm/contest/108307/I)

	题意：构造一个矩阵使得 i + 1 的位置可以从值为 i 的位置通过上下左右四个方向任意一个移动 i 格到达

	不难发现对于同一行我们可以左右左右的填，可以保证一行能填满，关键是填满后怎么到下一行呢？这个利用了一个性质$\gcd(a, b) == 1$时在 k <= b - 1的时候每个 1 + (a * k) % b都是不一样的值，这里由于每次移动的距离是递增的 a, 2a, 3a…但是也和之前一样上下上下填就行了

	```c++
	void solve(){
	    int n, m;
	    cin >> n >> m;
	    if(gcd(n, m) != 1) {
	        cout << "NO" << endl;
	        return;
	    }
	    cout << "YES" << endl;
	    vector<vector<int>> ans(n, vector<int>(m));
	    int x = 0, y = 0;
	    int d = 1, dd = 1;
	    fore(i, 1, n * m + 1) {
	        ans[x][y] = i;
	        if(i % m == 0) {
	            if(dd == 1) {
	                x = (x + (i % n)) % n;
	            }else{
	                x = (x + n - (i % n)) % n;
	            }
	            dd ^= 1;
	        }else{
	            if(d == 1) {
	                y = (y + (i % m)) % m;
	            }else{
	                y = (y + m - (i % m)) % m;
	            }
	            d ^= 1;
	        }
	    }
	    fore(i, 0, n) fore(j, 0, m) cout << ans[i][j] << " \n"[j == m - 1];
	}
	```


4. [K-Amazing Sets (amazing)_"影石Insta360杯"2025牛客暑期多校训练营10](https://ac.nowcoder.com/acm/contest/108307/K)

	​        题意：给出有n个点的有向树，每个节点有一个权值，定义一个集合是“amazing”的当且仅当对于集合中每个元素，可以先从它到达的所有点也在集合中，每个集合的值是所有这些点权值之和，额外给出了m对 u, v，表示再在v -> u建一条边。保证开始u可以到达v，问最后的这个树的所有amazing集合的值的种类有多少个

	​        从题目要求来看本质就是一个树上集合合并的操作，题目给的所有节点的和又很小，可以想到bitset来作为合适的容器便于操作，设计合并又要用到启发式合并，关键是题目还有一些反边会设计到点的合并操作，我是理解了好久才学会。启发式合并体现在代码里面那个swap操作，可能会觉得这样会打乱原本集合之间关系，但是并不会，实在不理解就手写两个集合吧，还有一个特别的是树上的前缀标记但是我们是后续遍历，所以其实是负数，但是都没影响啦，这里体现了缩点操作，只有当pre[x]为0就代表这个点是缩点后的根节点，此时才可以加上这个点的贡献

	```c++
	const int N = 1e4 + 5;
	bitset<N> dp[N];
	int val[N], deg[N], pre[N];
	vector<vector<int>> p(N);
	
	void dfs(int s) {
	    for(int to : p[s]) {
	        dfs(to);
	        bitset<N> cur;
	        pre[s] += pre[to];
	        val[s] += val[to];
	        if(dp[s].count() > dp[to].count())
	            swap(dp[s], dp[to]);
	        cur |= dp[to];
	        fore(i, 0, 10000 + 1) {
	            if(dp[s][i])
	                cur |= (dp[to] << i);
	        }
	        dp[s] |= cur;
	    }
	    if(pre[s] == 0)
	        dp[s].set(val[s], 1);
	}
	void solve(){
	    int n;
	    cin >> n;
	    fore(i, 1, n + 1) cin >> val[i];
	    int u, v;
	    fore(i, 1, n) {
	        cin >> u >> v;
	        deg[v]++;
	        p[u].emplace_back(v);
	    }
	    int m;
	    cin >> m;
	    fore(i, 0, m) {
	        cin >> u >> v;
	        pre[u]++, pre[v]--;
	    }
	    int rt;
	    fore(i, 1, n + 1) if (deg[i] == 0) rt = i;
	    dfs(rt);
	    dp[rt][0] = 1;
	    cout << dp[rt].count() << endl;
	}
	```


5. [A-AVL tree_"影石Insta360杯"2025牛客暑期多校训练营9](https://ac.nowcoder.com/acm/contest/108306/A)

  题意：给出n个点的左右子节点，如果为0就是没有那一个节点，每次操作可以去除一个节点或者增加一个左节点或者右节点，问将这颗树变成一颗avl树最少需要多少次操作，一棵树是avl树当且仅当树为空或者$|h[l] - h[r]| <= 1$

  发现最大操作次数不可能大于n（把所有点全删了），所以可以得出我们如果考虑以某个点为根的子树的情况不用考虑很深的情况，大约最大就能到30左右，因为再深就超过最大值了，所以定义$dp[i][j]$表示以 i 为根的子树构成深度为 j 的avl树需要操作的最小次数

  ```c++
  void solve(){
      int n;
      cin >> n;
      vector<array<int, 2>> p(n + 1);
      int a, b;
      fore(i, 1, n + 1) {
          cin >> a >> b;
          p[i][0] = a, p[i][1] = b;
      }
      vector<vector<int>> dp(n + 1, vector<int>(30, inf));
      dp[0][0] = 0, dp[0][1] = 1;
      fore(i, 2, 30) dp[0][i] = dp[0][i - 1] + dp[0][i - 2] + 1;
      auto dfs = [&](auto &&dfs, int s) -> void
      {
          if(s == 0) {
              return;
          }
          dp[s][0] = 1, dp[s][1] = 0;
          fore(i, 0, 2) {
              dfs(dfs, p[s][i]);
              dp[s][0] += dp[p[s][i]][0];
              dp[s][1] += dp[p[s][i]][0];
          }
          int l = p[s][0], r = p[s][1];
          fore(i, 2, 30) {
              dp[s][i] = min(dp[s][i], dp[l][i - 1] + dp[r][i - 2]);
              dp[s][i] = min(dp[s][i], dp[l][i - 2] + dp[r][i - 1]);
              dp[s][i] = min(dp[s][i], dp[l][i - 1] + dp[r][i - 1]);
          }
      };
      dfs(dfs, 1);
      int ans = inf;
      fore(i, 0, 30) ans = min(ans, dp[1][i]);
      cout << ans << endl;
  }
  ```

6. [C-Epoch-making_"影石Insta360杯"2025牛客暑期多校训练营9](https://ac.nowcoder.com/acm/contest/108306/C)

  题意：给出n个程序，运行每个程序需要花费$w_i$的时间，部分程序有数个前置程序，必须等这些程序运行完后才能运行这个，现在你需要给这些程序分组，一组的全部运行完后运行下一组，运行所有程序最少花费多少时间

  只需要注意到一个性质，如果取了一个入度是 0 的权值大的点，其他入度为零的权值小的点都取了一定不会变劣，然后爆搜就可以了，这里运用了回溯，什么时候回溯？抓住关键：当前状态可以到达的所有后续状态都dfs搜索完毕了

  ```c++
  void solve(){
      int n, m;
      cin >> n >> m;
      vector<int> val(n + 1);
      fore(i, 1, n + 1) cin >> val[i];
      vector<vector<int>> p(n + 1);
      vector<int> deg(n + 1);
      int u, v;
      fore(i, 0, m) {
          cin >> u >> v;
          p[u].emplace_back(v);
          deg[v]++;
      }
      int ans = inf;
      auto dfs = [&](auto &&dfs, int mas, int t) -> void {
          if(mas == (1ll << (n + 1)) - 1) {
              ans = min(ans, t);
              return;
          }
          if(t >= ans) return;
          vector<pii> nxt;
          fore(i, 1, n + 1) {
              if(!((mas >> i) & 1) && !deg[i]) nxt.emplace_back(val[i], i);
          }
          vector tmp = deg;
          sort(nxt.begin(), nxt.end());
          int sz = nxt.size();
          for (int l = 0, r = 0; r < sz; r++, l = r) {
              while(r < sz - 1 && nxt[r + 1].first == nxt[l].first) r++;
              fore(i, l ,r + 1) {
                  mas |= (1ll << nxt[i].second);
                  for(int to : p[nxt[i].second])
                      deg[to] -= 1;
              }
              dfs(dfs, mas, t + nxt[l].first);
          }
          deg = tmp;
      };
      dfs(dfs, 1, 0);
      cout << ans << endl;
  }
  ```

7. [P3964 [TJOI2013\] 松鼠聚会 - 洛谷](https://www.luogu.com.cn/problem/P3964)

  曼哈顿距离和切比雪夫距离：从1 - 2的转化相当于坐标轴向左旋转$45^\circ$之后再拉伸$\sqrt2$倍

  将一个点(x,y)的坐标变为$(x + y, x - y)$后，原坐标系中的曼哈顿距离=新坐标系中的切比雪夫距离

  将一个点(x,y)的坐标变为$(\frac{x + y}{2}, \frac{x - y}{2})$后，原坐标系中的切比雪夫距离=新坐标系中的曼哈顿距离

  题意：给出n个点的坐标，找出一个点使得所有点到这点的切比雪夫距离最小，并输出这个值

  如果转为曼哈顿距离来计算的话最后的值可以使用前缀和优化计算，可以对x, y轴单独计算，并且最优的点一定再最大和最小的数之间，枚举每一个点计算即可（利用二分查找），直接套用公式

  ```c++
  void solve(){
      int n;
      cin >> n;
      vector<int> x(n + 1), y(n + 1);
      vector<pii> p(n + 1);
      int xx, yy;
      fore(i, 1, n + 1) {
          cin >> xx >> yy;
          x[i] = xx + yy;
          y[i] = xx - yy;
          p[i] = {x[i], y[i]};
      }
      sort(x.begin() + 1, x.end());
      sort(y.begin() + 1, y.end());
      vector<int> prex(n + 1), prey = prex;
      fore(i, 1, n + 1) {
          prex[i] = prex[i - 1] + x[i];
          prey[i] = prey[i - 1] + y[i];
      }
      int ans = inf;
      fore(i, 1, n + 1) {
          int idx = lower_bound(x.begin() + 1, x.end(), p[i].first) - x.begin();
          int idy = lower_bound(y.begin() + 1, y.end(), p[i].second) - y.begin();
          int tmp = x[idx] * idx - prex[idx] + prex[n] - prex[idx] - x[idx] * (n - idx);
          tmp += y[idy] * idy - prey[idy] + prey[n] - prey[idy] - y[idy] * (n - idy);
          ans = min(ans, tmp);
      }
      cout << ans / 2 << endl;
  }
  ```

8. [F-Military Training_"影石Insta360杯"2025牛客暑期多校训练营9](https://ac.nowcoder.com/acm/contest/108306/F)

  题意：pog开始两只脚位于 (x, y) 上，每次他可以以一只脚为圆心，另一只脚旋转$90^\circ$，这样算作一步，问到达(ex, ey)最少需要多少步

  画图表示出走 x 步可以到达的位置可以发现满足一个关系：两个点的中点的切比雪夫距离为 x 时就可以在 x 步到达

  ```c++
  void solve(){
      vector<int> a(9);
      fore(i, 1, 8 + 1) cin >> a[i];
      int x1 = a[1] + a[3], y1 = a[2] + a[4];
      int x2 = a[5] + a[7], y2 = a[6] + a[8];
      int ans = max(abs(x1 - x2), abs(y1 - y2));
      cout << ans << endl;
  }
  ```

9. [G-Permutation_"影石Insta360杯"2025牛客暑期多校训练营9](https://ac.nowcoder.com/acm/contest/108306/G)

	题意：给出一个有n个数的数组，每次操作可以删除最左侧和最右侧的一个数或者将当前数组最小的数添加到ans数组的末尾，问最后的ans数组一共有多少种可能

	首先考虑什么样的数组可能成立呢，不难想到就是为空或者以某个数结尾的数组，那么似乎枚举以每个数结尾的数组有多少个就可以，这里就要用到笛卡尔树的思想了，他可以让你知道第 i 个位置左边第一个小于 a[i] 的数的位置，右边同理（也可以是大于，小根堆就是大于，大根堆就是小于），但是这里也只是用到了思想，并不需要建这个数，关键：如果最后保证可以加入这个数的话，那么在笛卡尔树中至少就要删除除了以这个点为根的子树的所有其他的点，也就是说最后得到的 ans 数组有一个元素个数限制，$x \in [1, sz]$，（至少有一个这个数，想要加入这个最后的数必须进行的删除操作次数），所以问题就变成了我们有dep[i]个元素可以选择，我们每次可以选择[0, sz - 1]个（最后一个已经确定了！）这样的方案有多少个。
	$$
	求x_1 + x_2 + ... +x_{dpe[i]} + x_p = sz - 1 这个方程的解的个数，\tbinom{sz - 1 + dep[i]}{dep[i]}
	$$

	```c++
	const int N = 2e6 + 5;
	int fac[N], inv[N];
	void init(){
	    fac[0] = inv[0] = 1;
	    fore(i, 1, N + 1) fac[i] = fac[i - 1] * i % mod;
	    inv[N] = fpow(fac[N], mod - 2);
	    for (int i = N - 1; i >= 1; i--) {
	        inv[i] = inv[i + 1] * (i + 1) % mod;
	    }
	}
	int C(int n, int m) {
	    return fac[n] * inv[m] % mod * inv[n - m] % mod;
	}
	void solve(){
	    int n;
	    cin >> n;
	    vector<int> a(n + 1);
	    vector<int> st(n + 1), len(n + 1), pre(n + 1);
	    a[0] = -inf, st[0] = 0;
	    int pos = 0, top = 0;
	    fore(i, 1, n + 1) {
	        cin >> a[i];
	        while(a[i] < a[st[top]]) {
	            len[st[top]] = i - st[top - 1] - 1;
	            pre[i] -= 1, pre[st[top - 1] + 1]++;
	            top--;
	        }
	        st[++top] = i;
	    }
	    while(top > 0) {
	        len[st[top]] = n - st[top - 1];
	        pre[st[top - 1] + 1]++;
	        top--;
	    }
	    int ans = 0;
	    fore(i, 1, n + 1) {
	        pre[i] += pre[i - 1];
	        ans = (ans + C(len[i] + pre[i] - 1, pre[i])) % mod;
	    }
	    cout << ((ans + 1) % mod) << endl;
	}
	```


10. [L-Ping Pong_"影石Insta360杯"2025牛客暑期多校训练营9](https://ac.nowcoder.com/acm/contest/108306/L)

	题意：给出n个人的能力值，保证互不相同，开始一号在乒乓球桌上，之后按照2, 3, 4, 5…的顺序一次加入比赛，如果能力值小于另一个或者连续获胜n - 1次则添加到队列末尾，问进行k轮后每个人分别参与了比赛多少次

	我们手玩一下可以发现虽然前面没什么规律，但是不管怎么进行，一定会碰到第二大的和第一大的比赛二点情况，此时可以发现就进入了一个n * 2 - 2的轮次循环，最后剩下的再接着开始的模拟就行，但是要记得此时连胜初始值要是1

	```c++
	void solve(){
	    int n, k, fst = 0, sed = 0;
	    cin >> n >> k;
	    map<int, int> mp;
	    vector<int> val(n + 1);
	    fore(i, 1, n + 1) {
	        cin >> val[i];
	        if(val[i] > fst) {
	            sed = fst, fst = val[i];
	            mp[2] = mp[1], mp[1] = i;
	        }else if(val[i] > sed){
	            sed = val[i];
	            mp[2] = i;
	        }
	    }
	    vector<int> ans(n + 1);
	    queue<int> q;
	    int cur = 1, cnt = 0;
	    fore(i, 2, n + 1) q.push(i);
	    while(k--) {
	        int flag = false;
	        int nxt = q.front();
	        q.pop();
	        if(val[cur] == sed && val[nxt] == fst) flag = true;
	        ans[cur]++, ans[nxt]++;
	        if(val[cur] < val[nxt] || cnt == n - 1) {
	            q.push(cur);
	            cur = nxt, cnt = 1;
	        }else{
	            q.push(nxt);
	            cnt++;
	        }
	        if(flag) break;
	    }
	    int t = k / (n * 2 - 2), res = k % (n * 2 - 2);
	    int d = 0;
	    ans[mp[1]] += n * t, ans[mp[2]] += n * t;
	    fore(i, 1, n + 1) {
	        if(i != mp[1] && i != mp[2])
	            ans[i] += t * 2;
	    }
	    cnt = 1;
	    fore(i, 0, res) {
	        int nxt = q.front();
	        q.pop();
	        ans[cur]++, ans[nxt]++;
	        if(val[cur] < val[nxt] || cnt == n - 1) {
	            q.push(cur);
	            cur = nxt, cnt = 1;
	        }else{
	            q.push(nxt);
	            cnt++;
	        }
	    }
	    fore(i, 1, n + 1) cout << ans[i] << " \n"[i == n];
	}
	```

	





