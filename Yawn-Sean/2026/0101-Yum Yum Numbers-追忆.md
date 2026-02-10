#### [C. Yum Yum Numbers](https://codeforces.com/gym/106094/problem/C)

**题意：** 给出一个数字 $x$ ，你可以将其乘上任意一个质数 $k$ 次，问这个 $x$ 最多被开平方后还是整数的次数，例如 16 的次数是 2 , 16 -> 4 -> 2

如果一个数可以被开平方 $k$ 次，那么对这个数分解质因数后所有次数都应该是 $2^k$ 的倍数，这个 $k$ 并不会很大，所以暴力看每一个行不行就行了

```cpp
void solve(){
    int n, k;
    cin >> n >> k;
    int ans = 0, v = 1, cur = 2;
    vector<int> fat = Fat(n);
    while(true) {
        int sum = 0;
        for(int x : fat) {
            int val = (x + cur - 1) / cur;
            int tmp = val * cur - x;
            sum += tmp;
        }
        if(sum > k) break;
        v++, cur *= 2, ans++;
    }
    cout << ans << endl;
}
```


#### [H. 追忆](https://codeforces.com/gym/106290/problem/H)

**题意：** 一首诗一共有 $n$ 行，每一行都描述了一种意象 $a_i$ ，一段回忆的价值不仅在于区间内意象的个数，也在于其之外包含了多少种意象。换言之，你需要找到一个 $[l, r]$ 使得区间内元素的个数加上区间外元素的个数之和最大，输出这个最大的值

某一个意象对值的贡献最多只有 2 ，也就是区间外也包含这个意象的时候。

两个端点都可以移动的时候可以尝试固定一个，也就是暴力枚举一边的端点再想办法优化另一边的操作，直接枚举就是 $n^2$

枚举右端点的时候会有两种情况，当这个位置是不是当前元素最后一次出现时，左端点是可以任意选择的，因为右侧一定会剩下一个。此时 $[1, i]$ 的每个位置上的值都应该 +1 ，代表左端点在这个位置时当前元素有一个贡献。还有一种是当前是最后一次出现时，此时应该在 $[first[i], i]$ 区间 +1 ，在这之前还要清除之前累计的 +1 

每次移动右端点是用线段树查询一次即可，时间复杂度 $nlogn$

```cpp
class SegTree{
private:
    int n;
    vector<int> info, add;

    void up(int i) {
        info[i] = max(info[i << 1], info[i << 1 | 1]);
    }
    void down(int i) {
        if(add[i] == 0) return;
        upgrade(i << 1, add[i]);
        upgrade(i << 1 | 1, add[i]);
        add[i] = 0;
    }
    void upgrade(int i, int val) {
        add[i] += val;
        info[i] += val;
    }
    void push(int jobl, int jobr, int jobv, int l, int r, int i) {
        if(jobl <= l && jobr >= r) {
            upgrade(i, jobv);
        }else{
            int mid = (l + r) >> 1;
            down(i);
            if(jobl <= mid)
                push(jobl, jobr, jobv, l, mid, i << 1);
            if(jobr > mid)
                push(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
            up(i);
        }
    }
    int query(int jobl, int jobr, int l, int r, int i) {
        int ans = 0;
        if(jobl <= l && jobr >= r)
            return info[i];
        int mid = (l + r) >> 1;
        down(i);
        if(jobl <= mid)
            ans = max(query(jobl, jobr, l, mid, i << 1), ans);
        if(jobr > mid)
            ans = max(query(jobl, jobr, mid + 1, r, i << 1 | 1), ans);
        return ans;
    }
public:
    SegTree(int n) : 
    n(n), info((n << 2) + 1, 0), add((n << 2) + 1, 0) {}

    void push(int l, int r, int v) {return push(l, r, v, 1, n, 1); }
    int query(int l, int r) {return query(l, r, 1, n, 1); }
};

void solve(){
    int n;
    cin >> n;
    vector<int> a(n + 1);
    fore(i, 1, n + 1) cin >> a[i];
    vector<int> first(n + 1, 0), last(n + 1, 0), pre(n + 1, 0);
    
    fore(i, 1, n + 1) {
        pre[i] = last[a[i]];
        last[a[i]] = i;
        if(first[a[i]] == 0) first[a[i]] = i;
    }

    SegTree seg(n);
    int ans = 0;
    fore(i, 1, n + 1) if(first[i] != 0) ans++;
    int tmp = 0;
    fore(i, 1, n + 1) {
        if(last[a[i]] == first[a[i]]) continue;
        if(last[a[i]] != i) {
            seg.push(pre[i] + 1, i, 1);
        }else {
            seg.push(1, pre[i], -1);
            seg.push(first[a[i]] + 1, i, 1);
        }
        tmp = max(tmp, seg.query(1, n));
    }
    cout << ans + tmp << endl;
}
```
