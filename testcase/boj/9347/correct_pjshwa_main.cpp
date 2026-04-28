#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1000, INF = 0x3f3f3f3f;
const int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};
int A[MAXN][MAXN], cdist[MAXN][MAXN];

void solve() {
  int N, M; cin >> N >> M;
  auto is_border = [&](int x, int y) {
    return x == 0 || x == N - 1 || y == 0 || y == M - 1;
  };

  deque<pii> dq;
  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
    cin >> A[i][j]; cdist[i][j] = INF;
    if (!is_border(i, j)) continue;
    if (A[i][j] == 0) dq.emplace_front(i, j);
    else dq.emplace_back(i, j);
    cdist[i][j] = A[i][j];
  }

  int maxd = 0;
  while (!dq.empty()) {
    auto p = dq.front(); dq.pop_front();
    int x = p.first, y = p.second, d = cdist[x][y];
    if (A[x][y] == 0 && d > maxd) maxd = d;
    for (int k = 0; k < 4; ++k) {
      int nx = x + dx[k], ny = y + dy[k];
      if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue;
      int nd = d + A[nx][ny];
      if (cdist[nx][ny] > nd) {
        cdist[nx][ny] = nd;
        if (A[nx][ny] == 0) dq.emplace_front(nx, ny);
        else dq.emplace_back(nx, ny);
      }
    }
  }

  int ans = 0;
  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
    if (A[i][j] == 0 && cdist[i][j] == maxd) ++ans;
  }
  cout << maxd << ' ' << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
