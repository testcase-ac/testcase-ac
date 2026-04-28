#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 100;
const int dx[] = {0, 0, 1, -1}, dy[] = {1, -1, 0, 0};
int C[MAXN][MAXN];
bool vis[MAXN][MAXN];

void solve() {
  int N, M; cin >> N >> M;
  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) cin >> C[i][j];

  int D; cin >> D;
  queue<pii> Q;
  Q.emplace(0, 0); vis[0][0] = true;

  while (!Q.empty()) {
    auto [x, y] = Q.front(); Q.pop();
    for (int nx = x - D; nx <= x + D; ++nx) for (int ny = y - D; ny <= y + D; ++ny) {
      if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue;
      if (abs(nx - x) + abs(ny - y) > D) continue;
      if (vis[nx][ny] || C[nx][ny] != C[x][y]) continue;
      Q.emplace(nx, ny); vis[nx][ny] = true;
    }
  }

  if (vis[N - 1][M - 1]) cout << "ALIVE\n";
  else cout << "DEAD\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
