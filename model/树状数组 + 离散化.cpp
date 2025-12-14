vector<int> tmp = arr;
sort(tmp.begin(), tmp.end());
tmp.erase(unique(tmp.begin(), tmp.end()), tmp.end());

vector<int> rank(n);
for (int i = 0; i < n; i++) {
    rank[i] = lower_bound(tmp.begin(), tmp.end(), arr[i]) - tmp.begin() + 1;
}

----------------------------------------------------------------------------------------

class Fenwick{
public:
    int n;
    vector<int> tree;
    Fenwick(int n) : n(n), tree(n + 1) {}
    void add(int x, int val) {
        while(x <= n) {
            tree[x] += val;
            x += lowbit(x);
        }
    }
    int query(int x) {
        int ans = 0;
        while(x) {
            ans += tree[x];
            x -= lowbit(x);
        }
        return ans;
    }
};
