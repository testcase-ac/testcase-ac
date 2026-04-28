#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 50, MAXV = 2520, INF = 0x3f3f3f3f;
const int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};
char board[MAXN + 1][MAXN + 1];
int B[MAXN][MAXN], cdist[MAXN][MAXN];
vector<pii> adj[MAXN][MAXN];

void solve() {
  int N, M; cin >> N >> M;
  for (int i = 0; i < N; ++i) {
    cin >> board[i];
    for (int j = 0; j < M; ++j) {
      B[i][j] = MAXV / (board[i][j] - '0');
    }
  }
  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) adj[i][j].clear();

  using T = tuple<int, int, int>;
  priority_queue<T, vector<T>, greater<T>> pq;
  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
    memset(cdist, 0x3f, sizeof(cdist));
    cdist[i][j] = B[i][j]; pq.emplace(B[i][j], i, j);

    while (!pq.empty()) {
      auto [w, x, y] = pq.top(); pq.pop();
      if (cdist[x][y] < w) continue;

      for (int k = 0; k < 4; ++k) {
        int nx = x + dx[k], ny = y + dy[k];
        if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue;
        if (w + B[nx][ny] > MAXV) continue;

        if (cdist[nx][ny] > w + B[nx][ny]) {
          cdist[nx][ny] = w + B[nx][ny];
          pq.emplace(w + B[nx][ny], nx, ny);
        }
      }
    }

    for (int ni = 0; ni < N; ++ni) for (int nj = 0; nj < M; ++nj) {
      if (cdist[ni][nj] <= MAXV) {
        adj[i][j].emplace_back(ni, nj);
        // cout << "(" << i << ", " << j << ") -> (" << ni << ", " << nj << ")\n";
      }
    }
  }

  int Sx, Sy, Dx, Dy; cin >> Sx >> Sy >> Dx >> Dy; --Sx, --Sy, --Dx, --Dy;

  queue<pii> q;
  memset(cdist, 0x3f, sizeof(cdist));
  cdist[Sx][Sy] = 0; q.emplace(Sx, Sy);

  while (!q.empty()) {
    auto [x, y] = q.front(); q.pop();
    if (x == Dx && y == Dy) break;

    for (auto [nx, ny] : adj[x][y]) {
      if (cdist[nx][ny] > cdist[x][y] + 1) {
        cdist[nx][ny] = cdist[x][y] + 1;
        q.emplace(nx, ny);
      }
    }
  }

  int ans = cdist[Dx][Dy];
  if (ans == INF) ans = -1;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
