class SegTree{
public:
    int n;
    vector<int> info, add, a;
    SegTree(int n) : n(n), info((n << 2) + 1, 0), add((n << 2) + 1, 0), a(n + 1) {}

    void build(int i, int l, int r) {
        if(l == r) {
            info[i] = a[l];
            return;
        }else{
            int mid = (l + r) >> 1;
            build(i << 1, l, mid);
            build(i << 1 | 1, mid + 1, r);
            up(i);
        }
    }
    void up(int i) {
        info[i] = info[i << 1] + info[i << 1 | 1];
    }
    void down(int i, int ln, int rn) {
        if(add[i] == 0) return;
        upgrade(i << 1, add[i], ln);
        upgrade(i << 1 | 1, add[i], rn);
        add[i] = 0;
    }
    void upgrade(int i, int val, int cnt) {
        add[i] += val;
        info[i] += val * cnt;
    }
    void push(int jobl, int jobr, int jobv, int l, int r, int i) {
        if(jobl <= l && jobr >= r) {
            upgrade(i, jobv, r - l + 1);
        }else{
            int mid = (l + r) >> 1;
            down(i, mid - l + 1, r - mid);
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
        down(i, mid - l + 1, r - mid);
        if(jobl <= mid)
            ans += query(jobl, jobr, l, mid, i << 1);
        if(jobr > mid)
            ans += query(jobl, jobr, mid + 1, r, i << 1 | 1);
        return ans;
    }
};
