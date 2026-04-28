#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, K; cin >> N >> K;

  set<pii> obs;
  for (int i = 0; i < N; ++i) {
    int xi, yi; cin >> xi >> yi;
    obs.insert({xi, yi});
  }

  int cx = 0, cy = 0;
  string Q; cin >> Q;
  for (char c : Q) {
    int nx, ny;
    if (c == 'U') nx = cx, ny = cy + 1;
    if (c == 'D') nx = cx, ny = cy - 1;
    if (c == 'L') nx = cx - 1, ny = cy;
    if (c == 'R') nx = cx + 1, ny = cy;
    if (obs.count({nx, ny})) continue;
    cx = nx, cy = ny;
  }

  cout << cx << ' ' << cy << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
