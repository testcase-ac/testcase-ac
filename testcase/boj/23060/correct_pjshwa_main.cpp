#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 500;
int n, board[MAX + 1][MAX + 1];
bool vis[MAX + 1][MAX + 1];
vector<pair<int, int>> moves;

void dfs(int i, int j) {
  vis[i][j] = true;
  moves.push_back({i, j});

  if (i - 1 >= 1 && j - 2 >= 1 && !vis[i - 1][j - 2]) dfs(i - 1, j - 2), moves.push_back({i, j});
  if (i - 2 >= 1 && j - 1 >= 1 && !vis[i - 2][j - 1]) dfs(i - 2, j - 1), moves.push_back({i, j});
  if (i - 2 >= 1 && j + 1 <= n && !vis[i - 2][j + 1]) dfs(i - 2, j + 1), moves.push_back({i, j});
  if (i - 1 >= 1 && j + 2 <= n && !vis[i - 1][j + 2]) dfs(i - 1, j + 2), moves.push_back({i, j});
  if (i + 1 <= n && j + 2 <= n && !vis[i + 1][j + 2]) dfs(i + 1, j + 2), moves.push_back({i, j});
  if (i + 2 <= n && j + 1 <= n && !vis[i + 2][j + 1]) dfs(i + 2, j + 1), moves.push_back({i, j});
  if (i + 2 <= n && j - 1 >= 1 && !vis[i + 2][j - 1]) dfs(i + 2, j - 1), moves.push_back({i, j});
  if (i + 1 <= n && j - 2 >= 1 && !vis[i + 1][j - 2]) dfs(i + 1, j - 2), moves.push_back({i, j});
}

int main() {
  fast_io();

  int cr, cc;
  cin >> n >> cr >> cc;
  dfs(cr, cc);

  bool able = true;
  for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) {
    able &= vis[i][j];
  }

  if (able) {
    cout << moves.size() << '\n';
    for (auto [i, j] : moves) cout << i << ' ' << j << '\n';
  }
  else cout << "-1\n";
}
