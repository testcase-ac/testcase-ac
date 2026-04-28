#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 5, INF = 0x3f3f3f3f;
const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};
int A[5][5], vis[5][5];
int ans = INF;

void dfs(int i, int j, int mov, int cnt) {
  if (cnt == 3) ans = min(ans, mov);
  else {
    for (int k = 0; k < 4; ++k) {
      int ni = i + dx[k], nj = j + dy[k];
      if (ni < 0 || ni >= MAXN || nj < 0 || nj >= MAXN || vis[ni][nj]) continue;
      if (A[ni][nj] == -1) continue;

      vis[ni][nj] = 1;
      dfs(ni, nj, mov + 1, cnt + (A[ni][nj] == 1));
      vis[ni][nj] = 0;
    }
  }
}

void solve() {
  for (int i = 0; i < MAXN; ++i) for (int j = 0; j < MAXN; ++j) cin >> A[i][j];
  int r, c; cin >> r >> c;

  vis[r][c] = 1;
  dfs(r, c, 0, 0);
  if (ans == INF) cout << "-1\n";
  else cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
