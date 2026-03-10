struct DSU {
private:
    vector<int> fa, sz;
public:
    DSU(int n) : fa(n + 1), sz(n + 1, 1) {
        iota(fa.begin(), fa.end(), 0);
    }
    int find(int x) {
        while (x != fa[x]) x = fa[x] = fa[fa[x]];
        return x;
    }
    bool merge(int x, int y) { 
        x = find(x);
        y = find(y);
        if (x == y) return false;
        fa[y] = x;
        sz[x] += sz[y];
        return true;
    }
    int size(int x) {return sz[find(x)]; }
};
