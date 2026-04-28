#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 100, MOD = 1001113;
int dp[MAXN + 1][MAXN + 1];

void solve() {
  int tc, N, v; cin >> tc >> N >> v;
  cout << tc << ' ' << dp[N][v] << '\n';
}

int main() {
  fast_io();
  
  memset(dp, 0, sizeof dp); dp[1][0] = 1;
  for (int i = 2; i <= MAXN; ++i) for (int pd = 0; pd < i - 1; ++pd) {
    ll pre = dp[i - 1][pd];
    dp[i][pd + 1] = (dp[i][pd + 1] + pre * (i - pd - 1) % MOD) % MOD;
    dp[i][pd] = (dp[i][pd] + pre * (pd + 1) % MOD) % MOD;
  }

  int t = 1;
  cin >> t;
  while (t--) solve();
}
