#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 105;
const int dx[8] = {1, 1, 2, 2, -1, -1, -2, -2};
const int dy[8] = {2, -2, 1, -1, 2, -2, 1, -1};
ll D[MAXN][MAXN], x, y;

void solve() {
  x = abs(x); y = abs(y);
  if (x > y) swap(x, y);

  ll ans = 0;
  while (x >= 20 || y >= 20) {
    if (x == 0) {
      ans += y - 2 * (y / 4);
      y = 0;
    } else if (x == y) {
      ans += 2 * ((x + 2) / 3);
      x = y = 0;
    } else if (y >= 2 * x) {
      ans += x;
      y -= 2 * x; x = 0;
    } else {
      ans += y - x;
      ll z = 2 * x - y;
      x = y = z;
    }
  }
  cout << ans + D[x + 2][y + 2] << '\n';
}

int main() {
  fast_io();

  queue<pii> Q;
  memset(D, 0x3f, sizeof(D));
  Q.push({2, 2}); D[2][2] = 0;

  while (!Q.empty()) {
    auto [x, y] = Q.front(); Q.pop();
    for (int i = 0; i < 8; ++i) {
      int nx = x + dx[i], ny = y + dy[i];
      if (nx < 0 || nx >= MAXN || ny < 0 || ny >= MAXN) continue;
      if (D[nx][ny] > D[x][y] + 1) {
        D[nx][ny] = D[x][y] + 1;
        Q.push({nx, ny});
      }
    }
  }

  string O;
  while (cin >> O) {
    if (O == "END") break;
    x = stoi(O); cin >> y;
    solve();
  }
}
