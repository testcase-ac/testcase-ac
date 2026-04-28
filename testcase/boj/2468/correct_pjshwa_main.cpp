#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int n;
int board[100][100];
bool vis[100][100];

void dfs(int x, int y, int wf) {
  vis[x][y] = true;

  if (x > 0 && !vis[x - 1][y] && board[x - 1][y] > wf) dfs(x - 1, y, wf);
  if (y > 0 && !vis[x][y - 1] && board[x][y - 1] > wf) dfs(x, y - 1, wf);
  if (x < n - 1 && !vis[x + 1][y] && board[x + 1][y] > wf) dfs(x + 1, y, wf);
  if (y < n - 1 && !vis[x][y + 1] && board[x][y + 1] > wf) dfs(x, y + 1, wf);
}

int main() {
  fast_io();

  cin >> n;
  int minv = 1e9, maxv = -1;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> board[i][j];
      minv = min(minv, board[i][j]);
      maxv = max(maxv, board[i][j]);
    }
  }

  int mxcnt = -1, cnt;
  for (int wf = minv - 1; wf <= maxv; wf++) {
    cnt = 0;
    memset(vis, false, sizeof(vis));

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (!vis[i][j] && board[i][j] > wf) {
          cnt++;
          dfs(i, j, wf);
        }
      }
    }

    mxcnt = max(mxcnt, cnt);
  }

  cout << mxcnt << '\n';
}
