#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 20;
int f[MAX], p[MAX];
int n, ans, tflow, tprc;
int t, v;

void dfs(int i) {
  if (i == n) {
    if (tflow * v >= t) {
      if (ans == -1) ans = tprc;
      else ans = min(ans, tprc);
    }
    return;
  }

  dfs(i + 1);
  tflow += f[i];
  tprc += p[i];
  dfs(i + 1);
  tflow -= f[i];
  tprc -= p[i];
}

int main() {
  fast_io();

  cin >> n;
  for (int i = 0; i < n; i++) cin >> f[i] >> p[i];

  int m;
  cin >> m;
  for (int i = 1; i <= m; i++) {
    cin >> t >> v;
    ans = -1;
    dfs(0);
    if (ans == -1) cout << "Case " << i << ": IMPOSSIBLE" << '\n';
    else cout << "Case " << i << ": " << ans << '\n';
  }
}
