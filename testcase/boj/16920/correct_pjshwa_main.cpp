#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000;
const int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};
char board[MAX + 1][MAX + 1];
int S[MAX];
queue<tii> q[9];

void solve() {
  int N, M, P;
  cin >> N >> M >> P;
  for (int i = 0; i < P; i++) cin >> S[i];
  for (int i = 0; i < N; i++) cin >> board[i];

  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) {
    if ('1' <= board[i][j] && board[i][j] <= '9') {
      int x = board[i][j] - '1';
      q[x].push({i, j, 0});
    }
  }

  while (1) {
    bool f = false;
    for (int t = 0; t < 9; t++) {
      if (q[t].empty()) continue;

      f = true;
      queue<tii> nq;
      while (!q[t].empty()) {
        auto [i, j, c] = q[t].front();
        q[t].pop();

        if (c == S[t]) {
          nq.push({i, j, 0});
          continue;
        }

        for (int k = 0; k < 4; k++) {
          int nx = i + dx[k], ny = j + dy[k];
          if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue;
          if (board[nx][ny] != '.') continue;

          board[nx][ny] = t + '1';
          q[t].push({nx, ny, c + 1});
        }
      }
      swap(q[t], nq);
    }

    if (!f) break;
  }

  int C[9] = {0};
  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) {
    if ('1' <= board[i][j] && board[i][j] <= '9') {
      int x = board[i][j] - '1';
      C[x]++;
    }
  }

  for (int i = 0; i < P; i++) cout << C[i] << ' ';
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
