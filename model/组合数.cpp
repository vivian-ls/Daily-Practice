const int N = 1e6 + 5;
int fac[N], inv[N], p[N];
void init(){
    fac[0] = inv[0] = 1;
    fore(i, 1, N + 1) fac[i] = fac[i - 1] * i % mod;
    inv[N] = fpow(fac[N], mod - 2);
    for (int i = N - 1; i >= 1; i--)
        inv[i] = inv[i + 1] * (i + 1) % mod;
    p[1] = 2;
    fore(i, 2, N + 1) p[i] = p[i - 1] * 2 % mod;
}
int A(int n, int m) {
    return fac[n] * inv[n - m] % mod;
}

int C(int n, int m) {
    return fac[n] * inv[m] % mod * inv[n - m] % mod;
}

int Catalan(int n) {  // 卡特兰数
    if(n == 0) return 1;
    else return C(n * 2, n) * fpow(n + 1, mod - 2) % mod;
}

int Catalan(int n, int mod) {  // when mod is not prime
    vector<int> cnt(n * 2, 0);
    fore(i, 2, n + 1) cnt[i] = -1;
    fore(i, n + 2, n * 2 + 1) cnt[i] = 1;
    for(int i = n * 2; i >= 2; i--) {
        if(lpf[i] == 0) continue;
        cnt[lpf[i]] += cnt[i];
        cnt[i / lpf[i]] += cnt[i];
        cnt[i] = 0;
    }
    int ans = 0;
    fore(i, 2, n * 2 + 1) {
        if(cnt[i] == 0) continue;
        ans = ans * fpow(i, cnt[i], mod) % mod;
    }
    return ans;
}


const int N = 5005;
int c[N][N];  // when mod is not prime
void init(){
    fore(i, 0, N) c[i][0] = 1;
    fore(i, 1, N) fore(j, 1, i + 1) {
        c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
        c[i][j] %= mod;
    }
}
