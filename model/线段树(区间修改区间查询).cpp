class SegTree{
private:
    int n;
    vector<int> info, add;

    void up(int i) {
        info[i] = max(info[i << 1], info[i << 1 | 1]);
    }
    void down(int i) {
        if(add[i] == 0) return;
        upgrade(i << 1, add[i]);
        upgrade(i << 1 | 1, add[i]);
        add[i] = 0;
    }
    void upgrade(int i, int val) {
        add[i] += val;
        info[i] += val;
    }
    void push(int jobl, int jobr, int jobv, int l, int r, int i) {
        if(jobl <= l && jobr >= r) {
            upgrade(i, jobv);
        }else{
            int mid = (l + r) >> 1;
            down(i);
            if(jobl <= mid)
                push(jobl, jobr, jobv, l, mid, i << 1);
            if(jobr > mid)
                push(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
            up(i);
        }
    }
    int query(int jobl, int jobr, int l, int r, int i) {
        int ans = 0;
        if(jobl <= l && jobr >= r)
            return info[i];
        int mid = (l + r) >> 1;
        down(i);
        if(jobl <= mid)
            ans = max(query(jobl, jobr, l, mid, i << 1), ans);
        if(jobr > mid)
            ans = max(query(jobl, jobr, mid + 1, r, i << 1 | 1), ans);
        return ans;
    }
public:
    SegTree(int n) : 
    n(n), info((n << 2) + 1, 0), add((n << 2) + 1, 0) {}

    void push(int l, int r, int v) {return push(l, r, v, 1, n, 1); }
    int query(int l, int r) {return query(l, r, 1, n, 1); }
};
