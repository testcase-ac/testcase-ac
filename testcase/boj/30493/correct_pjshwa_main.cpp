#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 2000;
ll dp[MAXN + 1][MAXN + 1];
ll S[MAXN + 1], P[MAXN + 1], E[MAXN + 1], A[MAXN + 1];

void solve() {
  int N; cin >> N;
  for (int i = 1; i <= N; i++) cin >> S[i] >> P[i] >> E[i] >> A[i];

  for (int i = 0; i <= N; ++i) for (int j = 0; j <= N; ++j) dp[i][j] = LLONG_MIN;
  dp[0][0] = 0;

  for (int i = 1; i <= N; ++i) for (int j = 0; j <= N; ++j) {
    dp[i][j] = dp[i - 1][j] + (S[i] - E[i - 1]);
    if (j == 0) continue;
    ll U = dp[i - 1][j - 1] + (S[i] - E[i - 1]);
    if (U >= A[i]) dp[i][j] = max(dp[i][j], U - A[i] + (E[i] - P[i]));
  }

  for (int j = N; j >= 0; --j) {
    if (dp[N][j] >= 0) return cout << j << '\n', void();
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
