#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int ymax = 1001, xc, yc, N; cin >> N;
  for (int i = 0; i < N; i++) {
    int x, y; cin >> x >> y;
    if (ymax > y) {
      ymax = y;
      xc = x;
      yc = y;
    }
  }
  cout << xc << ' ' << yc << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
