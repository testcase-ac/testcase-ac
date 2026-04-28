#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

ll f(ll x) {
  if (x == 1) return 1;

  ll h = x / 2;
  if (x % 2 == 0) {
    return 3 * f(h);
  }
  else return 2 * f(h) + f(h + 1);
}

void solve() {
  ll N; cin >> N;
  cout << f(N) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
