#### [G. XOR Fun](https://codeforces.com/gym/103870/problem/G)

**题意：** 给出一个范围 $A, B$ ，你要找出存在多少个 $A \le x \le B$ 使得 $x \oplus (x + 1) >= M$

观察可以发现一个数二进制后面如果有 $k$ 个连续的1，得到的结果就是 $2^k - 1$

最简单的一个关系是 $x \equiv 2^k - 1 \pmod {2^k}$ ，为了更好计算可以化简成 ${x + 1} \equiv 0 \pmod {2^k}$

也就是在 $l, r$ 这个范围找出有多少个 $x$ 使其满足上面条件( $2^k$ 的倍数)

注：模数可以不是这个，只要等式成立即可

```cpp
void solve(){
    int a, b, m;
    cin >> a >> b >> m;
    unsigned long long tmp = m;
    int bit = bit_width(tmp) - 1;
    cout << ((b + 1) >> bit) - (a >> bit) << endl;
}
```
#### [K. Rock Paper Scissors (Easy Version)](https://codeforces.com/gym/103870/problem/K)

**题意：** 一共有 $n$ 个人在玩石头剪刀布的游戏，输出最后游戏可能进行的轮数的期望值。由于可能比较大输出对 $P$ 取模后的值， $P$ 是每次给出的，但保证是素数。

明显是只能用dp解决的，设置 $dp[i]$ 表示当前人数是 $i$ 的情况下轮数的期望值

先考虑不平局的概率是多少： 不平局说明出现的只有石头剪刀和布中的两种，初步计算是 $C_3^2 \times (\frac{2}{3})^n$

但是这个多算了只出一种手势的情况，并且每个还算了两次，所以还要减去 $3 \times 2 \times (\frac{1}{3})^n$

所以期望次数也就是 $\frac{1}{3\times\left(\frac{2}{3}\right)^i-6\times\left(\frac{1}{3}\right)^i}$ ，代表经过这么多局才会出现非平局，记为 $V$

$dp[i] = V + \sum\limits^{i - 1}_{j = 1} \frac{C_i^j}{2^i - 2} dp[j]$ 分母代表总共情况数，分子代表剩下 $j$ 人的情况数

这个就是完整的转移方程，时间复杂度 $O(n^2)$

注意下面的计算必须优化，不然会超时！！！

```cpp
class Comb{
private:
    int N;
    vector<int> fac, finv;
    
    void init(){
        fac[0] = finv[0] = 1;
        fore(i, 1, N + 1) fac[i] = fac[i - 1] * i % mod;
        finv[N] = this->fpow(fac[N], mod - 2);
        for (int i = N - 1; i >= 1; i--)
            finv[i] = finv[i + 1] * (i + 1) % mod;
    }
public:
    Comb(int N) : N(N), fac(N + 5), finv(N + 5) {
        init();
    }

    int fpow(int a, int b) {
        if(b < 0) return 0;
        int ans = 1;
        a %= mod;
        while (b) { if (b & 1) ans = ans * a % mod; a = a * a % mod; b >>= 1;}
        return ans;
    }

    int getfac(int n) { return fac[n]; }
    int getfinv(int n) { return finv[n]; }
    int inv(int n) { return this->fpow(n, mod - 2); }

    int A(int n, int m) {
        if(n < 0 || m < 0 || m > n) return 0;
        return fac[n] * finv[n - m] % mod;
    }

    int C(int n, int m) {
        if(m < 0 || m > n) return 0;
        return fac[n] * finv[m] % mod * finv[n - m] % mod;
    }

    int Catalan(int n) {  // 卡特兰数
        if(n == 0) return 1;
        else return C(n * 2, n) * inv(n + 1) % mod;
    }
};


void solve(){
    int n;
    cin >> n >> mod;
    Comb comb(n + 1);
    vector<int> dp(n + 1);
    dp[0] = 0, dp[1] = 0;

    int p1 = comb.inv(3), p2 = 2 * p1 % mod;
    int p = 2, v1 = p1, v2 = p2;

    fore(i, 2, n + 1) {
        p = p * 2 % mod;
        v1 = v1 * p1 % mod;
        v2 = v2 * p2 % mod;
        for(int j = 1; j <= i - 1; j++) {
            dp[i] = (dp[i] + comb.C(i, j) * dp[j] % mod) % mod;
        }
        dp[i] = dp[i] * comb.inv(p - 2) % mod;
        int tmp = (3 * v2 % mod + mod - 6 * v1 % mod) % mod;
        dp[i] = (dp[i] + comb.inv(tmp)) % mod;
    }
    fore(i, 1, n + 1) cout << dp[i] << " \n"[i == n];
}
```
