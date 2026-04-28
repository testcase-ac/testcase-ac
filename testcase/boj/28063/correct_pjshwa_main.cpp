#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;
  if (N == 1) return cout << "0\n", void();

  int x, y; cin >> x >> y;
  bool xside = x == 1 || x == N;
  bool yside = y == 1 || y == N;

  int ans = 4; ans -= xside; ans -= yside;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
