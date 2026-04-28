#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXT = 200, MAXC = 10;
double dp[MAXT + 1][1 << MAXC];

int tc;
void solve() {
  cout << "Case #" << ++tc << ": ";

  int C, N; cin >> C >> N;
  memset(dp, 0, sizeof(dp)); dp[0][0] = 1;

  vector<int> B;
  for (int s = 0; s < (1 << C); ++s) {
    if (__builtin_popcount(s) == N) B.push_back(s);
  }

  double P = 1.0 / B.size();
  for (int t = 1; t <= MAXT; ++t) {
    for (int ps = 0; ps < (1 << C) - 1; ++ps) {
      for (int s : B) dp[t][ps | s] += dp[t - 1][ps] * P;
    }
  }

  double ans = 0;
  for (int t = 1; t <= MAXT; ++t) ans += t * dp[t][(1 << C) - 1];
  cout << fixed << setprecision(10) << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
