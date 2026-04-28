#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 20;
bool vis[MAX];
int board[MAX][MAX];
int n, mans = 1e9;

void dfs(int idx, int cnt) {
  if (cnt == n / 2) {
    int as = 0, bs = 0;
    for (int i = 0; i < n; ++i) for (int j = i + 1; j < n; ++j) {
      if (vis[i] && vis[j]) as += (board[i][j] + board[j][i]);
      else if (!vis[i] && !vis[j]) bs += (board[i][j] + board[j][i]);
    }
    mans = min(mans, abs(as - bs));
    return;
  }
  else if (idx == n) return;

  dfs(idx + 1, cnt);
  vis[idx] = true;
  dfs(idx + 1, cnt + 1);
  vis[idx] = false;
}

int main() {
  fast_io();

  cin >> n;
  for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) cin >> board[i][j];
  dfs(0, 0);
  cout << mans << '\n';
}
