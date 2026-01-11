class Seg{
private:
    int n;
    vector<int> a, info;

    void build(int i, int l, int r) {
        if(l == r)
            info[i] = a[l];
        else {
            int mid = (l + r) >> 1;
            build(i << 1, l, mid);
            build(i << 1 | 1, mid + 1, r);
            info[i] = min(info[i << 1], info[i << 1 | 1]);
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
        info[i] = min(info[i << 1], info[i << 1 | 1]);
    }
    int query(int jobl, int jobr, int jobv, int l, int r, int i) {
        if(info[i] > jobv) return -1;
        int mid = (l + r) >> 1;
        if(l == r) return l;
        else if(jobl <= l && r <= jobr) {
            if(info[i << 1] <= jobv) return query(jobl, jobr, jobv, l, mid, i << 1);
            else return query(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
        }else {
            int ans = -1;
            if(jobl <= mid) 
                ans = query(jobl, jobr, jobv, l, mid, i << 1);
            if(ans == -1 && jobr > mid) 
                ans = query(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
            return ans;
        }
    }

public:
    Seg(vector<int>& tmp) : n(tmp.size() - 1), info((n << 2) + 1, inf), a(tmp) {
        build(1, 1, n);
    }
    void set(int pos, int val) {return set(pos, val, 1, n, 1);}
    int query(int l, int r, int val) {return query(l, r, val, 1, n, 1);}
};
