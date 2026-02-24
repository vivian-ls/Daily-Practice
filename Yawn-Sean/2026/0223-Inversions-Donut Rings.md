#### [I. Inversions](https://codeforces.com/gym/104736/problem/I)

**题意：** 给出一个字符串 $s$ ，重复拼接这个字符串 $n$ 次之后问有多少对 $i, j$ 满足 $i < j$ 和 $s_i < s_j$

字母一共就26个，所以用树状数组维护有多少个比自己小的字母就非常合适，也很简单

对于每一个字母只需要知道它前面有多少个比自己大的以及整个字符串里面有多少比自己大的即可

```cpp
void solve(){
    string s;
    cin >> s;
    int n = s.length(), m;
    cin >> m;
    m %= mod;
    s = " " + s;
    Fenwick tr(30);
    vector<int> pre(n + 1);
    fore(i, 1, n + 1) {
        int tmp = s[i] - 'a' + 1;
        tr.add(tmp, 1);
        pre[i] = i - tr.query(tmp);
        // cout << i << ' ' << pre[i] << endl;
    }
    int sum = 0;
    fore(i, 1, n + 1) {
        sum += (pre[i] * m % mod + (n - tr.query(s[i] - 'a' + 1)) * m % mod * (m - 1) % mod * fpow(2, mod - 2, mod) % mod) % mod;
        sum %= mod;
    }
    cout << sum << endl;
}
```

#### [K. Donut Rings](https://codeforces.com/gym/104720/problem/K)

**题意：** 给出了 $n$ 个甜甜圈的内径和外径，分别是 $r_i, R_i$ ，定义一个甜甜圈的美丽度是甜甜圈的面积减去空腔的面积，你可以任意选择甜甜圈组合，但是必须保证不重叠。这样可以的得到的最高美丽度是多少

这种题目可以看出来是要用 dp 解决的，但是怎么优化呢？

当到了第 $i$ 个元素时，我们计算的公式也就是下面这个

$ dp_i = (R_i^2 - r_i^2) + \mathop{max}\limits_{R_j \le r_i}dp_j $
​
