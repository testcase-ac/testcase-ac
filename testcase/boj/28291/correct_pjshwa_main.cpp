#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 50;
const int dx[4] = {0, 0, -1, 1}, dy[4] = {1, -1, 0, 0};
int cdist[MAX][MAX], B[MAX][MAX];

void solve() {
  int N, M, K; cin >> N >> M >> K;

  memset(cdist, 0x3f, sizeof(cdist));
  vector<pii> C; queue<pii> Q;
  while (K--) {
    string U; int X, Y;
    cin >> U >> X >> Y;
    if (U == "redstone_block") {
      B[X][Y] = 1;
      Q.emplace(X, Y);
      cdist[X][Y] = 0;
    }
    if (U == "redstone_dust") {
      B[X][Y] = 1;
    }
    if (U == "redstone_lamp") {
      C.emplace_back(X, Y);
    }
  }

  while (!Q.empty()) {
    auto [x, y] = Q.front(); Q.pop();
    if (B[x][y] == 0) continue;

    for (int k = 0; k < 4; k++) {
      int nx = x + dx[k], ny = y + dy[k];
      if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue;
      if (cdist[nx][ny] > cdist[x][y] + 1) {
        cdist[nx][ny] = cdist[x][y] + 1;
        Q.emplace(nx, ny);
      }
    }
  }

  for (auto [x, y] : C) {
    if (cdist[x][y] > 15) return cout << "failed\n", void();
  }
  cout << "success\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
