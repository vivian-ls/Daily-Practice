// 严格分层，指同一层的元素不互相影响，不分开的话可能前一个扩散后导致后一个无法扩散，但是其实可以
void solve() {
    int n, m;
    string s;
    cin >> n >> m;
    vector<vector<int>> a(n + 1, vector<int>(m + 1, 0));
    fore(i, 1, n + 1) {
        cin >> s;
        fore(j, 0, m) if(s[j] == '#') a[i][j + 1] = 1; 
    }

    queue<pii> q;
    fore(i, 1, n + 1) fore(j, 1, m + 1) {
        if(a[i][j] == 1) q.emplace(i, j);
    }

    auto check = [&](int x, int y) -> bool {
        if(a[x][y]) return false;
        int cnt = 0;
        fore(i, 0, 4) {
            int xx = x + dx[i], yy = y + dy[i];
            if(xx < 1 || xx > n || yy < 1 || yy > m) continue;
            cnt += (a[xx][yy]);
        }
        return cnt == 1;
    };

    while(!q.empty()) {
        queue<pii> tmp;
        while(!q.empty()) {
            auto[x, y] = q.front(); q.pop();
            fore(i, 0, 4) {
                int xx = x + dx[i], yy = y + dy[i];
                if(xx < 1 || xx > n || yy < 1 || yy > m) continue;
                if(check(xx, yy)) {
                    tmp.emplace(xx, yy);
                }
            }
        }
        while(!tmp.empty()) {
            auto[x, y] = tmp.front();
            tmp.pop();
            a[x][y] = 1;
            q.emplace(x, y);
        }
    }
    int ans = 0;
    fore(i, 1, n + 1) fore(j, 1, m + 1) ans += a[i][j];
    cout << ans << endl;
}
