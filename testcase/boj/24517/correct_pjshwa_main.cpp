#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

bool d[56][1 << 10];

void solve() {
  int q;
  cin >> q;

  while (q--) {
    int a, b, k;
    cin >> a >> b >> k;

    int diff = b - a;
    bool flip = false;
    if (k & 1) {
      diff %= (k * (k + 1));
      if (2 * diff >= k * (k + 1)) flip = true;
    }
    diff %= (k * (k + 1) / 2);

    cout << (d[diff][(1 << k) - 1] ^ flip ? "swoon" : "raararaara") << '\n';
  }
}

int main() {
  fast_io();

  for (int j = 0; j < (1 << 10); j++) d[0][j] = false;
  for (int i = 1; i <= 55; i++) for (int j = 0; j < (1 << 10); j++) {
    bool f = true;
    for (int k = 0; k < 10; k++) {
      if (j & (1 << k)) {
        if (i < k + 1) f = false;
        else f &= d[i - k - 1][j ^ (1 << k)];
      }
    }
    d[i][j] = !f;
  }

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
