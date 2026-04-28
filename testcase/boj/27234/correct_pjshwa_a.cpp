#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N = 3;

  int ans = 1 << N, B[6][6];

  for (int j = 0; j < 1; j++) {
    for (int s = 0; s < (1 << N); s++) {
      B[0][0] = (s & 4) ? 1 : 0;
      B[0][1] = (s & 2) ? 1 : 0;
      B[1][j] = (s & 1) ? 1 : 0;

      if (!(B[0][j] == 1 || B[0][j + 1] == 1)) continue;

      ans++;
    }
  }

  cout << ans << '\n';

}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
