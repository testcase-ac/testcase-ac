#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int d[1 << 17][17];
int w[17][17];
const int MAX = 1e9;
int main() {
  fast_io();

  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) cin >> w[i][j];
  }

  for (int i = 0; i < (1 << n); i++) {
    for (int j = 0; j < n; j++) d[i][j] = MAX;
  }

  d[1][0] = 0;
  for (int i = 0; i < (1 << n); i++) {
    for (int j = 0; j < n; j++) {
      if (i & (1 << j)) {
        for (int k = 0; k < n; k++) {
          if (
            k != j &&
            !(i & (1 << k)) &&
            w[j][k]
          ) d[i | (1 << k)][k] = min(d[i | (1 << k)][k], d[i][j] + w[j][k]);
        }
      }
    }
  }

  int ans = MAX;
  for (int i = 1; i < n; i++) {
    if (w[i][0]) ans = min(ans, d[(1 << n) - 1][i] + w[i][0]);
  }
  cout << ans << '\n';
}
