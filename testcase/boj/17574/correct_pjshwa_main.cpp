#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

ll n, m; double F;
double f(ll d) {
  return (m - (d * F) * (d * F)) / (n - d);
}

void solve() {
  cin >> n >> m >> F;

  // Ternary search
  ll left = 0, right = n - 1;
  while (left + 3 <= right) {
    ll mid1 = left + (right - left) / 3;
    ll mid2 = right - (right - left) / 3;

    if (f(mid1) > f(mid2)) right = mid2;
    else left = mid1;
  }

  double ans = 0;
  for (ll i = left; i <= right; i++) ans = max(ans, f(i));
  cout << fixed << setprecision(10) << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
