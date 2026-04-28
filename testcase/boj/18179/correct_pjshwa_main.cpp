#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  string S, T;
  cin >> S >> T;
  int n = S.size();

  int t[4][4] = {0};
  for (int i = 0; i < n; i++) {
    int si, ti;

    if (S[i] == 'A') si = 0;
    if (S[i] == 'T') si = 1;
    if (S[i] == 'C') si = 2;
    if (S[i] == 'G') si = 3;

    if (T[i] == 'A') ti = 0;
    if (T[i] == 'T') ti = 1;
    if (T[i] == 'C') ti = 2;
    if (T[i] == 'G') ti = 3;

    t[si][ti]++;
  }

  int ans = 0;

  while (t[0][1] && t[1][0]) t[0][1]--, t[1][0]--, ans++;
  while (t[0][2] && t[2][0]) t[0][2]--, t[2][0]--, ans++;
  while (t[0][3] && t[3][0]) t[0][3]--, t[3][0]--, ans++;
  while (t[1][2] && t[2][1]) t[1][2]--, t[2][1]--, ans++;
  while (t[1][3] && t[3][1]) t[1][3]--, t[3][1]--, ans++;
  while (t[2][3] && t[3][2]) t[2][3]--, t[3][2]--, ans++;

  while (t[0][1] && t[1][2] && t[2][0]) t[0][1]--, t[1][2]--, t[2][0]--, ans += 2;
  while (t[0][2] && t[2][1] && t[1][0]) t[0][2]--, t[2][1]--, t[1][0]--, ans += 2;
  while (t[0][1] && t[1][3] && t[3][0]) t[0][1]--, t[1][3]--, t[3][0]--, ans += 2;
  while (t[0][3] && t[3][1] && t[1][0]) t[0][3]--, t[3][1]--, t[1][0]--, ans += 2;
  while (t[0][2] && t[2][3] && t[3][0]) t[0][2]--, t[2][3]--, t[3][0]--, ans += 2;
  while (t[0][3] && t[3][2] && t[2][0]) t[0][3]--, t[3][2]--, t[2][0]--, ans += 2;
  while (t[1][2] && t[2][3] && t[3][1]) t[1][2]--, t[2][3]--, t[3][1]--, ans += 2;
  while (t[1][3] && t[3][2] && t[2][1]) t[1][3]--, t[3][2]--, t[2][1]--, ans += 2;

  int rest = 0;
  for (int i = 0; i < 4; i++) t[i][i] = 0;
  for (int i = 0; i < 4; i++) for (int j = 0; j < 4; j++) rest += t[i][j];
  cout << ans + 3 * rest / 4 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
