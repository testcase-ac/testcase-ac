#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 500;
const int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};
int A[MAXN][MAXN], cdist[MAXN][MAXN];

void solve() {
  int N, M; cin >> N >> M;
  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) cin >> A[i][j];

  using T = tuple<int, int, int, int>;
  priority_queue<T, vector<T>, greater<T>> pq;

  memset(cdist, 0x3f, sizeof(cdist));
  for (int i = 0; i < N; ++i) {
    cdist[i][M - 1] = A[i][M - 1];
    pq.emplace(cdist[i][M - 1], i, M - 1, i);
  }

  vector<int> C(N);
  while (!pq.empty()) {
    auto [d, x, y, s] = pq.top(); pq.pop();
    if (cdist[x][y] != d) continue;
    if (y == 0) ++C[s];
    for (int k = 0; k < 4; ++k) {
      int nx = x + dx[k], ny = y + dy[k];
      if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue;
      int nd = d + A[nx][ny];
      if (cdist[nx][ny] > nd) {
        cdist[nx][ny] = nd;
        pq.emplace(nd, nx, ny, s);
      }
    }
  }

  assert(accumulate(C.begin(), C.end(), 0) == N);
  for (int i = 0; i < N; ++i) cout << C[i] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
