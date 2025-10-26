// 用于快速分解质因数

vector<int> min_p(N + 1);
  iota(min_p.begin(), min_p.end(), 0);
  fore(i, 2, N + 1) {
      if(min_p[i] == i) {
          for(int j = i; j <= N; j += i) {
              if(min_p[j] == j) min_p[j] = i; // 如果不需要找到最小质因子，只是分解这个if可以不要
          }
      }
  }

  auto fat = [&](int x) -> vector<pii> {
      vector<pii> ans;
      while(x > 1) {
          int p = min_p[x];
          int cnt = 0;
          while(x % p == 0) x /= p, cnt += 1;
          ans.emplace_back(p, cnt);
      }
      return ans;
  };
