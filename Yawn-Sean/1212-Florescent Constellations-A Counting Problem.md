#### [D. Florescent Constellations](https://codeforces.com/gym/105780/problem/D)

**题意：** 再二维平面上有 $n$ 个恒星，第 $i$ 个位于 $x_i, y_i$ ，如果存在一个圆，使得位于其边界上的所有点之间的间隔都是相等的，那么这些恒星就可以组成一个荧光星座，输出一共有多少个这样的星座，$n \in [1, 1000]$

有一个必须知道的结论是：格点多变形是正多边形，当且仅当这个多边形是正方形的时候存在

所以我们只需要枚举每一条可能的边，看这个边可不可能组成正方形即可

假设现在枚举到了点 $(x_1, y_1), (x_2, y_2)$ ， $d_x = x_2 - x_1, d_y = y_2 - y_1$ ，假设点1位于上方，那么右侧的正方形就可以通过将这个 d 的向量逆时针旋转90度得到新的向量 $(-d_y, d_x)$ ，两个点分别加上这个向量就是剩下两个点的坐标，另外左侧的也是类似

这里每一个矩阵都会被统计四次，最后的结果还要除以四

这里使用了向量的旋转转移矩阵，(逆时针)，如果是顺时针把 $\theta$ 改成 $-\theta$ 

$$
\begin{pmatrix}
x^{\prime} \\
y^{\prime}
\end{pmatrix} =
\begin{pmatrix}
\cos \theta & -\sin \theta \\
\sin \theta & \cos \theta
\end{pmatrix}
\begin{pmatrix}
x \\
y
\end{pmatrix}
$$

```cpp
void solve(){
    int n;
    cin >> n;
    vector<pii> p(n + 1);
    fore(i, 1, n + 1) cin >> p[i].first >> p[i].second;

    set<pii> st(p.begin() + 1, p.end());
    int ans = 0;

    fore(i, 1, n + 1) {
        fore(j, 1, i) {
            auto[x1, y1] = p[i];
            auto[x2, y2] = p[j];
            int dx = x2 - x1, dy = y2 - y1;
            if(st.count({x1 - dy, y1 + dx}) && st.count({x2 - dy, y2 + dx})) ans++;
            if(st.count({x1 + dy, y1 - dx}) && st.count({x2 + dy, y2 - dx})) ans++;
        }
    }
    cout << ans / 4 << endl;
}
```

#### [G. A Counting Problem](https://codeforces.com/gym/105863/problem/G)

**题意：** 定义 $f(a)$ 的值为数组 $a$ 中 $\min(a_1, a_2...a_i) = a_i$ 的 $i$ 的个数，现在有一个数组长度是 $n$ ，每一个 $a_i \in [1, k]$ ，这样的数组明显有 $k_n$ 个，问这些所有数组的 $f(a)$ 的和

对于这种全体数列求每个的值的和的问题，可以考虑先求出单个数列的期望，把这个期望乘以数列的总数就是最终的结果

考虑第 $i$ 位对结果的贡献，其是 $j$ 的概率是 $\frac{1}{k}$ ，而此时前面的元素不比它小的概率是 $\frac{k-j+1}{k}$ ，所以是 $j$ 的情况下满足条件的概率是 $\left(\frac{k-j+1}{k}\right)^{i-1}$ ，所以根据全概率公式，第 $i$ 位的总贡献是 $\sum\limits_{j=1}^k\frac{1}{k}\left(\frac{k-j+1}{k}\right)^{i-1}=\frac{1}{k}\sum\limits_{j=1}^k\left(\frac{k-j+1}{k}\right)^{i-1}$ 。

所以最终求的东西就是 $\frac{1}{k}\sum\limits_{i=1}^n\sum\limits_{j=1}^k\left(\frac{k-j+1}{k}\right)^{i-1}$ 。我们可以先关于 $i$ 求和，这样求和的就是个等比数列 $\sum\limits_{i=1}^n\left(\frac{k-j+1}{k}\right)^{i-1}$ ，再关于 $j$ 求和 $k$ 次就是答案。

等比数列求和公式：

$$
\frac{a_n q - a_1}{q - 1} = \frac{a_1(q^n - 1)}{q - 1}
$$


```cpp
void solve(){
    int n, k;
    cin >> n >> k;
    int ans = n, invk = fpow(k, mod - 2, mod);
    fore(i, 2, k + 1) {
        int up = (fpow((k - i + 1) * invk % mod, n, mod) - 1 + mod) % mod;
        int down = ((k - i + 1) * invk % mod - 1 + mod) % mod;
        ans = (ans + (up * fpow(down, mod - 2, mod)) % mod) % mod;
    }
    ans = (ans * fpow(k, n - 1, mod)) % mod;
    cout << ans << endl;
}
```
