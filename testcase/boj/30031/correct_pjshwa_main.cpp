#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;

  int ans = 0;
  for (int i = 0; i < N; ++i) {
    int X, Y; cin >> X >> Y;
    if (X == 136) ans += 1000;
    if (X == 142) ans += 5000;
    if (X == 148) ans += 10000;
    if (X == 154) ans += 50000;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
