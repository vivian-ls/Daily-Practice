#### [E. Divisive Battle](https://codeforces.com/contest/2200/problem/E)

**题意：** 最初数组中有 $n$ 个元素， Alice 和 Bob 在玩一个游戏， Alice 先手。每次操作可以选择一个 X 将其拆分成 $y, z$ 有 $y \times z = x (1 \le y, z \le x)$ 。任何时候只要数组是非递减的，游戏直接结束，否则游戏会在无法分解时结束。最后数组是非递减的则 Bob 获胜，否则 Alice 获胜

Alice 先手，发现只有当所有的数只有一个质因子时才可以，因为如果有两个可以把 $x$ 分出来一个最小的质因子放在后面，那么此时就一定输了。所以只有所有的数都只有一个质因子，并且这个质因子是不递减的才可以

```cpp
void solve(){
    int n;
    cin >> n;
    vector<int> a(n + 1);
    fore(i, 1, n + 1) cin >> a[i];
    int flag = true;
    fore(i, 2, n + 1) if(a[i] < a[i - 1]) flag = false;
    if(flag) {
        cout << "Bob" << endl;
        return;
    }
    flag = true;

    int pre = -1;
    fore(i, 1, n + 1) {
        vector<pii> tmp = fat_s(a[i]);
        if(tmp.size() != 1) {
            flag = false;
        }else if(tmp[0].first < pre) {
            flag = false;
        }else {
            pre = tmp[0].first;
        }
    }
    if(flag) cout << "Bob" << endl;
    else cout << "Alice" << endl;
}
```

#### [F. Mooclear Reactor 2](https://codeforces.com/contest/2200/problem/F)

**题意：** 现在有 $n$ 个燃料棒，每个燃料棒有参数 $x, y$ 代表产生的能量是 $x$ 但是最多只能与 $y$ 个其他的燃料棒一起使用，商店里还有 $m$ 个燃料棒，请输出假如购买第 $i$ 个燃料棒最多可以生产多少能量(你不一定要使用购买的燃料棒)

有一个性质是 $y$ 更低的可以和所有 $y$ 更高的一起用，排序后从 $y$ 更大的开始会更好处理

所以就从假设选择 $n$ 个开始，用堆一个维护最大的 $i$ 个值就可以，注意在选择时判断是否选满，满了要及时 pop

```cpp
void solve(){
    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n + 1);
    int x, y;
    fore(i, 1, n + 1) {
        cin >> x >> y;
        a[y].emplace_back(x);
    }

    priority_queue<int, vector<int>, greater<int>> pq;
    vector<int> sum(n + 1);
    int cur = 0, ans = 0;
    for(int i = n; i >= 0; i--) {
        for(int c : a[i]) {
            pq.push(c);
            cur += c;
        }
        while(pq.size() > i + 1) {
            cur -= pq.top();
            pq.pop();
        }
        ans = max(ans, cur);
        sum[i] = cur - (pq.size() == i + 1 ? pq.top() : 0);
    }

    fore(i, 1, n + 1) sum[i] = max(sum[i], sum[i - 1]);
    fore(i, 1, m + 1) {
        cin >> x >> y;
        cout << max(ans, x + sum[y]) << " \n"[i == m];
    }
}
```
