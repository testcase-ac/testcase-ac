#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ll n, s, t; cin >> n >> s >> t;

  ll ans = 0;
  while (n) {
    if (n & 1) {
      n--; ans += s;
    }
    else {
      ll h = n / 2;
      if (h > t) ans += t;
      else ans += min(h * s, t);
      n -= h;
    }
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
