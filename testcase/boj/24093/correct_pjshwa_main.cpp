#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 400;
int A[MAX + 1][MAX + 1];

void solve() {
  int N, M;
  cin >> N >> M;
  for (int i = 1; i <= N; i++) for (int j = 1; j <= M; j++) cin >> A[i][j];

  ll ans = 0;
  for (int si = 1; si <= N; si++) for (int ei = si + 1; ei <= N; ei++) {
    int t[9] = {0};
    for (int j = 1; j <= M; j++) {
      int rx = A[si][j], ry = A[ei][j];
      if (rx == ry) {
        for (int k = 0; k < 9; k++) {
          int lx = k / 3, ly = k % 3;
          if (lx != ly && lx != rx && ly != rx) ans += t[k];
        }
      }
      else {
        for (int k = 0; k < 9; k++) {
          int lx = k / 3, ly = k % 3;
          if ((lx != rx && lx != ry) || (ly != rx && ly != ry)) ans += t[k];
        }
      }

      t[rx * 3 + ry]++;
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
