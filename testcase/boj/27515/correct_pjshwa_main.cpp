#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

ll run = 0;
void q() {
  ll x; cin >> x;
  run += x;

  for (int b = 62; b >= 0; b--) {
    if (run & (1LL << b)) {
      cout << (1LL << b) << '\n';
      return;
    }
  }
  cout << "0\n";
}

void solve() {
  int Q; cin >> Q;
  while (Q--) q();
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
