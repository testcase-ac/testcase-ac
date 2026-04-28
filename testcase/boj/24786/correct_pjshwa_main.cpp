#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n, e;
  cin >> n >> e;

  int phi = -1;
  for (int p = 2; p < 1000; p++) {
    if (n % p == 0) {
      phi = (p - 1) * ((n / p) - 1);
      break;
    }
  }

  for (ll d = 1; d < phi; d++) {
    if ((d * e) % phi == 1) return cout << d << '\n', void();
  }
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
