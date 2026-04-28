#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pipii = pair<int, pii>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 100;
const int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};
int board[MAX][MAX];
bool vis[MAX][MAX];

void solve() {
  int N, M;
  cin >> N >> M;
  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) cin >> board[i][j];

  priority_queue<pipii, vector<pipii>, greater<pipii>> pq;
  for (int i = 0; i < N; i++) {
    pq.push({board[i][0], {i, 0}});
    vis[i][0] = true;
    pq.push({board[i][M - 1], {i, M - 1}});
    vis[i][M - 1] = true;
  }
  for (int j = 0; j < M; j++) {
    pq.push({board[0][j], {0, j}});
    vis[0][j] = true;
    pq.push({board[N - 1][j], {N - 1, j}});
    vis[N - 1][j] = true;
  }

  int ans = 0;
  while (!pq.empty()) {
    auto [h, x] = pq.top();
    auto [i, j] = x;
    pq.pop();

    for (int k = 0; k < 4; k++) {
      int ni = i + dx[k], nj = j + dy[k];
      if (ni < 0 || ni >= N || nj < 0 || nj >= M) continue;
      if (vis[ni][nj]) continue;

      vis[ni][nj] = true;
      if (h <= board[ni][nj]) {
        pq.push({board[ni][nj], {ni, nj}});
      }
      else {
        int diff = h - board[ni][nj];
        ans += diff;
        pq.push({h, {ni, nj}});
      }
    }
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
