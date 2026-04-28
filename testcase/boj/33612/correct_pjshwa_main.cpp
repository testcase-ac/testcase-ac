#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int T; cin >> T;
  int y = 2024, m = 8;
  while (--T) {
    m += 7;
    if (m > 12) m -= 12, y++;
  }
  cout << y << " " << m << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
