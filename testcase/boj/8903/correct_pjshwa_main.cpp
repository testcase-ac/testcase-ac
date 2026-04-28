#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e4;
int a[MAX + 1][5], n, k, g[5], ans;

void dfs(int i) {
  if (i == 5) {
    int tot[5] = {0};

    for (int j = 0; j < k; j++) {
      int mask = 0;
      for (int u = 0; u < 5; u++) {
        if (g[u] == j) mask |= 1 << u;
      }

      int mi = -1, mval = 0;
      for (int i = 1; i <= n; i++) {
        int cval = 0;
        for (int j = 0; j < 5; j++) if (mask & (1 << j)) cval += a[i][j];
        if (cval > mval) {
          mval = cval;
          mi = i;
        }
      }

      if (mi == -1) continue;
      for (int j = 0; j < 5; j++) tot[j] = max(tot[j], a[mi][j]);
    }

    ans = max(ans, accumulate(tot, tot + 5, 0));
    return;
  }

  for (int j = 0; j < k; j++) {
    g[i] = j;
    dfs(i + 1);
  }
}

void solve() {
  cin >> n >> k;
  for (int i = 1; i <= n; i++) for (int j = 0; j < 5; j++) cin >> a[i][j];
  ans = 0;

  if (k >= 5) {
    for (int j = 0; j < 5; j++) {
      int cur = 0;
      for (int i = 1; i <= n; i++) cur = max(cur, a[i][j]);
      ans += cur;
    }
  }
  else dfs(0);

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
