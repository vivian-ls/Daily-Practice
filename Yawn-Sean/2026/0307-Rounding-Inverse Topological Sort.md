#### [E. Rounding](https://codeforces.com/gym/102465/problem/E)

**题意：** 调查组一共调查了10000个人法国最喜欢的地点，但是由于调查员不小心四舍五入的最终的数据，这样数据精度大大下降了，你想知道每个数据的原始取值范围，或者这个数据出错了，是不可能的

模拟，但是难点在于同时要找左边界和右边界，不妨初始全部都选择左边界，记录下最多可以在这个位置增加多少(tot_add)以及最少需要多少(tot)

根据上面两个就可以判断数据是否出错，求最小值就是尝试把 res 都增加到剩下的元素上，求最大值就是尝试把 res 都加到这个元素上

```cpp
void solve(){
    int n;
    cin >> n;
    vector<string> s(n + 1);
    vector<int> val(n + 1), cur(n + 1), add(n + 1);
    int tot = 0, tot_add = 0;
    fore(i, 1, n + 1) {
        cin >> s[i] >> val[i];
        val[i] *= 100;
        if(val[i] == 0) cur[i] = 0, add[i] = 49;
        else if(val[i] == 10000) cur[i] = 9950, add[i] = 50;
        else cur[i] = val[i] - 50, add[i] = 99;
        tot += cur[i];
        tot_add += add[i];
    }
    int res = 10000 - tot;
    cout << fixed << setprecision(2);
    if(tot > 10000 || tot + tot_add < 10000) {
        cout << "IMPOSSIBLE" << endl;
    }else {
        fore(i, 1, n + 1) {
            int maxn = cur[i] + min(add[i], res);
            int minn = cur[i] + max(0ll, res - (tot_add - add[i]));
            cout << s[i] << ' ' << minn * 1.0 / 100 << ' ' << maxn * 1.0 / 100 << endl;
        }
    }
}
```

#### [E. Inverse Topological Sort](https://codeforces.com/gym/104891/problem/E)

**题意：** 现在有一个拓扑图，但是你忘了它原来是什么样的，只知道最小的拓扑序列 A 和最大的拓扑序列 B，请你还原这个拓扑图。如果不能还原输出 NO，可以还原输出任意一种即可

