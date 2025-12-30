class Comb{
private:
    int N;
    vector<int> fac, finv;
    
    void init(){
        fac[0] = finv[0] = 1;
        fore(i, 1, N + 1) fac[i] = fac[i - 1] * i % mod;
        finv[N] = fpow(fac[N], mod - 2);
        for (int i = N - 1; i >= 1; i--)
            finv[i] = finv[i + 1] * (i + 1) % mod;
    }
public:
    Comb(int N) : N(N), fac(N + 5), finv(N + 5) {
        init();
    }

    int fpow(int a, int b) {
        if(b < 0) return 0;
        int ans = 1;
        a %= mod;
        while (b) { if (b & 1) ans = ans * a % mod; a = a * a % mod; b >>= 1;}
        return ans;
    }

    int inv(int n) {
        return fpow(n, mod - 2);
    }

    int A(int n, int m) {
        if(n < 0 || m < 0 || m > n) return 0;
        return fac[n] * finv[n - m] % mod;
    }

    int C(int n, int m) {
        if(m < 0 || m > n) return 0;
        return fac[n] * finv[m] % mod * finv[n - m] % mod;
    }

    int Catalan(int n) {  // 卡特兰数
        if(n == 0) return 1;
        else return C(n * 2, n) * inv(n + 1) % mod;
    }

    // int Catalan(int n, int mod) {  // when mod is not prime
    //     vector<int> cnt(n * 2, 0);
    //     fore(i, 2, n + 1) cnt[i] = -1;
    //     fore(i, n + 2, n * 2 + 1) cnt[i] = 1;
    //     for(int i = n * 2; i >= 2; i--) {
    //         if(is_prime(i)) continue;
    //         cnt[lpf[i]] += cnt[i];
    //         cnt[i / lpf[i]] += cnt[i];
    //         cnt[i] = 0;
    //     }
    //     int ans = 0;
    //     fore(i, 2, n * 2 + 1) {
    //         if(cnt[i] == 0) continue;
    //         ans = ans * fpow(i, cnt[i]) % mod;
    //     }
    //     return ans;
    // }
};

// const int N = 5005;
// int c[N][N];  // when mod is not prime
// void init(){
//     fore(i, 0, N) c[i][0] = 1;
//     fore(i, 1, N) fore(j, 1, i + 1) {
//         c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
//         c[i][j] %= mod;
//     }
// }
