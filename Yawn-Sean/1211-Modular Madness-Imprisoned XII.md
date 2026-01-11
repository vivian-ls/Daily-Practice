#### [F. Modular Madness](https://codeforces.com/gym/105863/problem/F)

**题意：** 给出一个有n个数的数组， $a[i] \in [1, 1e9]$ ，再给出q次询问，每次询问给出一个整数x，你需要输出 $f_n(x)$ 的值，其中 $f_n(x) = f_{n-1}(x)$ % $a_n$ ，也就是  $f_n(x) = (\ldots((x \text{ mod } a_1)\text{ mod } a_2)\ldots \text{ mod } a_n)$. 

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

#### [I. Imprisoned XII](https://codeforces.com/gym/106033/problem/I)

**题意：** 给出两个整数 $N$ 和 $K$, 计算长度为 $n$ 的非递减序列 $(a, b)$ 满足以下条件:

-   $a_1 = b_1 = 0$
-   $\forall 2 \leq i \leq N, a_i - a_{i - 1} \leq 1$
-   $\forall 2 \leq i \leq N, b_i - b_{i - 1} \leq 1$
-   $\forall 1 \leq i \leq N, a_i - b_i \leq K$

前两个条件都是互不干扰的，将他们联系起来的是第三条规则，规定差值 $d_i = a_i -b_i$ ，这个差值每次可能的情况有+1, -1, 0

这里很快可以意识到这是一个带权随机游走问题，一半都需要用到(反射原理 / 卡特兰数)来求解，但是用这个必须每一步是等权的并且只有两种选择，也就是 $+x$ , $-x$ 两种

通过把每一步也就是 $d_i$ 的变化设置为0.5，原来的每一次变换两次之后就可以达到想要的效果

0.5 + 0.5 = 1, 0.5 - 0.5 = 0, -0.5 + 0.5 = 0, -0.5 - 0.5 = -1

这在随机游走里叫：把带权步，变成等权细分步

你什么时候该想到“拆步”？

出现下面三个信号之一，基本就要想它了：

1️⃣ 步数少，但权重不均匀「一步里有 1、1、2 这种怪权重」

2️⃣ 你想用反射原理 / 卡特兰，但发现不等权 → 用不了

3️⃣ 权重是小整数（尤其是 2），非常容易被拆成“顺序不同”

一个类比，想象：一个骰子有三种结果，但概率不均匀

常见做法不是硬算，而是：用两个公平硬币去模拟

这里完全一样：原模型：不公平，拆步：用更细粒度的公平模型模拟

现在回到这一题，将每一步拆分之后现在我们需要走 $2(n - 1)$ 步，把加一想象成 $y$ 坐标加一，减一想象成 $x$ 坐标加一

但是用卡特兰数思想有一个关键点是，限制是什么，在游走过程中碰到那一条直线才能保证一定不合法呢，发现并不是 $y = x * 2 + 1$ 而是 $y = x * 2 + 2$

因为我到达第一条直线之后还可以再走一步回来，也可以最后合法，所以这个要做镜像翻转的直线是第二个，剩下就是卡特兰数的知识了

```cpp
const int N = 2e6;
int fac[N + 5], finv[N + 5];
int inv(int n) {
    return fpow(n, mod - 2, mod);
}

int A(int n, int m) {
    return fac[n] * finv[n - m] % mod;
}

int C(int n, int m) {
    if(m < 0 || m > n) return 0;
    return fac[n] * finv[m] % mod * finv[n - m] % mod;
}

int Catalan(int n) {  // 卡特兰数
    if(n == 0) return 1;
    else return C(n * 2, n) * fpow(n + 1, mod - 2) % mod;
}
void init(){
    fac[0] = finv[0] = 1;
    fore(i, 1, N + 1) fac[i] = fac[i - 1] * i % mod;
    finv[N] = inv(fac[N]);
    for (int i = N - 1; i >= 1; i--)
        finv[i] = finv[i + 1] * (i + 1) % mod;
}

void solve(){
    int n, k;
    cin >> n >> k;
    
    int ans = 0;
    n -= 1;
    for(int i = n - k; i <= n * 2; i++) {
        ans = (ans + (C(n * 2, i) - C(n * 2, n * 2 - i - k * 2 - 2) + mod) % mod) % mod;
    }
    cout << ans << endl;
}
```
