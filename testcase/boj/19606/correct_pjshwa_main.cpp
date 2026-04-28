#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e3;
vector<pii> graph[1'000'001];
bool vis[MAX + 1][MAX + 1];

int main() {
  fast_io();

  int n, m;
  cin >> n >> m;
  for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) {
    int x;
    cin >> x;
    graph[x].push_back({i, j});
  }

  queue<pii> q;
  q.push({n, m});
  vis[n][m] = true;

  while (!q.empty()) {
    auto [x, y] = q.front();
    q.pop();

    if (x == 1 && y == 1) return cout << "yes\n", 0;

    int d = x * y;
    for (auto [i, j] : graph[d]) {
      if (!vis[i][j]) {
        vis[i][j] = true;
        q.push({i, j});
      }
    }
  }

  cout << "no\n";
}
