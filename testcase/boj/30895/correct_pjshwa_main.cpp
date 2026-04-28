#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ll X, Y, K; cin >> X >> Y >> K;

  __int128_t dbase = (K - 1) / (X + Y) + 1;

  // loop for each denominator
  __int128_t pn = -1, pd = -1;
  for (ll da = 0; da <= X; ++da) {
    __int128_t d = dbase + da;
    __int128_t mmin = (d - 1) * (X + Y) + 1;
    mmin = max(mmin, (__int128_t)K);

    __int128_t n = (mmin - 1) / X + 1;
    __int128_t g = __gcd(n, d);
    n /= g; d /= g;
    if (pd == -1 || n * pd < pn * d) {
      pn = n;
      pd = d;
    }
  }

  for (__int128_t da = 0; da <= X; ++da) {
    __int128_t d = dbase + da;
    __int128_t mmin = max((__int128_t)K, (d - 1) * (X + Y) + 1);
    __int128_t n = (mmin - 1) / X + 1;
    __int128_t g = __gcd(n, d);
    n /= g; d /= g;
    if (n != pn || d != pd) continue;

    __int128_t cd = dbase + da;
    for (__int128_t mana = mmin; mana <= mmin + (X + Y); ++mana) {
      __int128_t cn = (mana - 1) / X + 1;
      if (n * cd == cn * d) {
        cout << (ll)mana << '\n';
        return;
      }
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
