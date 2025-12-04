#### [H. Beacon Towers](https://codeforces.com/gym/103855/problem/H)

**题意：** 给出n个村庄，每个村庄有一个高度，你需要把这些村庄分为连续的若干段使得前一段最高的村庄小于后一段最高的村庄

从头开始遍历一遍就可以找出一个递增的村庄序列，这个必须是严格递增的，并非最长上升子序列

这些村庄中任意两个中间都可以有一个分段点或者没有，把所有情况相乘就是结果

```cpp
void solve(){
    int n;
    cin >> n;
    vector<int> a(n + 1);
    fore(i, 1, n + 1) cin >> a[i];
    vector<int> pos;
    int pre = -1;
    fore(i, 1, n + 1) {
        if(a[i] >= pre) {
            pre = a[i];
            pos.emplace_back(i);
        }
    }
    pre = 1;
    fore(i, 1, pos.size()) {
        pre = pre * (pos[i] - pos[i - 1] + 1) % mod;
    }
    cout << pre << endl;
}
```

#### [M. Short Question](https://codeforces.com/gym/103855/problem/M)

**题意：** 给出两个有n个数的序列p, q，你需要求下面式子的值

$$
\sum_{i=1}^{N} {\sum_{j=1}^{N} {\min(|p_i - p_j|, |q_i - q_j|)} }
$$

如果熟悉切比雪夫距离的话，可以看出来这个式子除了min之外就是切比雪夫距离的表达式，肯定要转化成曼哈顿距离来算的

有一个等式是 $\max(x, y) = x + y - \min(x, y)$ ，这个x, y是在实数单位内的

所以这里就可以有第一步转化 $\sum\limits_i^n\sum\limits_j^n|p_i-p_j|+\sum\limits_i^n\sum\limits_j^n|q_i-q_j| - \max(|p_i - p_j|, |q_i - q_j|)$ 

接下来是转化为曼哈顿距离计算max

曼哈顿距离的公式为：dis = |x1 - x2| + |y1 - y2|，而切比雪夫距离的公式为：dis = max(|x1 - x2|, |y1 - y2|)。 

将点 (x, y) 转换为 (x + y, x - y) 后，原点的曼哈顿距离等于新点的切比雪夫距离。 

把上面的表达式每个除以2可以实现逆向过程

$max = \frac{\sum\limits_i\sum\limits_j|(p_i-q_i)-(p_j-q_j)|+\sum\limits_i\sum\limits_j|(p_i+q_i)-(p_j+q_j)|}{2}$ 

这里同样有一个快速计算 $\sum\limits_i^n\sum\limits_j^n|x_i - x_j|$ 的方法， $sum = 2\sum\limits_i^n({(2i - n - 1)} * x_i)$ (排序之后)

之后O(n)计算即可

```cpp
void solve(){
    int n;
    cin >> n;
    vector<int> x(n + 1), y = x;
    fore(i, 1, n + 1) cin >> x[i];
    fore(i, 1, n + 1) cin >> y[i];

    auto cal = [&](vector<int> &tmp) -> int
    {
        int ans = 0;
        sort(tmp.begin() + 1, tmp.end());
        fore(i, 1, n + 1) {
            ans += (i * 2 - n - 1) * tmp[i];
        }
        return ans;
    };
    int ans = 0;
    vector<int> tmp = x;
    ans += cal(tmp) * 2;
    tmp = y;
    ans += cal(tmp) * 2;
    fore(i, 1, n + 1) tmp[i] = x[i] - y[i];
    ans -= cal(tmp);
    fore(i, 1, n + 1) tmp[i] = x[i] + y[i];
    ans -= cal(tmp);
    cout << ans << endl;
}
```
