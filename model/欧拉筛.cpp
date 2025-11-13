vector<int> is;
vector<int> prime;
void sieve(int n){
    is.resize(n + 1, true);
    is[0] = is[1] = false;
    for (int i = 2; i <= n; i++){
        if(is[i]) prime.push_back(i);
        for(int p : prime){
            if((ll)i * p > n) break;
            is[i * p] = false;
            if(i % p == 0) break;
        }
    }
}
