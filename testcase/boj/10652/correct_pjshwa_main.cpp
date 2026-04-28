#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 4e4;
vector<int> graph[MAX + 1];
ll dist[MAX + 1][3];
bool vis[MAX + 1][3];

void bfs(int s, int ix) {
  queue<pair<int, int>> q;
  q.push({s, 0});

  while (!q.empty()) {
    auto [cc, cd] = q.front();
    q.pop();

    if (vis[cc][ix]) continue;
    vis[cc][ix] = true;
    dist[cc][ix] = cd;

    for (auto &i : graph[cc]) {
      if (vis[i][ix]) continue;
      q.push({i, cd + 1});
    }
  }
}

int main() {
  fast_io();

  int b, e, p, n, m;
  cin >> b >> e >> p >> n >> m;

  while (m--) {
    int x, y;
    cin >> x >> y;
    graph[x].push_back(y);
    graph[y].push_back(x);
  }

  bfs(1, 0);
  bfs(2, 1);
  bfs(n, 2);

  ll mx = 1e18;
  for (int i = 1; i <= n; i++) mx = min(mx, dist[i][0] * b + dist[i][1] * e + dist[i][2] * p);
  cout << mx;
}
