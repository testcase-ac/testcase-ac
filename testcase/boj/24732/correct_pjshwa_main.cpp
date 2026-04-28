#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

vector<long long> calc(const vector<long long>& v , int N) {
  vector<long long> ans(N), apf(N);

  stack<pair<long long, long long>> s;
  s.push({v[0], 1});

  ans[0] = apf[0] = 1;
  for (int x = 1; x < N; x++) {
    long long rm = 0;
    while (!s.empty() && s.top().first > v[x]) {
      rm += s.top().second;
      s.pop();
    }
    s.push({v[x], rm + 1});

    if (x == 1) {
      ans[x] = min(v[0], v[1]);
      apf[x] = (apf[x - 1] + ans[x]) % MOD;
      continue;
    }

    if (rm == 0) ans[x] = ans[x - 1] + v[x - 1] * ans[x - 1];
    else {
      if (x - rm - 1 < 0) {
        ans[x] = (apf[x - 1] * min(v[x - 1], v[x])) % MOD;
      }
      else {
        long long diff = (apf[x - 1] + MOD - apf[x - rm - 1]) % MOD;
        ans[x] = ans[x - rm] + diff * min(v[x - 1], v[x]);
      }
    }

    ans[x] = ans[x] % MOD;
    apf[x] = (apf[x - 1] + ans[x]) % MOD;
  }

  return ans;
}

int main() {
  int n;
  cin >> n;
  vector<long long> v(n);
  for (int i = 0; i < n; i++) {
    cin >> v[i];
  }

  auto e = calc(v, v.size());
  for (int i = 0; i < v.size(); i++) cout << e[i] << '\n';

}

