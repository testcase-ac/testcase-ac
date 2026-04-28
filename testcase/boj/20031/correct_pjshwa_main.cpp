#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; string S; cin >> N >> S;
  vector<pii> D;
  for (char c : S) {
    if (c == 'U') D.emplace_back(0, 1);
    if (c == 'D') D.emplace_back(0, -1);
    if (c == 'L') D.emplace_back(-1, 0);
    if (c == 'R') D.emplace_back(1, 0);
  }

  int Q; cin >> Q;
  while (Q--) {
    int sx, sy; cin >> sx >> sy;
    for (auto& [dx, dy] : D) {
      int nx = sx + dx, ny = sy + dy;
      if (nx == 0 && ny == 0) continue;
      sx = nx, sy = ny;
    }
    cout << sx << ' ' << sy << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
