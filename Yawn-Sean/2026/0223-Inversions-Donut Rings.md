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

这种题目可以看出来是要用 $dp$ 解决的，但是怎么优化呢？

当到了第 $i$ 个元素时，我们计算的公式也就是下面这个

$dp_i = (R_i^2 - r_i^2) + \mathop{max}\limits_{R_j \le r_i}dp_j$ 

​
这个时间复杂度是 $n^2$ ，肯定是不行的，后面是一个查找区间最大值的操作，可以用线段树维护。但是数据很大，还要离散化一下，因为只需要关心大小关系

把甜甜圈按外经从小到大排序，用 $seg$ 维护区间甜甜圈面积最大值，每次尝试更新获得的值就是 $seg(1, l) + (R_i^2 - r_i^2)$ 最后更新 $seg(r) = val$ 

这样就达到了 $nlogn$

```cpp
class Seg{
private:
    int n;
    vector<int> a, info;
    void build(int i, int l, int r) {
        if(l == r)
            info[i] = a[l];
        else {
            int mid = (l + r) >> 1;
            build(i << 1, l, mid);
            build(i << 1 | 1, mid + 1, r);
            info[i] = max(info[i << 1], info[i << 1 | 1]);
        }
    }
    void set(int pos, int val, int l, int r, int i) {  
        if(l == r) {
            a[pos] = val;
            info[i] = val;
            return;
        }
        int mid = (l + r) >> 1;
        if(pos <= mid) set(pos, val, l, mid, i << 1);
        else set(pos, val, mid + 1, r, i << 1 | 1);
        info[i] = max(info[i << 1], info[i << 1 | 1]);
    }
    int query(int jobl, int jobr, int l, int r, int i) {
        if(jobl <= l && jobr >= r) 
        return info[i];
        int mid = (l + r) >> 1, left = 0, right = 0;
        if(jobl <= mid)
        left = query(jobl, jobr, l, mid, i << 1);
        if(jobr > mid)
        right = query(jobl, jobr, mid + 1, r, i << 1 | 1);
        return max(left, right);
    }
public:
    Seg(int n) : n(n), info((n << 2) + 1), a(n + 1, 0) {}
    void set(int pos, int val) { set(pos, val, 1, n, 1);}
    int query(int jobl, int jobr) {return query(jobl, jobr, 1, n, 1);}
    int get(int pos) {return query(pos, pos);}
};

void solve(){
    int n;
    cin >> n;
    vector<int> l(n + 1), r(n + 1);
    vector<int> tmp;
    tmp.emplace_back(0);
    fore(i, 1, n + 1) {
        cin >> l[i] >> r[i];
        tmp.emplace_back(l[i]);
        tmp.emplace_back(r[i]);
    }
    sort(tmp.begin() + 1, tmp.end());
    tmp.erase(unique(tmp.begin() + 1, tmp.end()), tmp.end());

    vector<int> order(n + 1);
    iota(order.begin(), order.end(), 0);
    sort(order.begin() + 1, order.end(), [&](int i, int j) {
        return r[i] < r[j];
    });

    Seg seg(n * 2); // 大小别开小了

    int ans = -inf; // 不要从0开始
    fore(i, 1, n + 1) {
        int id = order[i]; // 用排序后的顺序
        int pl = lower_bound(tmp.begin(), tmp.end(), l[id]) - tmp.begin();
        int pr = lower_bound(tmp.begin(), tmp.end(), r[id]) - tmp.begin();

        int val = seg.query(1, pl) + r[id] * r[id] - l[id] * l[id];
        seg.set(pr, max(val, seg.get(pr))); // 不能覆盖，相当于dp一直取最大
        ans = max(ans, val * 2 - r[id] * r[id]);
    }
    cout << ans << endl;
}
```
