#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

bool vis[101];
unordered_map<int, int> bridges;

int bfs() {
  queue<pair<int, int>> q;
  q.push({1, 0});

  while (!q.empty()) {
    auto[v, d] = q.front();
    q.pop();

    if (v == 100) return d;

    if (vis[v]) continue;
    vis[v] = true;

    for (int i = 1; i <= 6; i++) {
      int nxt = bridges.count(v + i) ? bridges[v + i] : v + i;
      if (nxt <= 100 && !vis[nxt]) q.push({nxt, d + 1});
    }
  }
}

int main() {
  fast_io();

  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n + m; i++) {
    int x, y;
    cin >> x >> y;
    bridges[x] = y;
  }

  cout << bfs();
}
