#include <bits/stdc++.h> 
using namespace std;

bool vis[50][50], grid[50][50];

void dfs(int i, int j, int w, int h) {
  vis[i][j] = true;

  if (j > 0 && !vis[i][j - 1] && grid[i][j - 1] == 1) dfs(i, j - 1, w, h);
  if (i > 0 && !vis[i - 1][j] && grid[i - 1][j] == 1) dfs(i - 1, j, w, h);
  if (j < w - 1 && !vis[i][j + 1] && grid[i][j + 1] == 1) dfs(i, j + 1, w, h);
  if (i < h - 1 && !vis[i + 1][j] && grid[i + 1][j] == 1) dfs(i + 1, j, w, h);

  if (j > 0 && i > 0 && !vis[i - 1][j - 1] && grid[i - 1][j - 1] == 1) dfs(i - 1, j - 1, w, h);
  if (j > 0 && i < h - 1 && !vis[i + 1][j - 1] && grid[i + 1][j - 1] == 1) dfs(i + 1, j - 1, w, h);
  if (j < w - 1 && i > 0 && !vis[i - 1][j + 1] && grid[i - 1][j + 1] == 1) dfs(i - 1, j + 1, w, h);
  if (j < w - 1 && i < h - 1 && !vis[i + 1][j + 1] && grid[i + 1][j + 1] == 1) dfs(i + 1, j + 1, w, h);
}

void FastIO() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main() {
  FastIO();

  int w, h, island_no;

  while (1) {
    cin >> w >> h;
    if (w == 0 && h == 0) break;

    memset(vis, false, sizeof(vis));

    for (int i = 0; i < h; i++) {
      for (int j = 0; j < w; j++) {
        cin >> grid[i][j];
      }
    }

    island_no = 0;
    for (int i = 0; i < h; i++) {
      for (int j = 0; j < w; j++) {
        if (!vis[i][j] && grid[i][j] == 1) {
          island_no++;
          dfs(i, j, w, h);
        }
      }
    }
  
    cout << island_no << '\n';
  }
}
