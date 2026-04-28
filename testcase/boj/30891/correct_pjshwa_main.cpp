#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, R; cin >> N >> R;
  vector<pii> A;
  for (int i = 0; i < N; ++i) {
    int x, y; cin >> x >> y;
    A.emplace_back(x, y);
  }

  int mi, mj, mans = 0;
  for (int xi = -100; xi <= 100; ++xi) for (int yi = -100; yi <= 100; ++yi) {
    int cnt = 0;
    for (auto [x, y] : A) {
      int dist = (x - xi) * (x - xi) + (y - yi) * (y - yi);
      if (dist <= R * R) ++cnt;
    }
    if (cnt > mans) {
      mans = cnt;
      mi = xi;
      mj = yi;
    }
  }
  cout << mi << ' ' << mj << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
