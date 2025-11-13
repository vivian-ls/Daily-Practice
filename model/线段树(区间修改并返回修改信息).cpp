class SegTree{
public:
    int n;
    vector<int> cnt, add, val, minn;
    SegTree(int n) : n(n), cnt((n << 2) + 1, 0), add((n << 2) + 1, 0), minn((n << 2) + 1), val(n + 1) {}

    void build(int i, int l, int r) {
        if(l == r) {
            cnt[i] = 1;
            minn[i] = val[l];
            return;
        }else{
            int mid = (l + r) >> 1;
            build(i << 1, l, mid);
            build(i << 1 | 1, mid + 1, r);
            up(i);
        }
    }
    void up(int i) {
        cnt[i] = cnt[i << 1] + cnt[i << 1 | 1];
        minn[i] = min(minn[i << 1], minn[i << 1 | 1]);
    }
    void down(int i) {
        if(add[i] == 0) return;
        upgrade(i << 1, add[i]);
        upgrade(i << 1 | 1, add[i]);
        add[i] = 0;
    }
    void upgrade(int i, int val) {
        minn[i] += val;
        add[i] += val;
    }
    int push(int jobl, int jobr, int jobv, int l, int r, int i) {
        if(cnt[i] == 0) return 0;
        if(jobl <= l && jobr >= r && minn[i] > jobv) {
            upgrade(i, -jobv);
            return cnt[i] * jobv;
        }
        if(l == r) {
            cnt[i] = 0;
            int tmp = minn[i];
            minn[i] = inf;
            return tmp;
        }
        int mid = (l + r) >> 1;
        down(i);
        int ans = 0;
        if(jobl <= mid) ans += push(jobl, jobr, jobv, l, mid, i << 1);
        if(jobr > mid) ans += push(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
        up(i);
        return ans;
    }
};
