#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int P3, P4, P0; cin >> P3 >> P4 >> P0;

  int T3 = 0, T4 = 0;
  while (P3 >= 3) {
    P3 -= 3;
    ++T3;
  }
  if (P3) {
    int need = 3 - P3;
    if (P0 < need) return cout << "-1\n", void();
    P0 -= need; ++T3;
  }

  while (P4 >= 4) {
    P4 -= 4;
    ++T4;
  }
  if (P4) {
    int need = 4 - P4;
    if (P0 < need) return cout << "-1\n", void();
    P0 -= need; ++T4;
  }

  for (int T3_add = 0; T3_add < 4; ++T3_add) {
    int P4_add = P0 - 3 * T3_add;
    if (P4_add < 0 || P4_add % 4) continue;
    int T4_add = P4_add / 4;
    cout << T3 + T3_add << ' ' << T4 + T4_add << '\n';
    return;
  }
  cout << "-1\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
