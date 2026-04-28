#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 20;
const int dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};
char board[MAXN + 1][MAXN + 1];
int vis[MAXN][MAXN], N, M;

void print_line_decor() {
  for (int j = 0; j < M; ++j) cout << "+---";
  cout << "+\n";
}

void print_board() {
  for (int i = 0; i < N; ++i) {
    print_line_decor();
    for (int j = 0; j < M; ++j) {
      cout << "|";
      if (board[i][j] == 'X') cout << " X ";
      else if (vis[i][j]) cout << " M ";
      else cout << "   ";
    }
    cout << "|\n";
  }
  print_line_decor();
}

int tc;
void solve() {
  cout << "Case: " << ++tc << '\n';

  cin >> N >> M;
  for (int i = 0; i < N; ++i) cin >> board[i];

  memset(vis, 0, sizeof(vis)); queue<pii> q;
  if (board[0][0] == 'O') q.push({0, 0}), vis[0][0] = 1;
  while (!q.empty()) {
    auto [x, y] = q.front(); q.pop();
    for (int d = 0; d < 4; ++d) {
      int nx = x + dx[d], ny = y + dy[d];
      if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue;
      if (board[nx][ny] == 'X' || vis[nx][ny]) continue;
      vis[nx][ny] = 1; q.push({nx, ny});
    }
  }

  print_board(); int ok = vis[N - 1][M - 1];
  cout << "Minions can" << (ok ? "" : "not") << " cross the room\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
