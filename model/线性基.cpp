// 普通消元
class BASE{
private:
    bool zero = false;
    int sz = 0;
    array<int, 64> basis = {};
public:
    bool insert(int x) {
        for (int i = 63; i >= 0; i--) {
            if (!((x >> i) & 1)) continue;  // 第i位为0，跳过
            if (basis[i] == 0) {
                basis[i] = x;   // 找到空位，插入成功
                sz++;
                return true;
            }
            x ^= basis[i];      // 消去第i位，继续尝试
        }
        // 被消成0，线性相关
        zero = true;
        return false;
    }
    // 查询：检查x能否被当前基表示
    bool check(int x) const {
        for (int i = 63; i >= 0; i--) {
            if ((x >> i) & 1) {
                if (basis[i] == 0) return false;
                x ^= basis[i];
            }
        }
        return x == 0;
    }
    int size() { return sz;}
    int max_val() {
        int ans = 0;
        fore(i, 0, 63) ans = max(ans, ans ^ basis[i]);
        return ans;
    }
};


// 高斯消元
class BASE {
private:
    bool zero = false;
    int len;
    int n;
    vector<int> basis;
public:
    BASE(int n, vector<int>& arr) : n(n), basis(arr) {
        len = 1;
        for(int i = 63; i >= 0; i--) {
            if(len > n) break;
            for(int j = len; j <= n; j++) {
                if((basis[j] >> i) & 1) {
                    swap(basis[j], basis[len]);
                    break;
                }
            }
            if((basis[len] >> i) & 1) {
                for(int j = 1; j <= n; j++) {
                    if(j != len && ((basis[j] >> i) & 1)) {
                        basis[j] ^= basis[len];
                    }
                }
                len++;
            }
        }
        len--;
        zero = (len != n);
    }

    // 判断 x 是否能被当前线性基表示
    bool check(int x) {
        for(int i = 1; i <= len; i++) {
            x = min(x, x ^ basis[i]);
        }
        return x == 0;
    }

    int maxVal() {
        int ans = 0;
        for(int i = 1; i <= len; i++) {
            ans = max(ans, ans ^ basis[i]);
        }
        return ans;
    }

    // 所有不同异或值中的第 k 小（1-based，包含 0）
    int kth(int k) {
        if(k < 1) return -1;
        if(len < 63 && k > (1LL << len)) return -1;
        k--;  // 第1小是0，对应空集

        int ans = 0;
        for(int i = 1; i <= len; i++) {
            if((k >> (i - 1)) & 1LL) {
                ans ^= basis[len - i + 1]; // 按主元从低到高拼
            }
        }
        return ans;
    }

    // 第 k 小非0不同异或值（1-based）
    int kth_nonzero(int k) {
        if(k < 1) return -1;
        if(len < 63 && k > (1LL << len) - 1) return -1;
        return kth(k + 1);
    }

    int rank() { return len; }
    bool hasZero() { return zero; }
};
