#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int X; cin >> X;
  for (int i = X + 1; i <= 9999; ++i) {
    int fh = i / 100, sh = i % 100;
    if ((fh + sh) * (fh + sh) == i) {
      cout << i << '\n';
      return;
    }
  }
  cout << "-1\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
