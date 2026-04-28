#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ll U, O, S; cin >> U >> O >> S;
  ll D = U - S;
  if (D >= 3) {
    ll t = D / 3;
    U -= 2 * t; S += t;
  }
  cout << min({U, O, S}) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
