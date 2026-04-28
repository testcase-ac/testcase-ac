#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int INF = 0x3f3f3f3f;
string S[6];
int dp[10][10][10][10][10][10], Z[6];

int r(int i1, int i2, int i3, int i4, int i5, int i6) {
  if (dp[i1][i2][i3][i4][i5][i6] != -1) return dp[i1][i2][i3][i4][i5][i6];

  if (
    i1 == Z[0] &&
    i2 == Z[1] &&
    i3 == Z[2] &&
    i4 == Z[3] &&
    i5 == Z[4] &&
    i6 == Z[5]
  ) return dp[i1][i2][i3][i4][i5][i6] = 0;

  int ret = INF;
  for (char c : {'A', 'B', 'C', 'D'}) {
    int ni1 = i1, ni2 = i2, ni3 = i3, ni4 = i4, ni5 = i5, ni6 = i6;
    if (i1 < Z[0] && S[0][i1] == c) ni1++;
    if (i2 < Z[1] && S[1][i2] == c) ni2++;
    if (i3 < Z[2] && S[2][i3] == c) ni3++;
    if (i4 < Z[3] && S[3][i4] == c) ni4++;
    if (i5 < Z[4] && S[4][i5] == c) ni5++;
    if (i6 < Z[5] && S[5][i6] == c) ni6++;

    if (ni1 == i1 && ni2 == i2 && ni3 == i3 && ni4 == i4 && ni5 == i5 && ni6 == i6) continue;
    ret = min(ret, r(ni1, ni2, ni3, ni4, ni5, ni6) + 1);
  }

  return dp[i1][i2][i3][i4][i5][i6] = ret;
}

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; i++) cin >> S[i], Z[i] = S[i].size();

  memset(dp, -1, sizeof(dp));
  int sz = r(0, 0, 0, 0, 0, 0);

  int i1 = 0, i2 = 0, i3 = 0, i4 = 0, i5 = 0, i6 = 0;
  for (int i = 0; i < sz; i++) {
    int ov = dp[i1][i2][i3][i4][i5][i6];

    for (char c : {'A', 'B', 'C', 'D'}) {
      int ni1 = i1, ni2 = i2, ni3 = i3, ni4 = i4, ni5 = i5, ni6 = i6;
      if (i1 < Z[0] && S[0][i1] == c) ni1++;
      if (i2 < Z[1] && S[1][i2] == c) ni2++;
      if (i3 < Z[2] && S[2][i3] == c) ni3++;
      if (i4 < Z[3] && S[3][i4] == c) ni4++;
      if (i5 < Z[4] && S[4][i5] == c) ni5++;
      if (i6 < Z[5] && S[5][i6] == c) ni6++;

      int nv = dp[ni1][ni2][ni3][ni4][ni5][ni6];
      if (nv == ov - 1) {
        cout << c;
        i1 = ni1, i2 = ni2, i3 = ni3, i4 = ni4, i5 = ni5, i6 = ni6;
        break;
      }
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
