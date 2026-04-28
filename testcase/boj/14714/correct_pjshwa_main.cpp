#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 500;
bool vis[2][MAX][MAX];

int main() {
  fast_io();

  int n, a, b, da, db;
  cin >> n >> a >> b >> da >> db;

  queue<tuple<int, int, int, int>> q;
  q.push({a - 1, b - 1, 0, 0});
  vis[0][a - 1][b - 1] = true;

  while (!q.empty()) {
    auto [ca, cb, d, turn] = q.front();
    q.pop();

    if (ca == cb) return cout << d << '\n', 0;

    if (turn) {
      int pb = (cb + db) % n, nb = (cb + (n - db)) % n;
      if (!vis[turn ^ 1][ca][pb]) vis[turn ^ 1][ca][pb] = true, q.push({ca, pb, d + 1, turn ^ 1});
      if (!vis[turn ^ 1][ca][nb]) vis[turn ^ 1][ca][nb] = true, q.push({ca, nb, d + 1, turn ^ 1});
    }
    else {
      int pa = (ca + da) % n, na = (ca + (n - da)) % n;
      if (!vis[turn ^ 1][pa][cb]) vis[turn ^ 1][pa][cb] = true, q.push({pa, cb, d + 1, turn ^ 1});
      if (!vis[turn ^ 1][na][cb]) vis[turn ^ 1][na][cb] = true, q.push({na, cb, d + 1, turn ^ 1});
    }
  }

  cout << "Evil Galazy\n";
}
