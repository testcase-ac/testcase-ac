#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int n, m;
int oboard[30][30], nboard[30][30];
bool vis[30][30];

bool compare_board() {
  bool same = true;
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
    same &= oboard[i][j] == nboard[i][j];
  }
  return same;
}

void dfs(int i, int j, int s, int t) {
  vis[i][j] = true;
  oboard[i][j] = t;
  if (i > 0 && !vis[i - 1][j] && oboard[i - 1][j] == s) dfs(i - 1, j, s, t);
  if (i < n - 1 && !vis[i + 1][j] && oboard[i + 1][j] == s) dfs(i + 1, j, s, t);
  if (j > 0 && !vis[i][j - 1] && oboard[i][j - 1] == s) dfs(i, j - 1, s, t);
  if (j < m - 1 && !vis[i][j + 1] && oboard[i][j + 1] == s) dfs(i, j + 1, s, t);
}

int main() {
  fast_io();

  cin >> n >> m;
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) cin >> oboard[i][j];
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) cin >> nboard[i][j];

  // already identical
  if (compare_board()) cout << "YES";
  else {
    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
      if (oboard[i][j] != nboard[i][j]) {
        dfs(i, j, oboard[i][j], nboard[i][j]);
        if (compare_board()) cout << "YES";
        else cout << "NO";
        return 0;
      }
    }
  }
}
