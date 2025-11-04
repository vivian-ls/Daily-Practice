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
