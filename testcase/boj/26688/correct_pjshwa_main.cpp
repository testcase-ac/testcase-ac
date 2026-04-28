#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 5000, MOD = 1e9 + 7;
int A[MAXN + 1], dp[MAXN + 1][MAXN + 1];

void solve() {
  int N; cin >> N;
  for (int i = 1; i <= N; ++i) cin >> A[i];
  sort(A + 1, A + N + 1);

  dp[1][1] = A[1] == 1;
  for (int i = 2; i <= N; ++i) {
    int x = A[i];
    if (x == 1) dp[i][1] = 1;

    // choose A[i]
    for (int j = x - 1; j <= MAXN; ++j) {
      int nx = min(j + x, MAXN);
      dp[i][nx] = (dp[i][nx] + dp[i - 1][j]) % MOD;
    }

    // don't choose A[i]
    for (int j = 1; j <= MAXN; ++j) {
      dp[i][j] = (dp[i][j] + dp[i - 1][j]) % MOD;
    }
  }

  int ans = 0;
  for (int i = 1; i <= MAXN; ++i) ans = (ans + dp[N][i]) % MOD;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
