#### [A. Episodes](https://codeforces.com/gym/104985/problem/A)

**题意：** 现在一共有 $n$ 个下载任务，每个任务此时的下载速度是 $v_i$ ，将在 $t_i$ 时刻下载完毕。但是实际并非这样，因为总速度不会降低，也就是一个任务下载完后，多余的速度会按照原本的比例分配出去，求出每个任务实际下载完毕的时刻

模拟题，但是处理起来挺麻烦的。按照时间从大到小排序，先处理先下载完的，这样可以将时间分为一段一段的

对于每个时间段求出具体的时间需要此时原本的总速度(cur_v)和原本需要的时间(t[id] - pre)，求出总工作量，再用这个工作量除以实际总速度(total)

```cpp
void solve(){
    int n;
    cin >> n;
    vector<int> v(n + 1), t(n + 1);
    int tot = 0;
    fore(i, 1, n + 1) {
        cin >> v[i] >> t[i];
        tot += v[i];
    }
    vector<int> order(n + 1);
    iota(order.begin(), order.end(), 0);
    sort(order.begin() + 1, order.end(), [&](int i, int j) {
        return t[i] < t[j];
    });
    int cur_v = tot, pre = 0;
    ld cur_t = 0;
    vector<ld> ans(n + 1); 

    fore(i, 1, n + 1) {
        int id = order[i];
        cur_t += (ld)(t[id] - pre) * cur_v / tot;
        pre = t[id];
        ans[id] = cur_t;
        cur_v -= v[id];
    }
    cout << fixed << setprecision(15);
    fore(i, 1, n + 1) cout << ans[i] << endl;
}
```

#### [C. A Noteworthy Debut](https://codeforces.com/gym/105109/problem/C)

**题意：** 现在一共有 $n$ 首乐曲，每首乐曲都有自己的兴奋度，问一共可以选出多少个子数组，使得这个子数组中存在一首歌的兴奋度高于剩下所有歌曲的兴奋度只和

又是一个数列规律的题，歌曲按兴奋度排列后，考虑每一首歌作为左边界，可以找到多少个右边界(分析复杂度)

最有的情况是 1, 2, 4, 8, 16... 每一次都会变成原本的2倍，是指数增长的所以不会有非常多项

枚举方式是选取每个元素作为兴奋度最高的那一首歌，先尽量往左边扩展(最多30次)，再用双指针向右扩展(同样最多30次)。累加结果即可

```cpp
void solve(){
    int n;
    cin >> n;
    vector<int> a(n + 1);
    fore(i, 1, n + 1) cin >> a[i];
    int ans = 0;
    fore(i, 1, n + 1) {
        int l = i, r = i;
        int tmp = 0;
        while(l > 1 && tmp + a[l - 1] < a[i]) l--, tmp += a[l];
        while(l <= i) {
            while(r < n && tmp + a[r + 1] < a[i]) r++, tmp += a[r];
            ans += (r - i + 1);
            tmp -= a[l];
            l++;
        }
    }
    cout << ans << endl;
}
```
