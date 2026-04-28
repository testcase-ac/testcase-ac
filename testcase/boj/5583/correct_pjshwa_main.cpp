#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;
using tll = tuple<ll, ll, ll>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll MAX = 150, INF = 1e18;
vector<pll> R[MAX + 1];

// ith row, jth skip jump, kth rock
ll d[MAX + 1][MAX + 1][10];

void solve() {
  int n, m; cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    int k, x, d; cin >> k;
    while (k--) {
      cin >> x >> d;
      R[i].push_back({x, d});
    }
  }

  for (int i = 1; i <= n; i++) for (int j = 0; j <= m; j++) {
    fill(d[i][j], d[i][j] + 10, INF);
  }

  for (int j = 0; j < R[1].size(); j++) d[1][0][j] = 0;
  for (int j = 0; j < R[2].size(); j++) d[2][1][j] = 0;

  for (int i = 2; i <= n; i++) {
    // Normal jump
    for (int r1 = 0; r1 < R[i - 1].size(); r1++) for (int r2 = 0; r2 < R[i].size(); r2++) {
      for (int j = 0; j <= m; j++) {
        auto [x1, d1] = R[i - 1][r1];
        auto [x2, d2] = R[i][r2];
        d[i][j][r2] = min(d[i][j][r2], d[i - 1][j][r1] + abs(x1 - x2) * (d1 + d2));
      }
    }

    // Skip jump
    if (i == 2) continue;
    for (int r1 = 0; r1 < R[i - 2].size(); r1++) for (int r2 = 0; r2 < R[i].size(); r2++) {
      for (int j = 1; j <= m; j++) {
        auto [x1, d1] = R[i - 2][r1];
        auto [x2, d2] = R[i][r2];
        d[i][j][r2] = min(d[i][j][r2], d[i - 2][j - 1][r1] + abs(x1 - x2) * (d1 + d2));
      }
    }
  }

  ll ans = INF;
  for (int j = 0; j < R[n].size(); j++) for (int i = 0; i <= m; i++) ans = min(ans, d[n][i][j]);
  for (int j = 0; j < R[n - 1].size(); j++) for (int i = 0; i < m; i++) ans = min(ans, d[n - 1][i][j]);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
