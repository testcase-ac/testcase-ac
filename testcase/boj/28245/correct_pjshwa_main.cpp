#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ll n, dif = 1e18, ans; cin >> n;
  for (int b1 = 0; b1 < 60; b1++) for (int b2 = b1; b2 < 60; b2++) {
    ll u = (1LL << b1) + (1LL << b2);
    if (dif > abs(n - u)) {
      dif = abs(n - u);
      ans = u;
    }
    else if (dif == abs(n - u) && ans > u) ans = u;
  }

  for (int b1 = 0; b1 < 60; b1++) for (int b2 = b1; b2 < 60; b2++) {
    ll u = (1LL << b1) + (1LL << b2);
    if (u == ans) return cout << b1 << ' ' << b2 << '\n', void();
  }
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
