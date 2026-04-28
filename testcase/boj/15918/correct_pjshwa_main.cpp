#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
 
void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int vis[25], visv[13], cnt, n, ans = 0;
void dfs(int i) {
  if (i == 2 * n + 1) {
    if (cnt == n) ans++;
    return;
  }

  if (vis[i] == 0) {
    for (int d = 1; d <= n; d++) {
      int j = i + d + 1;
      if (j > 2 * n) break;
      if (visv[d] || vis[j]) continue;

      vis[i] = vis[j] = d; visv[d] = 1; cnt++;
      dfs(i + 1);
      vis[i] = vis[j] = 0; visv[d] = 0; cnt--;
    }
  }
  else dfs(i + 1);
}

void solve() {
  int x, y;
  cin >> n >> x >> y;

  int d = y - x - 1;
  vis[x] = vis[y] = d; visv[d] = 1;
  cnt++;
  dfs(1);

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
