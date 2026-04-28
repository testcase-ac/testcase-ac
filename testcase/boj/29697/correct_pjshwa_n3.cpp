#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll MAXN = 1e5, INF = 1e18;
ll C[MAXN + 1], dp[MAXN + 1];

ll C2(ll x) {
  return x * (x + 1) / 2;
}

void solve() {
  ll N, P; cin >> N >> P;
  for (int i = 1; i <= N; ++i) cin >> C[i];

  function<ll(ll, ll)> f = [&](int x, int y) {
    // cout << "x = " << x << ", y = " << y << '\n';
    ll ret = INF;
    for (int i = x; i <= y; ++i) {
      ll cost = C2(i - x + 1) + C2(y - i + 1) - 1;
      if (cost <= P) {
        // cout << "i = " << i << ", C[i] = " << C[i] << ", cost = " << cost << '\n';
        ret = min(ret, C[i]);
      }
    }
    return ret;
  };

  fill(dp + 1, dp + N + 1, INF);
  for (int i = 1; i <= N; ++i) {
    for (int j = 0; j < i; ++j) {
      dp[i] = min(dp[i], dp[j] + f(j + 1, i));
    }
  }
  cout << dp[N] << '\n';

  // backtrack
  for (int i = N; i > 0; ) {
    for (int j = 0; j < i; ++j) {
      if (dp[i] == dp[j] + f(j + 1, i)) {
        // cout << "j: " << j << ", i: " << i << '\n';
        i = j;
        break;
      }
    }
  }

}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
