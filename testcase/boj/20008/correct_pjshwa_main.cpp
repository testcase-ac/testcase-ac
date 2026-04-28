#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 5;
int wait[MAX], damage[MAX];

void solve() {
  int n, h;
  cin >> n >> h;
  for (int i = 0; i < n; i++) cin >> wait[i] >> damage[i];

  int ans = 1e9;
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) for (int k = 0; k < n; k++)
  for (int l = 0; l < n; l++) for (int m = 0; m < n; m++) for (int o = 0; o < n; o++)
  for (int p = 0; p < n; p++) for (int q = 0; q < n; q++) for (int r = 0; r < n; r++)
  for (int s = 0; s < n; s++) {
    int ord[10] = {i, j, k, l, m, o, p, q, r, s}, last[10];
    for (int u = 0; u < 10; u++) last[u] = -1e9;

    int ch = h, ctime = 0;
    for (int u = 0; u < 10; u++) {
      int sk = ord[u], luse = last[sk];
      ctime = max(ctime, luse + wait[sk]) + 1;
      last[sk] = ctime - 1;
      ch -= damage[sk];
      if (ch <= 0) {
        ans = min(ans, ctime);
        break;
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
