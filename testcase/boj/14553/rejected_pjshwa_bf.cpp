#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000;
const int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};
bool vis[3][MAX];
int n, cnt;

void dfs(int i, int j) {
  if (i == 2 && j == n - 1) return cnt++, void();

  vis[i][j] = true;
  for (int k = 0; k < 4; k++) {
    int ni = i + dx[k], nj = j + dy[k];
    if (ni < 0 || ni >= 3 || nj < 0 || nj >= n || vis[ni][nj]) continue;
    dfs(ni, nj);
  }
  vis[i][j] = false;
}

void solve() {
  cin >> n;
  dfs(0, 0);
  cout << cnt << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
