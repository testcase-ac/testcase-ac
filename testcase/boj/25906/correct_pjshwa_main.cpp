#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 50;
int Z[3], C[3][MAX + 1], V[3][MAX + 1][5];
vector<int> A[5];

void solve() {
  int T, K; cin >> T >> K;
  for (int i = 0; i < 5; i++) {
    int L; cin >> L;
    A[i].resize(L);
    for (int& x : A[i]) cin >> x;
  }
  for (int i = 0; i < 3; i++) {
    cin >> Z[i];
    for (int j = 1; j <= Z[i]; j++) cin >> C[i][j];
    for (int j = 1; j <= Z[i]; j++) for (int k = 0; k < 5; k++) cin >> V[i][j][k];
  }

  ll ans = 0;
  for (int i = 0; i <= Z[0]; i++) for (int j = 0; j <= Z[1]; j++) for (int k = 0; k <= Z[2]; k++) {
    int cost = C[0][i] + C[1][j] + C[2][k];
    if (cost > T) continue;

    int acc[5]{};
    for (int l = 0; l < 5; l++) {
      acc[l] += V[0][i][l];
      acc[l] += V[1][j][l];
      acc[l] += V[2][k][l];
    }

    // cout << "i = " << i << ", j = " << j << ", k = " << k << '\n';
    // for (int l = 0; l < 5; l++) cout << acc[l] << ' '; cout << endl;

    ll cur = 0;
    for (int l = 0; l < 5; l++) {
      int lev = min(acc[l], (int)A[l].size());
      if (lev) cur += A[l][lev - 1];
    }
    ans = max(ans, cur);

    if (cost + K > T) continue;
    for (int l = 0; l < 5; l++) {
      if (acc[l] == 0) continue;
      for (int m = 0; m < 5; m++) {
        if (l == m) continue;

        acc[l]--; acc[m]++; ll cur = 0;
        for (int o = 0; o < 5; o++) {
          int lev = min(acc[o], (int)A[o].size());
          if (lev) cur += A[o][lev - 1];
        }
        ans = max(ans, cur);
        acc[l]++; acc[m]--;
      }
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
