#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int n;
int board[6][6];
char ops[6][6];

int cal(int v1, char op, int v2) {
  if (op == '+') return v1 + v2;
  if (op == '-') return v1 - v2;
  if (op == '*') return v1 * v2;
}

pii bfs(pii sv) {
  queue<pair<pii, int>> q;
  q.push({sv, board[sv.first][sv.second]});

  int mx = -1e9, mn = 1e9;
  while (!q.empty()) {
    auto[vtx, acc] = q.front();
    auto[i, j] = vtx;
    q.pop();

    if (vtx.first == n && vtx.second == n) {
      mx = max(mx, acc);
      mn = min(mn, acc);
    }

    if (j + 2 <= n) q.push({{i, j + 2}, cal(acc, ops[i][j + 1], board[i][j + 2])});
    if (i + 2 <= n) q.push({{i + 2, j}, cal(acc, ops[i + 1][j], board[i + 2][j])});
    if (j + 1 <= n && i + 1 <= n) {
      q.push({{i + 1, j + 1}, cal(acc, ops[i][j + 1], board[i + 1][j + 1])});
      q.push({{i + 1, j + 1}, cal(acc, ops[i + 1][j], board[i + 1][j + 1])});
    }
  }

  return {mx, mn};
}

int main() {
  fast_io();

  cin >> n;

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if ((i + j) & 1) cin >> ops[i][j];
      else cin >> board[i][j];
    }
  }

  pii ans = bfs({1, 1});
  cout << ans.first << ' ' << ans.second << '\n';
}
