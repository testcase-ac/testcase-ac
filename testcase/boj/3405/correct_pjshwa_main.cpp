#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1 << 20;
bool vis[MAX];
int cost[20][20], n;

void dfs(int state) {
  vis[state] = true;
  for (int i = 0; i < n; i++) {
    if (state & (1 << i)) {
      int icost = 0;
      for (int j = 0; j < n; j++) if (state & (1 << j)) icost += cost[i][j];
      if (icost > 0 && !vis[state ^ (1 << i)]) dfs(state ^ (1 << i));
    }
  }
}

void solve() {
  cin >> n;
  memset(vis, 0, sizeof(vis));
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) cin >> cost[i][j];
  dfs((1 << n) - 1);

  bool able = false;
  for (int i = 0; i < n; i++) if (vis[1 << i]) able = true, cout << i + 1 << ' ';
  if (!able) cout << 0;
  cout << '\n';
}

int main() {
  fast_io();

  int t;
  cin >> t;
  while (t--) solve();
}
