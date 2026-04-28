#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 500, INF = 0x3f3f3f3f;
const int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};
char board[MAX + 1][MAX + 1];
vector<tii> graph[MAX][MAX][2];
int cdist[MAX][MAX][2];

void solve() {
  int N, t, r, c;
  cin >> N >> t >> r >> c;
  r--; c--;
  for (int i = 0; i < N; i++) cin >> board[i];

  for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) {
    for (int k = 0; k < 4; k++) {
      int ni = i + dx[k], nj = j + dy[k];
      if (ni < 0 || ni >= N || nj < 0 || nj >= N) continue;
      graph[i][j][0].push_back({ni, nj, 0, 1});
    }
    graph[i][j][0].push_back({i, j, 1, t});
    graph[i][j][1].push_back({i, j, 0, 0});
  }

  for (int i = 0; i < N; i++) {
    int leftmost = -1;
    for (int j = 0; j < N; j++) {
      if (leftmost != -1) graph[i][j][1].push_back({i, leftmost, 1, 1});
      if (board[i][j] == '#') leftmost = j;
    }
  }

  for (int i = 0; i < N; i++) {
    int rightmost = -1;
    for (int j = N - 1; j >= 0; j--) {
      if (rightmost != -1) graph[i][j][1].push_back({i, rightmost, 1, 1});
      if (board[i][j] == '#') rightmost = j;
    }
  }

  for (int j = 0; j < N; j++) {
    int topmost = -1;
    for (int i = 0; i < N; i++) {
      if (topmost != -1) graph[i][j][1].push_back({topmost, j, 1, 1});
      if (board[i][j] == '#') topmost = i;
    }
  }

  for (int j = 0; j < N; j++) {
    int bottommost = -1;
    for (int i = N - 1; i >= 0; i--) {
      if (bottommost != -1) graph[i][j][1].push_back({bottommost, j, 1, 1});
      if (board[i][j] == '#') bottommost = i;
    }
  }

  for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) {
    cdist[i][j][0] = cdist[i][j][1] = INF;
  }
  cdist[0][0][0] = 0;

  priority_queue<tii, vector<tii>, greater<tii>> pq;
  pq.push({0, 0, 0, 0});

  while (!pq.empty()) {
    auto [w, ui, uj, uk] = pq.top();
    pq.pop();

    if (w > cdist[ui][uj][uk]) continue;

    for (auto& [ni, nj, nk, nd] : graph[ui][uj][uk]) {
      if (cdist[ni][nj][nk] > nd + w) {
        cdist[ni][nj][nk] = nd + w;
        pq.push({nd + w, ni, nj, nk});
      }
    }
  }

  int ans = min(cdist[r][c][0], cdist[r][c][1]);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
