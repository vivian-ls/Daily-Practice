#### [Turtle and GCD](https://codeforces.com/gym/104669/problem/L)

**题意：** 给定两个数 $a$ 和 $b$ ，考虑整数集 $a, a+1, a+2 ... a+b−1$ 。将这个集合划分为两个非空集合，使得每个元素只属于一个集合，并且集合和的GCD最大化。最大GCD是多少？

两个集合的 gcd 只可能是总和的因子，遍历每个因子暴力检查是否可行

对于这种可以采取确定集合大小，找出边界的方式快速维护是否可以找到满足条件的集合

假设当前集合大小是 $k$, 集合最小值就是 $a + a + 1 +...+ a + k - 1$, 最大值就是 $a + b - k + ... + a + b - 2 + a + b - 1$

中间的是一定也是可以取的到的因为可以一步步往最大值扩,只需要找到这个区间时候有结果是 $p$(当前枚举到的因子)的倍数即可, 具体操作是 r / p * p >= l

```cpp
void solve(){
    int a, b;
    cin >> a >> b;
    int sum = (2 * a + b - 1) * b / 2;

    auto check = [&](int x) {
        for(int i = 1; i <= b - 1; i++) {
            int l = a * i + (i - 1) * i / 2;
            int r = a * i + (b * 2 - i - 1) * i / 2;
            if(r / x * x >= l) return true;
        }
        return false;
    };
    int ans = 1;
    for(int i = 2; i * i <= sum; i++) {
        if(sum % i == 0) {
            if(check(i)) ans = max(ans, i);
            if(check(sum / i)) ans = max(ans, sum / i);
        }
    }
    cout << ans << endl;
}
```

