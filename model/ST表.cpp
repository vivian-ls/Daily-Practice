class ST{
public:  // 记得加上public
    int n;
    vector<vector<int>> st;
    ST(int n, vector<int>& a) : n(n){
        st = vector<vector<int>>(n + 1, vector<int>(22 + 1));
        build(n, a);
    }
    inline int get(const int& a, const int& b) { return max(a, b); };

    void build(int n, vector<int>& a){
        fore(i, 1, n + 1) st[i][0] = a[i];
        for (int p = 1, t = 2; t <= n; t <<= 1, p++){
            for (int i = 1; i <= n; i++){
                if(i + t - 1 > n) break;
                st[i][p] = max(st[i][p - 1], st[i + (t >> 1)][p - 1]);
            }
        }
    }
    inline int find(int l, int r){
        int t = (int)log2(r - l + 1);
        return get(st[l][t], st[r - (1 << t) + 1][t]);
    }
};
