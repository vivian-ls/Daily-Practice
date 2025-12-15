int fpow(int a, int b, int mod) {
    if(b < 0) return 0;
    int ans = 1;
    while (b) { if (b & 1) ans = ans * a % mod; a = a * a % mod; b >>= 1;}
    return ans;
}

const int N = 2e6;
int fac[N + 5], finv[N + 5];
int inv(int n) {
    return fpow(n, mod - 2, mod);
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
    else return C(n * 2, n) * fpow(n + 1, mod - 2, mod) % mod;
}
void init(){
    fac[0] = finv[0] = 1;
    fore(i, 1, N + 1) fac[i] = fac[i - 1] * i % mod;
    finv[N] = inv(fac[N]);
    for (int i = N - 1; i >= 1; i--)
        finv[i] = finv[i + 1] * (i + 1) % mod;
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
