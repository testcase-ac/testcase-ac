#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 3e5;
vector<int> graph[MAX + 1];
bool vis[MAX + 1];

void solve() {
  int N, M, S, E;
  cin >> N >> M >> S >> E;
  while (M--) {
    int x, y;
    cin >> x >> y;
    graph[x].push_back(y);
    graph[y].push_back(x);
  }

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

    if (v + 1 <= N && !vis[v + 1]) {
      q.push({v + 1, c + 1});
      vis[v + 1] = true;
    }
    if (v - 1 >= 1 && !vis[v - 1]) {
      q.push({v - 1, c + 1});
      vis[v - 1] = true;
    }

    for (int u : graph[v]) {
      if (!vis[u]) {
        vis[u] = true;
        q.push({u, c + 1});
      }
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
