#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e7, MOD = 1e9 + 7;
int dp[MAXN + 1];

void solve() {
  int N; cin >> N;
  cout << dp[N] << '\n';
}

int main() {
  fast_io();

  dp[0] = dp[1] = 1; dp[4] = 2;
  for (int i = 5; i <= MAXN; i++) {
    dp[i] = (dp[i] + (ll)(i + 1) * dp[i - 1]) % MOD;
    dp[i] = (dp[i] - (ll)(i - 2) * dp[i - 2] % MOD + MOD) % MOD;
    dp[i] = (dp[i] - (ll)(i - 5) * dp[i - 3] % MOD + MOD) % MOD;
    dp[i] = (dp[i] + (ll)(i - 3) * dp[i - 4]) % MOD;
  }

  int t = 1;
  cin >> t;
  while (t--) solve();
}
