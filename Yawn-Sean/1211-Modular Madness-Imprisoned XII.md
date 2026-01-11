#### [F. Modular Madness](https://codeforces.com/gym/105863/problem/F)

**题意：** 给出一个有n个数的数组，$(a[i] \in [1, 1e9])$ ，再给出q次询问，每次询问给出一个整数x，你需要输出 $f_n(x)$ 的值，其中 $f_n(x) = f_{n-1}(x)$ % $a_n$ ，也就是  $f_n(x) = (\ldots((x \text{ mod } a_1)\text{ mod } a_2)\ldots \text{ mod } a_n)$. 

显然可以发现的是对一个数取模，要么不变，要么减小到严格小于原本的一半，所以对一个数的操作次数并不多

现在问题就是如何找到这个数右侧的第一个比自己小的数？这个就是线段树上二分可以维护的信息

这里维护的是第一个比自己小的，所以线段树初始值应该是inf，info维护的信息是这一段中最小的元素的值。query的逻辑就是如果当前区间被全部包含了，那么就先尝试走左侧，不行再走右侧，如果不是全部包含我们就接着往下以mid为分界点递归下去，依然是尝试左侧(因为你要查找的是第一个，是最后一个那就是先走右侧)

最后一个while循环注意边界即可，时间复杂度 $O(n + q\log M \log n)$

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
            info[i] = min(info[i << 1], info[i << 1 | 1]);
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
        info[i] = min(info[i << 1], info[i << 1 | 1]);
    }
    int query(int jobl, int jobr, int jobv, int l, int r, int i) {
        if(info[i] > jobv) return -1;
        int mid = (l + r) >> 1;
        if(l == r) return l;
        else if(jobl <= l && r <= jobr) {
            if(info[i << 1] <= jobv) return query(jobl, jobr, jobv, l, mid, i << 1);
            else return query(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
        }else {
            int ans = -1;
            if(jobl <= mid) 
                ans = query(jobl, jobr, jobv, l, mid, i << 1);
            if(ans == -1 && jobr > mid) 
                ans = query(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
            return ans;
        }
    }

public:
    Seg(vector<int>& tmp) : n(tmp.size() - 1), info((n << 2) + 1, inf), a(tmp) {
        build(1, 1, n);
    }
    void set(int pos, int val) {return set(pos, val, 1, n, 1);}
    int query(int l, int r, int val) {return query(l, r, val, 1, n, 1);}
};


void solve(){
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1);
    fore(i, 1, n + 1) cin >> a[i];
    Seg seg(a);
    int cur;
    while(q--) {
        cin >> cur;
        int pos = 0;
        while(pos < n) {
            pos = seg.query(pos + 1, n, cur);
            if(pos == -1) break;
            cur %= a[pos];
        }
        cout << cur << endl;
    }
}
```

