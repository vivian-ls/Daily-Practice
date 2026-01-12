#### [C. Monkey Math Tree](https://codeforces.com/gym/105284/problem/C)

**题意：** 现在有一个有 $n$ 个点的链，满足 $|u - v| = 1$ ，每个点有 $\frac{1}{i}$ 的概率保留，也即有 $1 - \frac{1}{i}$ 的概率删除，问最后剩下的连通块的数量的期望是多少？ $n \in [1, 2e5]$

对于一个没有换的图中，点数，边数和连通块数是强相关的，点数 = 边数 + 块数

所以块数的期望也就等于点数的期望减去边数的期望

点数期望: $\sum\limits_{i = 1}^n \frac{1}{i}$ ，边数期望: $\sum\limits_{i = 1}^{n - 1} \frac{1}{i(i + 1)}$ 

后面一个可以用裂项公式计算，当然你不优化也没问题，预处理 $O(M)$

```cpp
int inv(int n) {
    return fpow(n, mod - 2, mod);
}
void init() {
    f[0] = 1;
    fore(i, 1, N + 1) f[i] = f[i - 1] * i % mod;
    g[N] = inv(f[N]);
    for(int i = N - 1; i >= 1; i--) g[i] = g[i + 1] * (i + 1) % mod;
    fore(i, 1, N + 1) p[i] = g[i] * f[i - 1] % mod;

    fore(i, 1, N + 1) pre[i] = (pre[i - 1] + p[i]) % mod;
}

void solve(){
    int n;
    cin >> n;
    cout << (pre[n] - (1 - p[n] + mod) % mod + mod) % mod << endl;
}
```
