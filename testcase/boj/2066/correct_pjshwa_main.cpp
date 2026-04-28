#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

ld dp[5][5][5][5][5][5][5][5][5];
string S[10][5];

ld rec(int i1, int i2, int i3, int i4, int i5, int i6, int i7, int i8, int i9) {
  if (i1 == 0 && i2 == 0 && i3 == 0 && i4 == 0 && i5 == 0 && i6 == 0 && i7 == 0 && i8 == 0 && i9 == 0) return 1;
  if (dp[i1][i2][i3][i4][i5][i6][i7][i8][i9] != -1) return dp[i1][i2][i3][i4][i5][i6][i7][i8][i9];

  int T[10];
  T[1] = i1; T[2] = i2; T[3] = i3; T[4] = i4; T[5] = i5; T[6] = i6; T[7] = i7; T[8] = i8; T[9] = i9;

  int tot = 0;
  for (int u = 1; u <= 9; ++u) for (int v = u + 1; v <= 9; ++v) {
    if (T[u] == 0 || T[v] == 0) continue;
    if (S[u][T[u]][0] != S[v][T[v]][0]) continue;
    ++tot;
  }

  ld ans = 0, prob = 1.0 / tot;
  for (int u = 1; u <= 9; ++u) for (int v = u + 1; v <= 9; ++v) {
    if (T[u] == 0 || T[v] == 0) continue;
    if (S[u][T[u]][0] != S[v][T[v]][0]) continue;

    --T[u]; --T[v];
    ans += prob * rec(T[1], T[2], T[3], T[4], T[5], T[6], T[7], T[8], T[9]);
    ++T[u]; ++T[v];
  }
  return dp[i1][i2][i3][i4][i5][i6][i7][i8][i9] = ans;
}

void solve() {
  for (int i = 1; i <= 9; ++i) {
    for (int j = 1; j <= 4; ++j) cin >> S[i][j];
  }

  for (int i1 = 0; i1 < 5; ++i1) for (int i2 = 0; i2 < 5; ++i2) for (int i3 = 0; i3 < 5; ++i3)
  for (int i4 = 0; i4 < 5; ++i4) for (int i5 = 0; i5 < 5; ++i5) for (int i6 = 0; i6 < 5; ++i6)
  for (int i7 = 0; i7 < 5; ++i7) for (int i8 = 0; i8 < 5; ++i8) for (int i9 = 0; i9 < 5; ++i9) {
    dp[i1][i2][i3][i4][i5][i6][i7][i8][i9] = -1;
  }

  cout << fixed << setprecision(9) << rec(4, 4, 4, 4, 4, 4, 4, 4, 4) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
