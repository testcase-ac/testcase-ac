#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int cost[12][12];
bool vis[6];
int ans = 0x3f3f3f3f;

void dfs(int p, int cur, int acc) {
  if (cur == 0) {
    ans = min(ans, acc);
    return;
  }

  if (cur & 1) {
    if (p & 1) dfs(p - 1, cur - 1, acc + cost[p][p - 1]);
    else dfs(p + 1, cur - 1, acc + cost[p][p + 1]);
  }
  else {
    for (int g = 0; g < 6; g++) {
      if (vis[g]) continue;

      vis[g] = 1;

      dfs(2 * g, cur - 1, acc + cost[p][2 * g]);
      dfs(2 * g + 1, cur - 1, acc + cost[p][2 * g + 1]);

      vis[g] = 0;
    }
  }
}

void solve() {
  for (int i = 0; i < 12; ++i) {
    for (int j = 0; j < 12; ++j) {
      cin >> cost[i][j];
    }
  }

  for (int g = 0; g < 6; g++) {
    vis[g] = 1;

    dfs(2 * g, 11, 0);
    dfs(2 * g + 1, 11, 0);

    vis[g] = 0;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
