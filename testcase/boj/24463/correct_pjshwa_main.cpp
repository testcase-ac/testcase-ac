#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2001;
const int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};
char board[MAX + 1][MAX + 1];
bool vis[MAX][MAX], mark[MAX][MAX];
pii from[MAX][MAX];

void solve() {
  int N, M;
  cin >> N >> M;
  for (int i = 0; i < N; i++) cin >> board[i];

  int si, sj;
  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) {
    bool on_edge = i == 0 || i == N - 1 || j == 0 || j == M - 1;
    if (on_edge && board[i][j] == '.') {
      si = i, sj = j;
      break;
    }
  }

  queue<pii> q;
  q.push({si, sj});
  vis[si][sj] = true;
  from[si][sj] = {-1, -1};

  int ei, ej;
  while (!q.empty()) {
    auto [i, j] = q.front();
    q.pop();

    bool on_edge = i == 0 || i == N - 1 || j == 0 || j == M - 1;
    if (on_edge && board[i][j] == '.' && !(i == si && j == sj)) {
      ei = i, ej = j;
      break;
    }

    for (int k = 0; k < 4; k++) {
      int ni = i + dx[k], nj = j + dy[k];
      if (ni < 0 || ni >= N || nj < 0 || nj >= M) continue;
      if (vis[ni][nj]) continue;
      if (board[ni][nj] == '+') continue;

      vis[ni][nj] = true;
      from[ni][nj] = {i, j};
      q.push({ni, nj});
    }
  }

  while (ei != si || ej != sj) {
    mark[ei][ej] = true;
    tie(ei, ej) = from[ei][ej];
  }
  mark[si][sj] = true;

  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) {
    if (!mark[i][j] && board[i][j] == '.') board[i][j] = '@';
  }

  for (int i = 0; i < N; i++) cout << board[i] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
