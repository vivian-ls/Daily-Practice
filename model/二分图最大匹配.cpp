class BP {
public:
    vector<int> vis, link;
    vector<vector<int>> p;
    int n, m;
    BP(int n, int m) : n(n), m(m) {
        p.resize(n + 1);
        vis.resize(m + 1, false), link.resize(m + 1, -1);
    }
    inline void add(int u, int v) { p[u].emplace_back(v); };
    bool dfs(int s) {
        for(int to : p[s]) {
            if(vis[to]) continue;
            vis[to] = true;
            if(link[to] == -1 || dfs(link[to])) {
                link[to] = s;
                return true;
            }
        }
        return false;
    }
    int match() {
        int ans = 0;
        fore(i, 1, n + 1) {
            fill(vis.begin() + 1, vis.end(), false);
            if(dfs(i)) ans++;
        }
        return ans;
    }
};
