#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5, MAXH = 100;
double dp[MAXN + 1][MAXH + 1];

void solve() {
  int n, h, a, Pi[3]; cin >> n >> h >> a >> Pi[0] >> Pi[1] >> Pi[2];
  int D[3] = {-1, 0, 1};
  double P[3] = {Pi[0] / 100.0, Pi[1] / 100.0, Pi[2] / 100.0};

  dp[0][a] = 1;
  for (int i = 1; i <= n; ++i) {
    for (int ph = 0; ph <= h; ++ph) {
      for (int j = 0; j < 3; ++j) {
        int nh = max(0, min(h, ph + D[j]));
        dp[i][nh] += dp[i - 1][ph] * P[j];
      }
    }
  }

  double ans = 0;
  for (int i = 0; i < n; ++i) {
    for (int ph = 0; ph <= h; ++ph) {
      for (int j = 0; j < 3; ++j) {
        double bonus = D[j] * 0.5;
        double area_exp = dp[i][ph] * max(0.0, min((double)h, ph + bonus));
        ans += area_exp * P[j];
      }
    }
  }
  cout << fixed << setprecision(9) << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
