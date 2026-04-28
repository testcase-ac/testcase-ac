#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 5000, INF = 0x3f3f3f3f;
int N, A[MAXN + 1], P[MAXN + 1], dp[MAXN + 1][MAXN + 1][2];

void solve() {
  cin >> N;
  for (int i = 1; i <= N; ++i) cin >> A[i];
  for (int i = 1; i <= N; ++i) P[i] = P[i - 1] ^ A[i];

  // dp[i][t][b] = ends with i, uses t transforms
  // if b = 1, max value it can have.
  // if b = 0, min value it can have.
  dp[1][0][0] = dp[1][0][1] = A[1];
  for (int i = 2; i <= N; ++i) for (int t = 0; t < i; ++t) {
    int pi = i - t - 1;

  }
    // not transform
    dp[i][t][0] = min(dp[i - 1][t][0], dp[i - 1][t][1] ^ A[i]);
    dp[i][t][1] = max(dp[i - 1][t][1], dp[i - 1][t][0] ^ A[i]);

    // transform
    if (t > 0) {
      dp[i][t][0] = min(dp[i][t][0], dp[i - 1][t - 1][0] ^ P[i]);
      dp[i][t][1] = max(dp[i][t][1], dp[i - 1][t - 1][1] ^ P[i]);
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
