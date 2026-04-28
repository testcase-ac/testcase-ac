#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 500;
int b[MAX][MAX];
bool vis[MAX][MAX];
int n;

int dfs(int i, int j, int d) {
  vis[i][j] = true;

  int c = b[i][j], ans = 1;
  if (i > 0 && !vis[i - 1][j] && abs(b[i - 1][j] - c) <= d) ans += dfs(i - 1, j, d);
  if (j > 0 && !vis[i][j - 1] && abs(b[i][j - 1] - c) <= d) ans += dfs(i, j - 1, d);
  if (i < n - 1 && !vis[i + 1][j] && abs(b[i + 1][j] - c) <= d) ans += dfs(i + 1, j, d);
  if (j < n - 1 && !vis[i][j + 1] && abs(b[i][j + 1] - c) <= d) ans += dfs(i, j + 1, d);

  return ans;
}

bool do_search(int d) {
  memset(vis, 0, sizeof(vis));
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
    if (vis[i][j]) continue;
    if (dfs(i, j, d) * 2 >= n * n) return true;
  }
  return false;
}

int main() {
  fast_io();

  cin >> n;
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) cin >> b[i][j];

  int left = 0, right = 1e6;
  int mid = (left + right) / 2;
  while (left < right) {
    if (do_search(mid)) right = mid;
    else left = mid + 1;
    mid = (left + right) / 2;
  }

  cout << mid << '\n';
}
