#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int Q; cin >> Q;

  ll add = 0, mul = 1, cur = 1;
  while (Q--) {
    ll op, x; cin >> op;
    if (op == 0) cin >> x, add += x;
    if (op == 1) cin >> x, mul *= x, add *= x;
    if (op == 2) cin >> x, cur += x;
    if (op == 3) cout << (cur * mul + add) << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
