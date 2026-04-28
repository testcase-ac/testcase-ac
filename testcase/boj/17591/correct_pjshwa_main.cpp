#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 100;
int A[MAXN + 1]; double dp[MAXN + 1][MAXN + 1];

void solve() {
  int N; cin >> N;
  for (int i = 1; i <= N; ++i) cin >> A[i];
  sort(A + 1, A + N + 1, greater<int>());

  dp[0][0] = 1;
  for (int i = 1; i <= N; ++i) {
    double p = (double)A[i] / 100;
    for (int v = 0; v <= i; ++v) {
      dp[i][v] = dp[i - 1][v] * (1 - p);
      if (v > 0) dp[i][v] += dp[i - 1][v - 1] * p;
    }
  }

  double ans = 0;
  for (int s = 1; s <= N; ++s) {
    double exp = 0;
    for (int a = 1; a <= N; ++a) {
      double p = dp[s][a], v = pow(a, (double)a / s);
      exp += p * v;
    }
    ans = max(ans, exp);
  }
  cout << fixed << setprecision(9) << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
