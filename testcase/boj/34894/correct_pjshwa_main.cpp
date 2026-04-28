#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll MAXN = 3e5, INF = 1e18;
ll A[MAXN + 1], dp[MAXN + 1][6];

void solve() {
  int N; string S; cin >> N >> S;
  for (int i = 1; i <= N; ++i) cin >> A[i];
  for (int i = 0; i <= N; ++i) for (int j = 0; j < 6; ++j) dp[i][j] = INF;

  dp[0][0] = 0; string T = "UOSPC";
  for (int i = 1; i <= N; ++i) {
    char c = S[i - 1]; int cost = A[i];
    for (int j = 0; j < 6; ++j) dp[i][j] = dp[i - 1][j];
    for (int j = 0; j < 5; ++j) {
      if (c != T[j]) continue;
      dp[i][j + 1] = min(dp[i][j + 1], dp[i - 1][j] + cost);
    }
  }

  ll ans = dp[N][5];
  if (ans == INF) cout << "-1\n";
  else cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
