#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll MAX = 5e5, INF = 1e18;
int A[MAX + 1], inv[MAX + 1];

void solve() {
  int N = 6;

  int ans = 1 << N, B[6][6];
  for (int s = 0; s < (1 << N); s++) {
    B[2][0] = (s & 1) ? 1 : 0;
    B[1][0] = (s & 2) ? 1 : 0;
    B[1][1] = (s & 4) ? 1 : 0;
    B[0][0] = (s & 8) ? 1 : 0;
    B[0][1] = (s & 16) ? 1 : 0;
    B[0][2] = (s & 32) ? 1 : 0;

    if (!(B[0][0] == 1 || B[0][1] == 1)) continue;
    if (!(B[0][2] == 1 || B[0][1] == 1)) continue;
    if (!(B[1][0] == 1 || B[1][1] == 1)) continue;

    ans++;
  }

  for (int s = 0; s < (1 << N); s++) {
    B[0][0] = (s & 8) ? 1 : 0;
    B[0][1] = (s & 16) ? 1 : 0;
    B[0][2] = (s & 32) ? 1 : 0;
    B[0][3] = (s & 4) ? 1 : 0;
    B[1][0] = (s & 1) ? 1 : 0;
    B[1][1] = (s & 2) ? 1 : 0;

    if (!(B[0][0] == 1 || B[0][1] == 1)) continue;
    if (!(B[0][2] == 1 || B[0][1] == 1)) continue;

    ans++;
  }

  for (int s = 0; s < (1 << N); s++) {
    B[0][0] = (s & 8) ? 1 : 0;
    B[0][1] = (s & 16) ? 1 : 0;
    B[0][2] = (s & 32) ? 1 : 0;
    B[0][3] = (s & 4) ? 1 : 0;
    B[1][1] = (s & 1) ? 1 : 0;
    B[1][2] = (s & 2) ? 1 : 0;

    if (!(B[0][3] == 1 || B[0][2] == 1)) continue;
    if (!(B[0][2] == 1 || B[0][1] == 1)) continue;

    ans++;
  }

  for (int s = 0; s < (1 << N); s++) {
    B[0][0] = (s & 8) ? 1 : 0;
    B[0][1] = (s & 16) ? 1 : 0;
    B[0][2] = (s & 32) ? 1 : 0;
    B[0][3] = (s & 4) ? 1 : 0;
    B[1][0] = (s & 1) ? 1 : 0;
    B[1][2] = (s & 2) ? 1 : 0;

    if (!(B[0][0] == 1 || B[0][1] == 1)) continue;
    if (!(B[0][2] == 1 || B[0][3] == 1)) continue;

    ans++;
  }

  for (int j = 0; j < 4; j++) {

    for (int s = 0; s < (1 << N); s++) {
      B[0][0] = (s & 8) ? 1 : 0;
      B[0][1] = (s & 16) ? 1 : 0;
      B[0][2] = (s & 32) ? 1 : 0;
      B[0][3] = (s & 4) ? 1 : 0;
      B[0][4] = (s & 1) ? 1 : 0;
      B[1][j] = (s & 2) ? 1 : 0;

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
