#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 200;
bool vis[MAX + 1][MAX + 1][MAX + 1];

void solve() {
  int a, b, c;
  cin >> a >> b >> c;

  queue<tii> q;
  q.push({0, 0, c});
  vis[0][0][c] = true;

  while (!q.empty()) {
    auto [x, y, z] = q.front();
    q.pop();

    if (x) {
      int ya = min(x, b - y);
      int za = min(x, c - z);

      if (!vis[x - ya][y + ya][z]) {
        vis[x - ya][y + ya][z] = true;
        q.push({x - ya, y + ya, z});
      }
      if (!vis[x - za][y][z + za]) {
        vis[x - za][y][z + za] = true;
        q.push({x - za, y, z + za});
      }
    }

    if (y) {
      int xa = min(y, a - x);
      int za = min(y, c - z);

      if (!vis[x + xa][y - xa][z]) {
        vis[x + xa][y - xa][z] = true;
        q.push({x + xa, y - xa, z});
      }
      if (!vis[x][y - za][z + za]) {
        vis[x][y - za][z + za] = true;
        q.push({x, y - za, z + za});
      }      
    }

    if (z) {
      int xa = min(z, a - x);
      int ya = min(z, b - y);

      if (!vis[x + xa][y][z - xa]) {
        vis[x + xa][y][z - xa] = true;
        q.push({x + xa, y, z - xa});
      }
      if (!vis[x][y + ya][z - ya]) {
        vis[x][y + ya][z - ya] = true;
        q.push({x, y + ya, z - ya});
      }
    }
  }

  for (int z = 0; z <= c; z++) {
    bool able = false;
    for (int y = 0; y <= b; y++) {
      if (vis[0][y][z]) {
        able = true;
        break;
      }
    }

    if (able) cout << z << ' ';
  }
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
