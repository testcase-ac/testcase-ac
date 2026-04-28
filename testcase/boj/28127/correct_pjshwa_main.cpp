#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ll a, d, x; cin >> a >> d >> x;

  auto f = [&](ll n) {
    return n * a + n * (n - 1) * d / 2;
  };

  ll left = 1, right = x + 1;
  while (left < right) {
    ll mid = (left + right) / 2;

    if (x <= f(mid - 1)) right = mid;
    else left = mid + 1;
  }

  left--;
  ll sum = f(left - 1);
  cout << left << ' ' << x - sum << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
