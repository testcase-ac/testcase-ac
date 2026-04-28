#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int C[3], D[3];
  for (int i = 0; i < 3; ++i) cin >> C[i] >> D[i];

  int H; cin >> H;
  for (int s = 0;; ++s) {
    for (int i = 0; i < 3; ++i) {
      if (s % C[i] == 0) H -= D[i];
    }
    if (H <= 0) return cout << s << '\n', void();
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
