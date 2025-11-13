struct DSU {
    vector<int> f;
    DSU(int n) : f(n + 1) {
        iota(f.begin(), f.end(), 0);
    }
    int find(int x) {
        while (x != f[x]) x = f[x] = f[f[x]];
        return x;
    }
    bool merge(int x, int y) { 
        x = find(x);
        y = find(y);
        if (x == y) return false;
        f[y] = x;
        return true;
    }
};
