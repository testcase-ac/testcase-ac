#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 10'000, MOD = 1e9 + 7;
int dp[MAXN + 1][7][7];

void solve() {
  int N; cin >> N;
  cout << dp[N][0][0] << '\n';
}

int main() {
  fast_io();

  for (int d = 1; d <= 9; ++d) dp[1][d % 7][d % 7] += 1;
  for (int i = 2; i <= MAXN; ++i) for (int d = 0; d < 10; ++d) {
    for (int pr = 0; pr < 7; ++pr) for (int pu = 0; pu < 7; ++pu) {
      int nr = (pr + d) % 7, nu = (pu * d) % 7;
      dp[i][nr][nu] = (dp[i][nr][nu] + dp[i - 1][pr][pu]) % MOD;
    }
  }

  int t = 1;
  cin >> t;
  while (t--) solve();
}
