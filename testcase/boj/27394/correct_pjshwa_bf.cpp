#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ll t, s; cin >> t >> s;

  ll tot = 0, avail = 0;
  for (int x = -s; x <= s; ++x) for (int y = -s; y <= s; ++y) {
    int abs_x = abs(x), abs_y = abs(y);
    if (2 * max(abs_x, abs_y) + min(abs_x, abs_y) <= 2 * s) {
      ++tot;
      if (abs_x + abs_y <= t) ++avail;
    }
  }
  if (avail >= tot) return cout << "1\n", void();

  ll g = __gcd(tot, avail);
  tot /= g; avail /= g;
  cout << avail << '/' << tot << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
