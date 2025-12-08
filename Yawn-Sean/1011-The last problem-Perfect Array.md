#### [L. The last problem](https://codeforces.com/gym/103708/problem/L)

**题意：** 给出一个有n个数的数组， $f(i)$ 表示val[i]作为最大值所在区间所有数的和，对每一个 $f(i)$ 求和后输出

这种推式子题一定要化简，不然很难算

对于每个 i 它的贡献都是可以单独计算的，维护出左右两侧第一个比自己大的数用单调栈很容易实现，一次维护左边，一次维护右边

左侧的选法相当于是求 $[],[a_{i-1}],[a_{i-2},a_{i-1}],\dots,[a_{left[i]+1},\dots,a_{i-1}]$ 的子数组和的和。这个算出来再乘以右边选法数量就是左边的贡献

每个 $a_j$ 在上述求和都被计算了 $j-left[i]$ 次。

所以我们只需求 $\sum\limits_{j=left[i]+1}^{i-1}(j-left[i])nums[j]=\sum\limits_{j=left[i]+1}^{i-1}j\times nums[j]-left[i]\sum\limits_{j=left[i]+1}^{i-1}nums[j]$ 。

于是只需维护 $nums[j]$ 和 $j\times nums[j]$ 的前缀和即可。

🔔数组中可能有相同元素单调栈就必须左右各跑一次，不然可以只跑一遍

```cpp[]
void solve(){
    int n;
    cin >> n;
    vector<int> val(n + 1), left(n + 1), right(n + 1);
    fore(i, 1, n + 1) cin >> val[i];
    
    vector<int> stk;

    stk = {0};
    for (int i = 1; i < n + 1; i ++) {
        while (stk.back() != 0 && val[stk.back()] <= val[i])
            stk.pop_back();
        left[i] = stk.back();
        stk.emplace_back(i);
    }

    stk = {n + 1};
    for (int i = n; i >= 1; i --) {
        while (stk.back() != n + 1 && val[stk.back()] <= val[i])
            stk.pop_back();
        right[i] = stk.back();
        stk.emplace_back(i);
    }

    int ans = 0;
    vector<int> pre1(n + 2); // sum of i
    fore(i, 1, n + 2) pre1[i] = pre1[i - 1] + val[i], pre1[i] %= mod;

    vector<int> pre2(n + 2); // sum of i * val[i]
    fore(i, 1, n + 2) pre2[i] = pre2[i - 1] + val[i] * i, pre2[i] %= mod;


    fore(i, 1, n + 1) {
        ans += val[i] * (i - left[i]) % mod * (right[i] - i) % mod;
        ans %= mod;

        int a = (pre2[i - 1] - pre2[left[i]] + mod) % mod;
        int b = (pre1[i - 1] - pre1[left[i]] + mod) % mod * left[i] % mod;
        ans += (a - b + mod) % mod * (right[i] - i) % mod;
        ans %= mod;

        a = (pre1[right[i] - 1] - pre1[i] + mod) % mod * right[i] % mod;
        b = (pre2[right[i] - 1] - pre2[i] + mod) % mod;
        ans += (a - b + mod) % mod * (i - left[i]) % mod;
        ans %= mod;
    }
    cout << ans << endl;
}
```
#### [H. Perfect Array](https://codeforces.com/gym/103785/problem/H)

**题意：** 给出一个有n个数的数组，为是否可以通过下面操作得到
-  $i$ 从1开始一直到n，每次可以选择一个 $p \in [1, i]$ 在p处插入一个值为p的数

问这样的数组是否可以得到

又是一个正难则反的问题，不妨考虑这个已经有的数组怎么还原回去

最后一次添加的数一定是 val[i] = i 的位置，如果有多个那么就是最后的那个，如果是前面的后面的都会被往后推一步，就产生矛盾了

每次暴力找一个这样的位置最后倒序输出这个顺序就是结果，找不到就是不行

```cpp[]
void solve(){
    int n;
    cin >> n;
    vector<int> a(n + 1);
    fore(i, 1, n + 1) cin >> a[i];
    vector<int> ans;
    for (int i = n; i >= 1; i--) {
        int flag = false;
        for (int j = i; j >= 1; j--) {
            if(a[j] == j) {
                flag = true;
                ans.emplace_back(j);
                a.erase(a.begin() + j);
                break;
            }
        }
        if(flag == false) {
            cout << "NO" << endl;
            return;
        }
    }
    cout << "YES" << endl;
    for (int i = n - 1; i >= 0; i--)
        cout << ans[i] << " \n"[i == 0];
}
```
