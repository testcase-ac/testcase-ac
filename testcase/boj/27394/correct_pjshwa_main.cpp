#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ll t, s; cin >> t >> s;

  ll tot = 0, avail = 0, sx, tx;
  for (int y = s; y >= 1; --y) {
    // find largest x
    ll x;
    {
      int l = 1, r = s + 1;
      while (l < r) {
        int x = (l + r) / 2;
        if (2 * max(x, y) + min(x, y) > 2 * s) r = x;
        else l = x + 1;
      }
      x = l - 1;
    }
    sx = min(2 * s + 1, 2 * x + 1);

    {
      int l = 0, r = t + 1;
      while (l < r) {
        int x = (l + r) / 2;
        if (x + y > t) r = x;
        else l = x + 1;
      }
      x = l - 1;
    }

    if (x == -1) tx = 0;
    else tx = min(2 * t + 1, 2 * x + 1);

    tot += sx;
    avail += min(sx, tx);
  }
  tot *= 2; avail *= 2;

  for (int x = -s; x <= s; ++x) {
    ++tot;
    if (abs(x) <= t) ++avail;
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
