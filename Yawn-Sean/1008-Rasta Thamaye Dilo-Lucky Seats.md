#### [E. Rasta Thamaye Dilo](https://codeforces.com/gym/104679/problem/E)

**题意：** 给出一个数n，点的编号从2开始一直到n，当 $i | j$ 或者 $j | i$ 时 i j 之间有一条边，问你需要增加最少多少条边使得所有点连通

从简单的开始，发现小于 n/2 的数一定是可以和2链接的

剩下的数中如果这个数是和数，一定会有一个小于 n/2 的因子，反之如果都大于 n/2 的话这个数就超过n了。所以和数也可以和2链接(它和这个小因子p链接，p一定和2p链接)

所以剩下的就是区间的质数，可以前缀和

🔔查询队列或栈元素时要先检查是不是空的

```cpp[]
vector<bool> is(10000005, true);
vector<int> ans(10000005);
vector<int> prime;
void init(){
    is[0] = is[1] = false;
    fore(i, 2, 10000001) {
        if(is[i]) prime.emplace_back(i);
        for(int p : prime) {
            if(p * i > 10000000) break;
            is[p * i] = false;
            if(i % p == 0) break;
        }
    }
    queue<int> q;
    fore(i, 2, 10000001) {
        if(is[i]) q.push(i);
        else if(!q.empty() && i == q.front() * 2) q.pop();
        ans[i] = q.size();
        if(!q.empty() && q.front() == 2)
            ans[i] -= 1;
    }
}

void solve(){
    int n;
    cin >> n;
    cout << ans[n] << endl;
}
```

#### [F. Lucky Seats](https://codeforces.com/gym/104679/problem/F)

**题意：** 给出一个a, b，你需要找出一个最长的序列，其中每个数互不相同，使得序列中的所有的数 '|' 起来结果是a，'^'结果是a，不存在输出-1

某位上 a 是 1 但是 b 是 0 肯定不行了，后面可以发现 a 只有一个1并且 b 是 0 的时候也不行，因为所有数必须不一样

最后结果 or 起来是 a 说明这些数一定在二进制上是 a 的子集

最后如何调整呢？如果 a 某位上是0， b 也一定是0，所以可以把 a 所有子集中的数都 or 起来，最后 xor 上和 b 之间的差异就是要删除的那个数

```cpp[]
void solve(){
    int a, b;
    cin >> a >> b;
    if((a | b) != a || ((a & -a) == a && b == 0 && a)) {
        cout << -1 << endl;
        return;
    }
    vector<int> ans;
    fore(i, 0, a + 1) {
        if((a & i) == i) {
            ans.emplace_back(i);
            b ^= i;
        }
    }
    int len = ans.size();
    if(b == 0) b = -1;
    else len -= 1;
    cout << len << endl;
    for(int x : ans) if(x != b) cout << x << ' ';
    cout << endl;
}
```
