vector<int> prime;
vector<int> lpf;  // least prime fac
void sieve(int n) {
    lpf.resize(n + 1);
    fore(i, 1, n + 1) lpf[i] = i;
    fore(i, 2, n + 1) {
        if(lpf[i] == i) prime.emplace_back(i);
        for(int p : prime) {
            if(i * p > n) break;
            lpf[i * p] = p;
            if(i % p == 0) break;
        }
    }
}

bool is_prime(int x) {
    if(x <= 1) return false;
    else return lpf[x] == x;
}

vector<pii> fat_lpf(int n) {
    vector<pii> ans;
    while(n > 1) {
        int p = lpf[n];
        int cnt = 0;
        while(n % p == 0) n /= p, cnt += 1;
        ans.emplace_back(p, cnt);
    }
    return ans;
}

vector<pii> fat_s(int n) {
    vector<pii> ans;
    int cnt = 0;
    while(n % 2 == 0) n /= 2, cnt++;
    if(cnt) ans.emplace_back(2, cnt);
    for(int p = 3; p * p <= n; p += 2) {
        if(n % p != 0) continue;
        int cnt = 0;
        while(n % p == 0) n /= p, cnt++;
        ans.emplace_back(p, cnt);
    }
    if(n > 1) ans.emplace_back(n, 1);
    return ans;
}
