#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll MAXN = 100, MAXV = 10000, INF = 1e18;
ll dp[MAXN + 1][MAXN + 1][MAXV + 1];

void solve() {
  int N, M; cin >> N >> M;

  vector<tuple<int, int, int>> A;
  for (int i = 0; i < N; ++i) {
    int a, b, c; cin >> a >> b >> c;
    A.emplace_back(a, b, c);
  }
  sort(A.begin(), A.end(), [](auto &x, auto &y) {
    return get<1>(x) > get<1>(y);
  });

  for (int i = 0; i <= N; ++i) for (int j = 0; j <= N; ++j) {
    fill(dp[i][j], dp[i][j] + MAXV + 1, -INF);
  }
  dp[0][0][0] = 0;

  for (int i = 1; i <= N; ++i) for (int j = 0; j <= i; ++j) {
    auto [a, b, c] = A[i - 1];
    for (int k = 0; k <= M; ++k) {
      dp[i][j][k] = max(dp[i][j][k], dp[i - 1][j][k]);
      if (j > 0 && k >= c) {
        int val = a + (N - j) * b;
        dp[i][j][k] = max(dp[i][j][k], dp[i - 1][j - 1][k - c] + val);
      }
    }
  }

  ll ans = 0;
  for (int j = 0; j <= N; ++j) for (int k = 0; k <= M; ++k) {
    ans = max(ans, dp[N][j][k]);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
