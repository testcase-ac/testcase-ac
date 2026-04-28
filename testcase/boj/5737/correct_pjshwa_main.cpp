#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 100;
const int dx[6] = {-1, -1, 0, 0, 1, 1}, dy[6] = {0, 1, -1, 1, -1, 0};
char board[MAX + 1][MAX + 1];
bool vis[MAX][MAX][2];
int N, M;

void dfs(int i, int j, int m) {
  vis[i][j][m] = true;
  for (int k = 0; k < 6; k++) {
    int ni = i + dx[k], nj = j + dy[k];
    if (ni < 0 || ni >= N || nj < 0 || nj >= M) continue;
    if (board[ni][nj] == '.') continue;
    if (vis[ni][nj][1 - m]) continue;
    dfs(ni, nj, 1 - m);
  }
}

void solve() {
  for (int i = 0; i < N; i++) cin >> board[i];

  memset(vis, 0, sizeof(vis));
  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) {
    if (board[i][j] != 'I') continue;
    if (vis[i][j][0]) continue;
    dfs(i, j, 0);
  }

  cout << '\n';
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      if (board[i][j] == '.') {
        cout << '.';
        continue;
      }

      if (vis[i][j][0] && vis[i][j][1]) cout << 'B';
      else if (vis[i][j][0]) cout << '(';
      else if (vis[i][j][1]) cout << ')';
      else cout << 'F';
    }

    cout << '\n';
  }
}

int main() {
  fast_io();

  while (1) {
    cin >> N >> M;
    if (N == 0 && M == 0) break;
    solve();
  }
}
