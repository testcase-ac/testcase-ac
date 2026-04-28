#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, K; cin >> N >> K;

  int xsum = 0, ysum = 0;
  for (int i = 0; i < N; i++) {
    int x, y; cin >> x >> y;

    int ywin = ysum + y >= K;
    if (ywin) {
      // Overpower disabled
      int xwin = xsum + x >= K || xsum + x - ysum - y >= 50;
      if (xwin) cout << "1\n";
      else cout << "-1\n";
      return;
    }
    else {
      // Check if Overpower works
      int xp = 3 * x / 2;
      int xwin = xsum + xp >= K || xsum + xp - ysum - y >= 50;
      if (xwin) return cout << "1\n", void();
    }
    xsum += x; ysum += y;
  }
  cout << "0\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
