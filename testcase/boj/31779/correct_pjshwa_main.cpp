#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1000;
const int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};
int A[MAXN][MAXN], B[MAXN][MAXN];
int vis[MAXN][MAXN];

void solve() {
  int N, M, K; cin >> N >> M >> K;
  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) cin >> A[i][j];
  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) cin >> B[i][j];

  while (K--) {
    int x, y; cin >> x >> y; --x, --y;
    vis[x][y] = 1;
    if (A[x][y] != B[x][y]) return cout << "No\n", void();
  }

  queue<pii> Q;
  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
    if (vis[i][j]) continue;
    Q.push({i, j}); vis[i][j] = 1;

    ll sumA = 0, sumB = 0;
    while (!Q.empty()) {
      auto [x, y] = Q.front(); Q.pop();
      if ((x + y) % 2) sumA += A[x][y], sumB += B[x][y];
      else sumA -= A[x][y], sumB -= B[x][y];
      for (int k = 0; k < 4; ++k) {
        int nx = x + dx[k], ny = y + dy[k];
        if (nx < 0 || nx >= N || ny < 0 || ny >= M || vis[nx][ny]) continue;
        Q.push({nx, ny}); vis[nx][ny] = 1;
      }
    }

    if (sumA != sumB) return cout << "No\n", void();
  }

  cout << "Yes\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
