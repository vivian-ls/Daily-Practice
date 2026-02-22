#### [2. Sum of Divisors](https://codeforces.com/gym/106247/problem/2)

**题意：** 在 1 到 $10^9$ 范围内找到一个数，这个数等于其 $n$ 个因数的和，所选的因数必须是不同的

这种题目最好是写出表达式，可以直接看到关系

如果 $a_i$ 代表 $n$ 的因子的话, $n = \frac{n}{a_1} + \frac{n}{a_2} + \frac{n}{a_3}... + \frac{n}{a_n}$

两边同时除以 $n$ 的话，可以得到一个等式： $\sum\limits_{1}^{n} {\frac{1}{a_i}} = 1$, 这个 $n$ 也就是这些 $a_i$ 的最小公倍数

这里要用到经典的拆分方法: $1 = \frac{1}{2} + \frac{1}{2}$

$1=\frac{1}{2}+\frac{1}{2}=\frac{1}{2}+\frac{1}{4}+\frac{1}{4}=\dots=\frac{1}{2}+\frac{1}{4}+\dots+\frac{1}{2^{n-3}}+\frac{1}{2^{n-3}}$

但是这样拆成上面那样(只有n - 2项)最后会有两个相同的项，这里要接着用到凑一法， $1 = \frac{1}{2} + \frac{1}{3} + \frac{1}{6}$

所以 $\frac{1}{2^{n-3}}=\frac{1}{2^{n-3}}\times 1=\frac{1}{2^{n-3}}\times\left(\frac{1}{2}+\frac{1}{3}+\frac{1}{6}\right)=\frac{1}{2^{n-2}}+\frac{1}{3\times 2^{n-3}}+\frac{1}{3\times 2^{n-2}}$ 。

最小公倍数也就是最大的 $3 \times 2^{n-2}$

```cpp
void solve(){
    int n;
    cin >> n;
    if(n == 1) {
        cout << 1 << endl;
        cout << 1 << endl;
    }else if(n == 2) {
        cout << -1 << endl;
    }else {
        cout << (3 << (n - 2)) << endl;
        cout << 1 << ' ' << 2 << ' ';
        fore(i, 0, n - 2) cout << (3 << i) << ' ';
        cout << endl;
    }
}
```

#### [4. Robot Charging](https://codeforces.com/gym/106247/problem/4)

**题意：** 现在有一个型号为 $n$ 的机器人需要充电，但是需满足以下条件： $p >= n + 1$ 并且 $p <= n + k$ ，$p$ 和 $k$ 都是给出的，分别表示充电功率的最大功率。你需要找到一个合适的功率使得 $lcm(n, p)$ 最小

和 lcm 有关的建议转化成 gcd 相关题目会容易很多，设 $p = n + v, gcd(n, p) = g$

$lcm(n, p) = n \times \frac{n + v}{g}$

这里的 $g$ 一定是 $n$ 的因子，要想后面这个分数是整数，就必须有 $v$ 也是 $g$ 的倍数，这里想要最小化分数，自然 $v = g$ 了，同时 $g$ 越大越好，所以 $g$ 就是 $n$ 的最大的因子，所以找出这个因子也就找到了这个 $p$

```cpp

```



