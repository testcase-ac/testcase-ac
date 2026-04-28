#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 500;
const int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
int a[MAX][MAX], w[MAX][MAX];
int n;

int dfs(int i, int j) {
  if (w[i][j] != -1) return w[i][j];

  int res = 0;
  for (int k = 0; k < 4; k++) {
    int nx = i + dx[k], ny = j + dy[k];
    if (nx < 0 || ny < 0 || nx >= n || ny >= n) continue;
    if (a[nx][ny] >= a[i][j]) continue;

    res = max(res, dfs(nx, ny));
  }

  return w[i][j] = res + 1;
}

void solve() {
  cin >> n;

  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) cin >> a[i][j];
  memset(w, -1, sizeof w);

  int ans = 0;
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
    if (w[i][j] != -1) continue;
    ans = max(ans, dfs(i, j));
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
