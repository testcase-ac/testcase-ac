#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int MW, MB, TW, TB, PW, PB;
  cin >> MW >> MB >> TW >> TB >> PW >> PB;

  int w1 = min({2 * MB + 1, 2 * MW, 2 * TB, 2 * TW + 1, 2 * PB + 1, 2 * PW});
  int w2 = min({2 * MB, 2 * MW + 1, 2 * TB + 1, 2 * TW, 2 * PB, 2 * PW + 1});
  cout << max(w1, w2) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
