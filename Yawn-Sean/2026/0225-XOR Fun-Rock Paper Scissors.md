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

先考虑不平局的概率是多少： 不平局说明出现的只有石头剪刀和布中的两种，初步计算是 $C_3^2 \times (\frac{3}{2})^n$
