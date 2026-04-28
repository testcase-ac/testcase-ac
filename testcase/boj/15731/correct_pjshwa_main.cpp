#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 5000, MOD = 1e9 + 7;
int dp[MAXN + 1][MAXN + 1];

int val(int i, int l) {
  if (l == 0) return dp[i][l];
  return (dp[i][l] - dp[i][l - 1] + MOD) % MOD;
}

void solve() {
  string S; cin >> S;
  int N = S.size();

  for (int l = 0; l <= N; ++l) dp[0][l] = 1;
  for (int i = 1; i < N; ++i) {
    if (S[i - 1] == 'f') {
      for (int l = 1; l <= N; ++l) dp[i][l] = val(i - 1, l - 1);
    } else {
      for (int l = 0; l <= N; ++l) {
        dp[i][l] = (dp[i - 1][N] - dp[i - 1][l] + MOD) % MOD;
        dp[i][l] = (dp[i][l] + val(i - 1, l)) % MOD;
      }
    }
    for (int l = 1; l <= N; ++l) dp[i][l] = (dp[i][l] + dp[i][l - 1]) % MOD;
  }

  cout << dp[N - 1][N] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
