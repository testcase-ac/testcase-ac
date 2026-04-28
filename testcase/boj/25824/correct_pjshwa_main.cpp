#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int cost[12][12];
int ans = 0x3f3f3f3f;

void dfs(int i, int p, int cur) {
  int g = i / 2;
  if (g == 5 && p == 0) {
    ans = min(ans, cur);
    return;
  }

  if (p) {
    if (i & 1) dfs(i - 1, 0, cur + cost[i][i - 1]);
    else dfs(i + 1, 0, cur + cost[i][i + 1]);
  }
  else {
    dfs(2 * (g + 1), 1, cur + cost[i][2 * (g + 1)]);
    dfs(2 * (g + 1) + 1, 1, cur + cost[i][2 * (g + 1) + 1]);
  }
}

void solve() {
  for (int i = 0; i < 12; ++i) {
    for (int j = 0; j < 12; ++j) {
      cin >> cost[i][j];
    }
  }

  dfs(0, 1, 0);
  dfs(1, 1, 0);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
