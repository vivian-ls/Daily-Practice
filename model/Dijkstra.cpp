class Graph{
public:
    int n;
    vector<vector<pii>> adj;
    //vector<int> pre;
    vector<int> vis, dis;
    explicit Graph(int n) : n(n){
        adj.resize(n + 1);
        //pre.resize(n + 1, -1);
        vis.resize(n + 1, false);
        dis.resize(n + 1, 0x3f3f3f3f);
    }
    void add(int u, int v, int w){
        adj[u].emplace_back(v, w);
        //adj[v].emplace_back(u, w);
    }
    void dj(int s){
        priority_queue<pii, vector<pii>, greater<pii>> pq;
        dis[s] = 0;
        pq.emplace(0, s);
        while(!pq.empty()){
            auto [d, cur] = pq.top(); pq.pop();
            if(vis[cur]) continue;
            vis[cur] = true;
            for(auto& [to, w] : adj[cur]){
                if(dis[to] > d + w){
                    dis[to] = w + d;
                    pq.emplace(dis[to], to);
                    //pre[to] = cur;
                }
            }
        }
    }
    vector<int> rec(vector<int>& pre, int s){
        vector<int> ans;
        for (int i = s; i != -1; i = pre[i]) ans.push_back(i);
        reverse(ans.begin(), ans.end());
        return ans;
    }
};
