#include <bits/stdc++.h> 
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};

int ans = 0, cur = 0;
int cc;
int N, M;
int board[8][8], rs[3][8][8];

void dfs(int i, int j, int v) {
  cc++;
  board[i][j] = 0;
  for (int k = 0; k < 4; k++) {
    int nx = i + dx[k], ny = j + dy[k];
    if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue;
    if (v == board[nx][ny]) dfs(nx, ny, v);
  }
}

void drop() {
  for (int k = 0; k < N; k++) {
    for (int i = N - 1; i >= 1; i--) for (int j = 0; j < M; j++) {
      if (board[i][j] == 0 && board[i - 1][j] != 0) swap(board[i][j], board[i - 1][j]);
    }
  }
}

void init(int v) {
  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) {
    board[i][j] = rs[v][i][j];
  }
}

void copy(int v) {
  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) {
    rs[v][i][j] = board[i][j];
  }
}

void r(int v) {
  ans = max(ans, cur);
  if (v == 3) return;

  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) {
    if (rs[v][i][j] == 0) continue;

    init(v);
    cc = 0;
    dfs(i, j, board[i][j]);

    int val = cc;
    cur += val * val;
    drop();
    copy(v + 1);
    r(v + 1);

    cur -= val * val;
  }
}

void solve() {
  cin >> M >> N;
  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) cin >> rs[0][i][j];

  r(0);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
