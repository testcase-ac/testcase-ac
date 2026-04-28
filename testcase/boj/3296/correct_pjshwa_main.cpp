#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 50;
const int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};
char board[MAX + 1][MAX + 1];
bool vis[1001][MAX + 1][MAX + 1];

void solve() {
  int N, M, si, sj;
  cin >> N >> M;
  for (int i = 0; i < N; i++) cin >> board[i];
  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) {
    if (board[i][j] == '*') si = i, sj = j;
  }

  int R;
  cin >> R;
  vector<string> D(R);
  for (int i = 0; i < R; i++) cin >> D[i];

  queue<tii> q;
  q.push({0, si, sj});
  vis[0][si][sj] = true;

  while (!q.empty()) {
    auto [r, i, j] = q.front(); q.pop();
    if (r == R) continue;

    if (D[r] == "NORTH") {
      int ni = i + dx[0], nj = j + dy[0];
      while (ni >= 0 && ni < N && nj >= 0 && nj < M && board[ni][nj] != 'X') {
        if (!vis[r + 1][ni][nj]) {
          q.push({r + 1, ni, nj});
          vis[r + 1][ni][nj] = true;
        }
        ni += dx[0], nj += dy[0];
      }
    }
    if (D[r] == "SOUTH") {
      int ni = i + dx[1], nj = j + dy[1];
      while (ni >= 0 && ni < N && nj >= 0 && nj < M && board[ni][nj] != 'X') {
        if (!vis[r + 1][ni][nj]) {
          q.push({r + 1, ni, nj});
          vis[r + 1][ni][nj] = true;
        }
        ni += dx[1], nj += dy[1];
      }
    }
    if (D[r] == "WEST") {
      int ni = i + dx[2], nj = j + dy[2];
      while (ni >= 0 && ni < N && nj >= 0 && nj < M && board[ni][nj] != 'X') {
        if (!vis[r + 1][ni][nj]) {
          q.push({r + 1, ni, nj});
          vis[r + 1][ni][nj] = true;
        }
        ni += dx[2], nj += dy[2];
      }
    }
    if (D[r] == "EAST") {
      int ni = i + dx[3], nj = j + dy[3];
      while (ni >= 0 && ni < N && nj >= 0 && nj < M && board[ni][nj] != 'X') {
        if (!vis[r + 1][ni][nj]) {
          q.push({r + 1, ni, nj});
          vis[r + 1][ni][nj] = true;
        }
        ni += dx[3], nj += dy[3];
      }
    }
  }

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      if (vis[R][i][j]) cout << '*';
      else if (board[i][j] == 'X') cout << 'X';
      else cout << '.';
    }
    cout << '\n';
  }

  
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
