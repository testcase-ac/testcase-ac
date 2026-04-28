#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 100;
const int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};
char board[MAX + 1][MAX + 1];
bool vis[MAX][MAX];
int N, M, cur;

void dfs(int i, int j) {
  vis[i][j] = true;
  cur++;
  for (int k = 0; k < 4; k++) {
    int nx = i + dx[k], ny = j + dy[k];
    if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue;
    if (board[nx][ny] != board[i][j] || vis[nx][ny]) continue;
    dfs(nx, ny);
  }
}

void solve() {
  cin >> M >> N;
  for (int i = 0; i < N; i++) cin >> board[i];

  int v[2] = {0};
  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) {
    if (vis[i][j]) continue;
    cur = 0;
    dfs(i, j);
    v[board[i][j] == 'B'] += cur * cur;
  }

  cout << v[0] << ' ' << v[1] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
