#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n; string ps;
  cin >> n >> ps;

  set<string> u;
  bool f = false;
  u.insert(ps);

  while (u.size() < (1 << n)) {
    cout << ps << '\n';
    for (int i = 0; i < n; i++) ps[i] ^= 1;

    if (f) {
      for (int i = 0; i < n; i++) {
        ps[i] ^= 1;
        if (u.count(ps)) ps[i] ^= 1;
        else break;
      }
    }

    u.insert(ps);
    f = !f;
  }
  cout << ps << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
