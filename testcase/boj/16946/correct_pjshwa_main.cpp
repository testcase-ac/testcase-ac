#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e3;
int n, m;
int board[MAX][MAX], ccnt[MAX * MAX];
int vis[MAX][MAX];

void dfs(int i, int j, int cc) {
  vis[i][j] = cc;
  ccnt[cc]++;

  if (i > 0 && !vis[i - 1][j] && board[i - 1][j] == 1) dfs(i - 1, j, cc);
  if (j > 0 && !vis[i][j - 1] && board[i][j - 1] == 1) dfs(i, j - 1, cc);
  if (i < n - 1 && !vis[i + 1][j] && board[i + 1][j] == 1) dfs(i + 1, j, cc);
  if (j < m - 1 && !vis[i][j + 1] && board[i][j + 1] == 1) dfs(i, j + 1, cc);
}

int main() {
  fast_io();

  cin >> n >> m;
  for (int i = 0; i < n; i++) {
    string s;
    cin >> s;
    for (int j = 0; j < m; j++) board[i][j] = s[j] == '0';
  }

  int cc = 0;
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
    if (board[i][j] == 1 && !vis[i][j]) dfs(i, j, ++cc);
  }

  int mv = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (board[i][j] == 0) {
        set<int> s;
        if (i > 0 && board[i - 1][j] == 1) s.insert(vis[i - 1][j]);
        if (j > 0 && board[i][j - 1] == 1) s.insert(vis[i][j - 1]);
        if (i < n - 1 && board[i + 1][j] == 1) s.insert(vis[i + 1][j]);
        if (j < m - 1 && board[i][j + 1] == 1) s.insert(vis[i][j + 1]);

        int r = 1;
        for (int it : s) r += ccnt[it];
        cout << (r % 10);
      }
      else cout << 0;
    }
    cout << '\n';
  }
}
