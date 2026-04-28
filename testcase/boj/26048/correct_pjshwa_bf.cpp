#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};

void solve() {
  int W, H, X, Y;
  cin >> W >> H >> X >> Y;

  vector<string> M(H, string(W, '0'));
  M[Y - 1][X - 1] = '1';

  set<pair<vector<string>, pii>> vis;
  queue<pair<vector<string>, pii>> q;
  q.push({M, {Y - 1, X - 1}});
  vis.insert({M, {Y - 1, X - 1}});

  while (!q.empty()) {
    auto [M, p] = q.front(); q.pop();

    int y = p.first, x = p.second;
    for (int i = 0; i < 4; i++) {
      int ny = y + dy[i], nx = x + dx[i];
      if (ny < 0 || ny >= H || nx < 0 || nx >= W) continue;
      if (M[ny][nx] == '1') continue;

      auto M2 = M;
      M2[ny][nx] = '1';
      if (vis.count({M2, {ny, nx}})) continue;
      vis.insert({M2, {ny, nx}});
      q.push({M2, {ny, nx}});
    }
  }

  
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
