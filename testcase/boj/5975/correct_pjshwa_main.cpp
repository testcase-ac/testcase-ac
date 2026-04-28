#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 100;
vector<int> graph[MAX];
set<int> reach[MAX];
bool vis[MAX];
int n;

void bfs(int s) {
  queue<pii> q;
  q.push({s, 0});
  vis[s] = true;

  while (!q.empty()) {
    auto [v, d] = q.front();
    q.pop();

    reach[d].insert(v);
    for (auto u : graph[v]) if (!vis[u]) vis[u] = true, q.push({u, d + 1});
  }
}

int main() {
  fast_io();

  int s, x;
  cin >> n >> s;
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
    cin >> x;
    if (x == 1) graph[i].push_back(j);
  }
  bfs(s - 1);

  for (int i = 0; i < MAX; i++) {
    if (reach[i].empty()) break;
    for (auto v : reach[i]) cout << v + 1 << ' ';
    cout << '\n';
  }
}
