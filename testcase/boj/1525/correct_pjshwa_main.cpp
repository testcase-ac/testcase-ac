#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};

void solve() {
  int w[3][3], S = 0;
  for (int i = 0; i < 3; ++i) for (int j = 0; j < 3; ++j) {
    cin >> w[i][j];
    S = S * 9 + w[i][j];
  }

  int E = 0;
  for (int i = 1; i <= 8; i++) E = E * 9 + i;
  E *= 9;

  unordered_map<int, bool> vis;
  queue<pii> q;
  q.push({S, 0});
  vis[S] = true;

  while (!q.empty()) {
    auto [v, c] = q.front();
    q.pop();

    if (v == E) {
      cout << c << '\n';
      return;
    }

    int zi, zj;
    for (int i = 2; i >= 0; --i) for (int j = 2; j >= 0; --j) {
      w[i][j] = v % 9;
      v /= 9;

      if (w[i][j] == 0) zi = i, zj = j;
    }

    for (int k = 0; k < 4; k++) {
      int ni = zi + dx[k], nj = zj + dy[k];
      if (ni < 0 || ni >= 3 || nj < 0 || nj >= 3) continue;

      swap(w[zi][zj], w[ni][nj]);

      int x = 0;
      for (int i = 0; i < 3; ++i) for (int j = 0; j < 3; ++j) x = x * 9 + w[i][j];
      if (!vis[x]) {
        vis[x] = true;
        q.push({x, c + 1});
      }

      swap(w[zi][zj], w[ni][nj]);
    }
  }

  cout << "-1\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
