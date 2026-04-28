#include <bits/stdc++.h>
using namespace std;

const int MOD = 2014;
map<string, int> dp;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int dfs(string s) {
  if(dp.find(s) != dp.end()) return dp[s];

  int ans = 1;
  int l = s.length();
  for (int i = 1; i * 2 < l ; ++i) {
    if (s.substr(0, i) == s.substr(l - i, i)) {
      ans += dfs(s.substr(i, l - i));
    }
    if (s.substr(0, i) == s.substr(i, i)) {
      ans += dfs(s.substr(i, l - i));
    }
    if (s.substr(0, i) == s.substr(l - i, i)) {
      ans += dfs(s.substr(0, l - i));
    }
    if (s.substr(l - i * 2, i) == s.substr(l - i, i)) {
      ans += dfs(s.substr(0, l - i));
    }
  }
  return dp[s] = ans % MOD;
}

int main() {
  fast_io();

  string s;
  cin >> s;
  cout << (dfs(s) - 1 + MOD) % MOD << '\n';
}
