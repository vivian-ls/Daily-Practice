int deep[500005], st[500005][22 + 1];
class LCA{
public:
    int n, maxp;
    vector<vector<int>> adj;

    LCA(int n) : n(n) {
        maxp = (int)log2(n);
        adj.resize(n + 1);
    }
    void add(int u, int v) adj[u].emplace_back(v);

    void dfs(int s, int f) {
        deep[s] = deep[f] + 1;
        st[s][0] = f;
        for (int p = 1; (1 << p) <= deep[s]; p++) st[s][p] = st[st[s][p - 1]][p - 1];
        for(int to : adj[s]) {
            if(to == f) continue;
            dfs(to, s);
        }
    }
    
    int find(int a, int b) {
        if(deep[a] < deep[b]) swap(a, b);
        for (int p = maxp; p >= 0; p--) {
            if(deep[st[a][p]] >= deep[b])
                a = st[a][p];
        }
        if(a == b) return a;
        for (int p = maxp; p >= 0; p--) {
            if(st[a][p] != st[b][p])
                a = st[a][p], b = st[b][p];
        }
        return st[a][0];
    }
};
