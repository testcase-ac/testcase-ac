#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int ans = 0;
bool vis[25][25];
int n, m;

void dfs(int i, int j) {
  if (i == n && j == 0) {
    ans++;
    return;
  }

  j == m - 1 ? dfs(i + 1, 0) : dfs(i, j + 1);
  if (i > 0 && j > 0 && vis[i - 1][j] && vis[i][j - 1] && vis[i - 1][j - 1]) {
    // No
  }
  else {
    vis[i][j] = true;
    j == m - 1 ? dfs(i + 1, 0) : dfs(i, j + 1);
    vis[i][j] = false;
  }
}

int main() {
  fast_io();

  cin >> n >> m;
  dfs(0, 0);
  cout << ans;
}
