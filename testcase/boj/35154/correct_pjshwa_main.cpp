#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 5000, MOD = 998244353;
int dp[MAXN + 5][MAXN + 5];

void solve() {
  int x, ans = 0; cin >> x;
  if (x == 1) return cout << "-1\n", void();

  for (int i = 0; i <= x; ++i) {
    ans = (ans + dp[x][i]) % MOD;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();
  
  memset(dp, 0, sizeof dp); dp[0][0] = 1;
  for (int i = 1; i <= MAXN; ++i) for (int pd = 0; pd <= i; ++pd) {
    dp[i][pd] = dp[i - 1][pd + 1];
    if (pd > 0 && i >= 2) dp[i][pd] = (dp[i][pd] + dp[i - 2][pd - 1]) % MOD;
  }

  int t = 1;
  cin >> t;
  while (t--) solve();
}
