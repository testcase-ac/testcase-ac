#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, K; string S; cin >> N >> S >> K;
  int X = 0, U = 0, R = 0;
  for (char c : S) {
    if (c == 'U') U++;
    if (c == 'R') R++;
    if (c == 'X') X++;
  }

  int ans = 0;
  while (K--) {
    int x, y; cin >> x >> y; x--; y--;
    int m = min({x, y, X}); x -= m; y -= m;
    ans += x <= R && y <= U;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
