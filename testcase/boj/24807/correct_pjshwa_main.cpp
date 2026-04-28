#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 250;

void solve() {
  int b, d, c, l;
  cin >> b >> d >> c >> l;

  bool found = false;
  for (int i = 0; i <= MAX; i++) for (int j = 0; j <= MAX; j++) for (int k = 0; k <= MAX; k++) {
    int x = i * b + j * d + k * c;
    if (x == l) found = true, cout << i << ' ' << j << ' ' << k << '\n';
  }

  if (!found) cout << "impossible\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
