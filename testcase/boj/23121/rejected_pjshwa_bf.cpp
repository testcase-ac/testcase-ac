#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXP = 200, INF = 0x3f3f3f3f;
int D[MAXP + 1][MAXP + 1];
int P;

void solve() {
  int a, b, c, d; cin >> a >> b >> c >> d;

  memset(D, 0x3f, sizeof(D));
  queue<pii> Q;
  Q.emplace(a, b); D[a][b] = 0;

  while (!Q.empty()) {
    auto [x, y] = Q.front(); Q.pop();

    {
      int nx = 2 * x % P, ny = (y + P - x) % P;
      if (D[nx][ny] > D[x][y] + 1) {
        D[nx][ny] = D[x][y] + 1;
        Q.emplace(nx, ny);
      }
    }
    {
      int nx = (x + P - y) % P, ny = 2 * y % P;
      if (D[nx][ny] > D[x][y] + 1) {
        D[nx][ny] = D[x][y] + 1;
        Q.emplace(nx, ny);
      }
    }
  }

  int ans = D[c][d] == INF ? -1 : D[c][d];
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> P >> t;
  while (t--) solve();
}
