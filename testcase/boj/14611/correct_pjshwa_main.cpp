#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;
using tll = tuple<ll, ll, ll>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 300;
const ll INF = 1e18;
const int dx[8] = {1, 1, 1, 0, 0, -1, -1, -1}, dy[8] = {1, 0, -1, 1, -1, 1, 0, -1};
int board[MAX + 1][MAX + 1];
ll cdist1[MAX + 10][MAX + 10], cdist2[MAX + 10][MAX + 10];

void solve() {
  int N, M;
  cin >> N >> M;
  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= M; j++) {
      cin >> board[i][j];
      if (board[i][j] == -2) board[i][j] = 0;

      cdist1[i][j] = cdist2[i][j] = INF;
    }
  }

  priority_queue<tll, vector<tll>, greater<tll>> pq;

  for (int j = 1; j <= M; j++) {
    if (board[1][j] == -1) continue;
    cdist1[1][j] = board[1][j];
    pq.push({cdist1[1][j], 1, j});
  }
  for (int i = 1; i <= N; i++) {
    if (board[i][M] == -1) continue;
    cdist1[i][M] = board[i][M];
    pq.push({cdist1[i][M], i, M});
  }

  while (!pq.empty()) {
    auto [w, x, y] = pq.top();
    pq.pop();

    if (w > cdist1[x][y]) continue;
    for (int k = 0; k < 8; k++) {
      int nx = x + dx[k], ny = y + dy[k];
      if (nx < 1 || nx > N || ny < 1 || ny > M) continue;
      if (board[nx][ny] == -1) continue;

      if (cdist1[nx][ny] > w + board[nx][ny]) {
        cdist1[nx][ny] = w + board[nx][ny];
        pq.push({cdist1[nx][ny], nx, ny});
      }
    }
  }

  for (int j = 1; j <= M; j++) {
    if (board[N][j] == -1) continue;
    cdist2[N][j] = board[N][j];
    pq.push({cdist2[N][j], N, j});
  }
  for (int i = 1; i <= N; i++) {
    if (board[i][1] == -1) continue;
    cdist2[i][1] = board[i][1];
    pq.push({cdist2[i][1], i, 1});
  }

  while (!pq.empty()) {
    auto [w, x, y] = pq.top();
    pq.pop();

    if (w > cdist2[x][y]) continue;
    for (int k = 0; k < 8; k++) {
      int nx = x + dx[k], ny = y + dy[k];
      if (nx < 1 || nx > N || ny < 1 || ny > M) continue;
      if (board[nx][ny] == -1) continue;

      if (cdist2[nx][ny] > w + board[nx][ny]) {
        cdist2[nx][ny] = w + board[nx][ny];
        pq.push({cdist2[nx][ny], nx, ny});
      }
    }
  }

  ll ans = INF;
  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= M; j++) {
      if (board[i][j] == -1) continue;
      ans = min(ans, cdist1[i][j] + cdist2[i][j] - board[i][j]);
    }
  }

  if (ans == INF) cout << "-1\n";
  else cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
