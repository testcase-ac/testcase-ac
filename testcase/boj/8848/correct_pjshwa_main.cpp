#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1000;
const int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};
int adj[MAX + 1][4], board[MAX + 1][MAX + 1];

void solve() {
  int N, M; cin >> N >> M;
  for (int i = 1; i <= N * M; i++) {
    for (int j = 0; j < 4; j++) cin >> adj[i][j];
  }
  cin >> board[0][0] >> board[0][1];
  
  int j = 0;
  for (int i = 0; i < N - 1; i++) {
    int x = board[i][j];

    set<int> pre;
    for (int k = 0; k < 4; k++) {
      if (adj[x][k]) pre.insert(adj[x][k]);
    }

    for (int k = 0; k < 4; k++) {
      int ni = i + dx[k], nj = j + dy[k];
      if (ni < 0 || ni >= N || nj < 0 || nj >= M) continue;
      if (board[ni][nj] == 0) continue;
      pre.erase(board[ni][nj]);
    }
    if (pre.size() != 1) return cout << "NIE\n", void();

    board[i + 1][j] = *pre.begin();

    set<int> pre1, pre2;
    for (int k = 0; k < 4; k++) {
      int x1 = board[i + 1][j];
      if (adj[x1][k] && board[i][j] != adj[x1][k]) pre1.insert(adj[x1][k]);
    }
    for (int k = 0; k < 4; k++) {
      int x2 = board[i][j + 1];
      if (adj[x2][k] && pre1.count(adj[x2][k])) pre2.insert(adj[x2][k]);
    }
    if (pre2.size() != 1) return cout << "NIE\n", void();

    board[i + 1][j + 1] = *pre2.begin();
  }

  for (int j = 2; j < M; j++) {
    int i = 0;

    int x = board[i][j - 1];

    set<int> pre;
    for (int k = 0; k < 4; k++) {
      if (adj[x][k]) pre.insert(adj[x][k]);
    }

    for (int k = 0; k < 4; k++) {
      int ni = i + dx[k], nj = j - 1 + dy[k];
      if (ni < 0 || ni >= N || nj < 0 || nj >= M) continue;
      if (board[ni][nj] == 0) continue;
      pre.erase(board[ni][nj]);
    }
    if (pre.size() != 1) return cout << "NIE\n", void();

    board[i][j] = *pre.begin();

    for (int i = 1; i < N; i++) {
      set<int> pre1, pre2;
      for (int k = 0; k < 4; k++) {
        int x1 = board[i - 1][j];
        if (adj[x1][k] && board[i - 1][j - 1] != adj[x1][k]) pre1.insert(adj[x1][k]);
      }
      for (int k = 0; k < 4; k++) {
        int x2 = board[i][j - 1];
        if (adj[x2][k] && pre1.count(adj[x2][k])) pre2.insert(adj[x2][k]);
      }
      if (pre2.size() != 1) return cout << "NIE\n", void();

      board[i][j] = *pre2.begin();
    }
  }

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      cout << board[i][j] << ' ';
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
