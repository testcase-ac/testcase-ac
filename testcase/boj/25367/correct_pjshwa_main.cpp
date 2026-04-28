#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int by[60];
void solve() {
  ll x, y;
  cin >> x >> y;

  memset(by, 0, sizeof(by));
  int i = 0;
  while (y) {
    by[i++] = y & 1;
    y >>= 1;
  }

  int cnt = 0;
  for (int i = 59; i >= 0; i--) {
    if (by[i]) {
      cnt++;
      x -= (1LL << i);
    }
    else if (x >= (1LL << (i + 1))) x -= (1LL << (i + 1));
  }

  if (x == 0) cout << (1LL << cnt) << '\n';
  else cout << "0\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
