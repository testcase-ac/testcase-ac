#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 3000;
const int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};
int U[MAX + 10][MAX + 10];
bool vis[MAX + 10][MAX + 10];

void solve() {
  int N, M, K;
  cin >> N >> M >> K;

  while (K--) {
    int r, c, d;
    cin >> r >> c >> d;
    for (int y = c - d; y <= c + d; y++) {
      if (y < 1 || y > M) continue;

      int rem = d - abs(y - c);
      U[max(1, r - rem)][y]++;
      U[min(N, r + rem) + 1][y]--;
    }
  }

  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= M; j++) {
      U[i][j] += U[i - 1][j];
      // cout << "U[" << i << "][" << j << "] = " << U[i][j] << " ";
      if (U[i][j] > 0) vis[i][j] = true;
    }
    // cout << "\n";
  }

  queue<tii> q;
  vis[1][1] = true;
  q.emplace(1, 1, 0);

  while (!q.empty()) {
    auto [x, y, d] = q.front(); q.pop();

    if (x == N && y == M) {
      cout << "YES\n";
      cout << d << '\n';
      return;
    }

    for (int i = 0; i < 4; i++) {
      int nx = x + dx[i], ny = y + dy[i];
      if (nx < 1 || nx > N || ny < 1 || ny > M) continue;
      if (vis[nx][ny]) continue;

      vis[nx][ny] = true;
      q.emplace(nx, ny, d + 1);
    }
  }

  cout << "NO\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
