class Seg{
public:
    int n;
    vector<int> a, info;
    Seg(int n) : n(n), info((n << 2) + 1, -inf), a(n + 1) {}

    void build(int i, int l, int r) {
        if(l == r)
            info[i] = a[l];
        else {
            int mid = (l + r) >> 1;
            build(i << 1, l, mid);
            build(i << 1 | 1, mid + 1, r);
            info[i] = max(info[i << 1], info[i << 1 | 1]);
        }
    }
    void set(int pos, int val, int l, int r, int i) {  
        if(l == r) {
            a[pos] = val;
            info[i] = val;
            return;
        }
        int mid = (l + r) >> 1;
        if(pos <= mid) set(pos, val, l, mid, i << 1);
        else set(pos, val, mid + 1, r, i << 1 | 1);
        info[i] = max(info[i << 1], info[i << 1 | 1]);
    }
    int query(int jobl, int jobr, int l, int r, int i) {
        if(jobl <= l && jobr >= r) 
            return info[i];
        int mid = (l + r) >> 1, left = -inf, right = -inf;
        if(jobl <= mid)
            left = query(jobl, jobr, l, mid, i << 1);
        if(jobr > mid)
            right = query(jobl, jobr, mid + 1, r, i << 1 | 1);
        return max(left, right);
    }
};
