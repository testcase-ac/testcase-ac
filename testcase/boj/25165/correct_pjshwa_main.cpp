#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n, m, y, d, sr, sc;
  cin >> n >> m >> y >> d >> sr >> sc;

  int x = 1;
  bool f = false;
  while (1) {
    if (x == sr && y == sc) f = true;
    if (x == n && y == m) break;

    if (d) {
      if (y == m) x++, d ^= 1;
      else y++;
    }
    else {
      if (y == 1) x++, d ^= 1;
      else y--;
    }
  }

  if (f) cout << "NO...\n";
  else cout << "YES!\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
