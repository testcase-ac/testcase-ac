#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ll n;
  cin >> n;

  ll l = __lg(n), ans = n * (n + 1) / 2;
  for (int i = 0; i < l; i++) {
    ans -= (1LL << i) * (1LL << i);
  }
  ans -= (n - (1LL << l) + 1) * (1LL << l);

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
