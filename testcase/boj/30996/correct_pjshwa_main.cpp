#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 3e4;
int A[MAXN + 1], sumA;
int N, M, Q;

void solve_Mlarge() {
  // approximate to normal distribution
  ld mu = 0, var = 0;

  for (int i = 1; i <= N; ++i) mu += A[i] * i;
  mu /= sumA;

  for (int i = 1; i <= N; ++i) var += A[i] * (i - mu) * (i - mu);
  var /= sumA;

  // sum(Xi) ~ N(M * mu, M * var)
  // probability of getting a sum in [1, x]
  while (Q--) {
    int x; cin >> x;

    ld ans;
    if (var == 0) {
      ans = x == M * mu ? 1 : 0;
    }
    else {
      // cumulative distribution function
      auto cdf = [&](ld x) {
        return 0.5 * (1 + erf((x - M * mu) / sqrt(2 * M * var)));
      };
      ans = cdf(x + 0.5);
    }
  
    cout << fixed << setprecision(10) << ans << '\n';
  }

}

void solve() {
  cin >> N >> M >> Q;

  sumA = 0;
  for (int i = 1; i <= N; ++i) cin >> A[i], sumA += A[i];

  if (M >= 100) return solve_Mlarge();

  vector<vector<ld>> dp(2, vector<ld>(N * M + 1));
  dp[0][0] = 1;

  for (int l = 1; l <= M; ++l) {
    int x = l % 2;
    for (int v = 0; v <= N * M; ++v) dp[x][v] = 0;
    for (int i = 1; i <= N; ++i) {
      for (int v = 0; v <= N * M; ++v) {
        if (v >= i) dp[x][v] += dp[1 - x][v - i] * ((ld)A[i] / sumA);
      }
    }
  }

  vector<ld> pre(N * M + 1);
  for (int i = 1; i <= N * M; ++i) pre[i] = pre[i - 1] + dp[M % 2][i];

  while (Q--) {
    int x; cin >> x;
    cout << fixed << setprecision(10) << pre[x] << '\n';
  }

}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
