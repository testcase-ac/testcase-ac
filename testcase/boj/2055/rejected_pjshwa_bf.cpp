#include <bits/stdc++.h> 
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, M; cin >> N >> M;

  ll ans = 0;
  for (int x1 = 0; x1 <= N; ++x1) for (int y1 = 0; y1 <= M; ++y1)
  for (int x2 = 0; x2 <= N; ++x2) for (int y2 = 0; y2 <= M; ++y2)
  for (int x3 = 0; x3 <= N; ++x3) for (int y3 = 0; y3 <= M; ++y3) {
    if (x1 == x2 && y1 == y2) continue;
    if (x1 == x3 && y1 == y3) continue;
    if (x2 == x3 && y2 == y3) continue;

    // check if three points lie on a line
    if ((x2 - x1) * (y3 - y1) == (x3 - x1) * (y2 - y1)) continue;
    ++ans;
  }
  cout << ans / 6 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
