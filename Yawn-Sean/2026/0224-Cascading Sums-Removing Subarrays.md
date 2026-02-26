#### [A. Cascading Sums](https://codeforces.com/gym/104523/problem/A)

**题意：** 定义 $x$ 的级联和是 $x$ 的所有非空前缀的和，例如 2023 的级联和是 2023 + 202 + 20 + 2，给出一个 $n$ ，你需要给出所有 $m \le n$ 并且 $m$ 不是任何数的级联和的正整数 $m$ 的个数

一个数的级联和肯定比自己大，从 1 开始的数的级联和是递增的。每一个数对应的级联和都是一一映射的关系，所以只需要找到有多少个数表示的级联和小于 $n$ 也就得出了结果

这个可以用二分得出

```cpp
void solve(){
    int n;
    cin >> n;
    auto check = [&](int x) -> int {
        int ans = 0;
        while(x) {
            ans += x, x /= 10;
        }
        return ans <= n;
    };

    int l = 0, r = 1e18, mid;
    while(l < r) {
        mid = (l + r + 1) / 2;
        if(check(mid)) l = mid;
        else r = mid - 1;
    }

    cout << n - l << endl;
}
```

#### [D. Removing Subarrays](https://codeforces.com/gym/104523/problem/D)

**题意：** 你现在有一个数组 $a_1, a_2...a_n$ ，一个子数组 $a_l, a_{l + 1}...a_r$ 是好的当它满足以下条件

1.  $r-l+1 \geq 2$
2.  $\max(a_l, a_{l+1},...,a_r)-\min(a_l, a_{l+1},...,a_r) \leq k$

你可以一次删除任何好子数组 $a_l, a_{l+1},...,a_r$ 代价是 $\lfloor \frac{r-l+1}{2} \rfloor$ ，输出可以得到的数组最短是多少以及这样的最小花费

可以发现的是删除次数是无限的，所以如果要删除一个区间肯定可以将其分成长度是2, 3的小区间，并且费用是不会上升的。最后要处理的就是怎么找这些区间

这就是区间 dp 可以维护的东西， $dp[l][r]$ 表示删除 $a_l, a_{l + 1}...a_r$子数组的花费，费用是 inf 就是不可以删除。这个转移有三个方向

1. $l$ 和 $r$ 不是一起被删除的。所以存在一个 $i$ 作为分界点， $dp[l][r] = \mathop{min}\limits_{i = l}^{r - 1} (dp[l][i] + dp[i + 1][r])$
2. 是一起删除的，但是长度是2。 $dp[l][r] = dp[l + 1][r - 1] + 1$
3. 长度是3。此时要枚举第三个是谁 $dp[l][r] = \mathop{min}\limits_{i = l + 1}^{r - 1} (dp[l - 1][i - 1] + dp[i + 1][r - 1] + 1)$

最后还要单独统计一遍找出两个值，区间作为第一变量，费用第二变量

```cpp
void solve(){
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1);
    fore(i, 1, n + 1) cin >> a[i];
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, inf));

    fore(i, 1, n + 1) dp[i][i - 1] = 0;
    for(int len = 1; len < n; len++) {
        for(int l = 1; l + len <= n; l++) {
            int r = l + len;
            for(int i = l; i <= r - 1; i++) {
                dp[l][r] = min(dp[l][r], dp[l][i] + dp[i + 1][r]);
            }
            int maxn = max(a[l], a[r]);
            int minn = min(a[l], a[r]);
            if(maxn - minn <= k) dp[l][r] = min(dp[l][r], dp[l + 1][r - 1] + 1);
            for(int i = l + 1; i <= r - 1; i++) {
                if(max(maxn, a[i]) - min(minn, a[i]) <= k) {
                    dp[l][r] = min(dp[l][r], dp[l + 1][i - 1] + dp[i + 1][r - 1] + 1);
                }
            }
        }
    }

    vector<pii> ans(n + 1, {inf, inf});
    ans[0] = {0, 0};
    fore(i, 1, n + 1) {
        ans[i] = min(ans[i], {ans[i - 1].first + 1, ans[i - 1].second});
        for(int j = 1; j < i; j++) {
            if(dp[j][i] == inf) continue;
            ans[i] = min(ans[i], {ans[j - 1].first, ans[j - 1].second + dp[j][i]});
        }
    }
    cout << ans[n].first << ' ' << ans[n].second << endl;
}
```

