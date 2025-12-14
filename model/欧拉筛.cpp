vector<int> prime;
vector<int> lpf;  // Least Prime Factor
void sieve(int n) {
    lpf.resize(n + 1, 0);
    fore(i, 2, n + 1) {
        if(lpf[i] == 0) {
            prime.emplace_back(i);
            lpf[i] = i;
        }
        for(int p : prime) {
            if((ll)i * p > n) break;
            lpf[i * p] = p;
            if(i % p == 0) break;
        }
    }
}

bool is_prime(int n) {
    if(n <= 1) return false;
    else return lpf[n] == n;
}

vector<pii> fat(int x) {  // factorize
    vector<pii> ans;
    while(x > 1) {
        int p = lpf[x];
        int cnt = 0;
        while(x % p == 0) x /= p, cnt += 1;
        ans.emplace_back(p, cnt);
    }
    return ans;
}
