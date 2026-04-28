#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 3e6;
ll z[MAX + 1], d[MAX + 1];

void solve() {
  ll l, ml, mk, amm;
  cin >> l >> ml >> mk >> amm;

  for (int i = 1; i <= l; i++) cin >> z[i];

  ll pf = 0;
  for (int i = 1; i <= l; i++) {
    pf += d[i];
    if (z[i] <= pf + mk) {
      if (i + ml <= l) d[i + ml] -= mk;
      pf += mk;
    }
    else if (amm) amm--;
    else return cout << "NO\n", void();
  }

  cout << "YES\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
