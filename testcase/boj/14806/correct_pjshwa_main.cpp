#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int tc;
void solve() {
  cout << "Case #" << ++tc << ": ";

  int N, C[6];
  cin >> N >> C[0] >> C[1] >> C[2] >> C[3] >> C[4] >> C[5];

  int mv = 0, mi;
  for (int i = 0; i < 6; i++) {
    if (2 * C[i] > N) return cout << "IMPOSSIBLE\n", void();
    if (C[i] > mv) mv = C[i], mi = i;
  }
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
