// 此线段树维护的是区间最大值
class SegTree {
private:
    int n;
    vector<int> a, info;

    void build(int i, int l, int r) {
        if (l == r) {
            info[i] = a[l];
        } else {
            int mid = (l + r) >> 1;
            build(i << 1, l, mid);
            build(i << 1 | 1, mid + 1, r);
            info[i] = max(info[i << 1], info[i << 1 | 1]);
        }
    }

    void set(int pos, int val, int l, int r, int i) {
        if (l == r) {
            a[pos] = val;
            info[i] = val;
            return;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid) set(pos, val, l, mid, i << 1);
        else set(pos, val, mid + 1, r, i << 1 | 1);
        info[i] = max(info[i << 1], info[i << 1 | 1]);
    }

    int query(int jobl, int jobr, int l, int r, int i) {
        if (jobl <= l && r <= jobr) return info[i];
        int mid = (l + r) >> 1;
        int left = INT_MIN, right = INT_MIN;
        if (jobl <= mid) left = query(jobl, jobr, l, mid, i << 1);
        if (jobr > mid) right = query(jobl, jobr, mid + 1, r, i << 1 | 1);
        return max(left, right);
    }

public:
    // 不给初始数组，默认全 0
    SegTree(int n) : n(n), a(n + 1, 0), info((n << 2) + 1, 0) {}

    // 给初始数组，要求 arr 是 1-based
    SegTree(int n, vector<int>& arr) : n(n), a(n + 1, 0), info((n << 2) + 1, 0) {
        for (int i = 1; i <= n; i++) a[i] = arr[i];
        build(1, 1, n);
    }
    void set(int pos, int val) { set(pos, val, 1, n, 1);}
    int query(int jobl, int jobr) { return query(jobl, jobr, 1, n, 1);}
    int get(int pos) { return a[pos];}
};
