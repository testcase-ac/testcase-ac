#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  long double L; cin >> L;
  long double ans = sqrt(3) / 4;
  ans *= (L * L);
  cout << fixed << setprecision(12) << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
