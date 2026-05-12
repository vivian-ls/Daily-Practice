class SCC{
private:
    int n, cntn = 0, cnt_scc = 0;
    vector<int> dfn;
    vector<int> low; // 从这个节点最多走一次回边可以到达的最高点
    vector<int> belong; // 节点 i 属于哪个强连通分量
    vector<vector<int>> p;
    stack<int> st;
    vector<int> sz;

public:
    SCC(int n) : n(n), dfn(n + 1), low(n + 1), belong(n + 1), p(n + 1), sz(n + 1) {}
    
    void add(int u, int v) {
        p[u].emplace_back(v);
    }

    void tarjan(int u) {
        dfn[u] = low[u] = ++cntn;
        st.push(u);
        for(int v : p[u]) {
            if(dfn[v] == 0) { // 碰到树边
                tarjan(v);
                low[u] = min(low[u], low[v]);
            }else if(belong[v] == 0) { // 碰到回边
                low[u] = min(low[u], dfn[v]);
            } // 碰到弃边不用操作
        }
        if(low[u] == dfn[u]) { // "封口袋"，找到一个分量
            cnt_scc++;
            int cur;
            do{
                cur = st.top(); st.pop();
                belong[cur] = cnt_scc;
                sz[cnt_scc]++;
            }while(cur != u);
        }
    }

    void init() {
        for(int i = 1; i <= n; i++) {
            if(dfn[i] == 0) tarjan(i);
        }
    }

    int find(int x) { return belong[x]; }
    int getcnt() { return cnt_scc; }
    int size(int x) { return sz[x]; }
};
