#include <bits/stdc++.h> 
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int INF = 0x3f3f3f3f;

void solve() {
  int N; cin >> N;
  ll uv = INF, lv = -INF, uh = INF, lh = -INF;
  for (int i = 0; i < N; i++) {
    ll x, y; string d;
    cin >> x >> y >> d;
    if (d == "L") uh = min(uh, x - 1);
    if (d == "R") lh = max(lh, x + 1);
    if (d == "U") lv = max(lv, y + 1);
    if (d == "D") uv = min(uv, y - 1);
  }

  if (uv == INF || lv == -INF || uh == INF || lh == -INF) cout << "Infinity\n";
  else cout << (uv - lv + 1) * (uh - lh + 1) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
