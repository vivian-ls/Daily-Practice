const int MAXN = 500005;
int head[500005], nxt[MAXN << 1], to[MAXN << 1], ind[MAXN << 1], ans[500005];
int cnt = 1;
void add(int u, int v, int i) {
    nxt[cnt] = head[u];
    to[cnt] = v;
    ind[cnt] = i;
    head[u] = cnt++;
}

void solve() {
    int n, m, s;
    cin >> n >> m >> s;
    vector<vector<int>> p(n + 1);
    vector<int> fa(n + 1);
    vector<int> vis(n + 1, false);
    fore(i, 1, n + 1) fa[i] = i;

    auto find = [&](auto &&find, int i) -> int
    {
        if(fa[i] != i)
            fa[i] = find(find, fa[i]);
        return fa[i];
    };

    int u, v;
    fore(i, 1, n) {
        cin >> u >> v;
        p[u].emplace_back(v);
        p[v].emplace_back(u);
    }
    fore(i, 1, m + 1) {
        cin >> u >> v;
        add(u, v, i);
        add(v, u, i);
    }

    auto tarjan = [&](auto &&tarjan, int s, int f) -> void
    {
        vis[s] = true;
        for(int to : p[s]) {
            if(to == f) continue;
            tarjan(tarjan, to, s);
            fa[to] = s;
        }
        for (int e = head[s]; e != 0; e = nxt[e]) {
            int v = to[e];
            if(!vis[v]) continue;
            ans[ind[e]] = find(find, v);
        }
    };

    tarjan(tarjan, s, 0);
    fore(i, 1, m + 1) cout << ans[i] << endl;
}
