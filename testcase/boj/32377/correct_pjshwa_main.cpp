#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ll N, x, y, z; cin >> N >> x >> y >> z;
  auto f = [&](ll t) {
    return t / x + t / y + t / z;
  };

  ll l = 1, r = N * (x + y + z);
  while (l < r) {
    ll m = (l + r) / 2, cnt = f(m);
    if (cnt >= N) r = m;
    else l = m + 1;
  }

  ll t = N - f(l - 1);
  if (l % x == 0 && --t == 0) return cout << "A win\n", void();
  if (l % y == 0 && --t == 0) return cout << "B win\n", void();
  if (l % z == 0 && --t == 0) return cout << "C win\n", void();
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
