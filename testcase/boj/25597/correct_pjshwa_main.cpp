#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int INF = 0x3f3f3f3f;

void solve() {
  int X, T;
  cin >> X >> T;

  int mpress = INF, mconfig = -1;
  for (int s = 1; s < (1 << 3); s++) {
    int u[3] = {0}, OX = X;
    for (int j = 0; j < 3; j++) {
      if (!(s & (1 << j))) continue;

      if (j == 0) u[j] += OX / 8, OX %= 8;
      if (j == 1) u[j] += OX / 4, OX %= 4;
      if (j == 2) u[j] += OX, OX = 0;
    }
    if (OX) continue;
    if (u[0] + u[1] + u[2] > T) continue;

    int cnt = __builtin_popcount(s);
    if (mpress > cnt) {
      mpress = cnt;
      mconfig = s;
    }
  }
  if (mconfig == -1) return cout << "-1\n", void();

  int u[3] = {0};
  for (int j = 0; j < 3; j++) {
    if (!(mconfig & (1 << j))) continue;

    if (j == 0) u[j] += X / 8, X %= 8;
    if (j == 1) u[j] += X / 4, X %= 4;
    if (j == 2) u[j] += X, X = 0;
  }
  assert(X == 0);

  cout << mpress << '\n';
  vector<pii> ans;
  if (u[0]) ans.push_back({u[0], 8});
  if (u[1]) ans.push_back({u[1], 4});
  if (u[2]) ans.push_back({u[2], 1});

  int ltime = T - (u[0] + u[1] + u[2]);
  for (auto& [t, d] : ans) {
    cout << ltime << ' ' << d << '\n';
    ltime += t;
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
