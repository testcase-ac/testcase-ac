#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 100;
vector<pii> graph[MAX + 1];
bool vis[MAX + 1], ban[5001];
int n, m, cnt;

void bfs(int s) {
  memset(vis, 0, sizeof(vis));

  queue<int> q;
  q.push(s);
  vis[s] = true;

  while (!q.empty()) {
    int cur = q.front();
    q.pop();

    cnt++;
    for (auto &e : graph[cur]) {
      if (ban[e.second]) continue;
      if (!vis[e.first]) {
        vis[e.first] = true;
        q.push(e.first);
      }
    }
  }
}

void solve() {
  for (int i = 0; i < n; i++) graph[i].clear();

  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    graph[u].push_back({v, i});
    graph[v].push_back({u, i});
  }

  memset(ban, 0, sizeof(ban));
  for (int i = 0; i < m; i++) {
    ban[i] = true;

    cnt = 0;
    bfs(0);
    if (cnt < n) return cout << "Yes\n", void();

    ban[i] = false;
  }

  cout << "No\n";
}

int main() {
  fast_io();

  while (1) {
    cin >> n >> m;
    if (n == 0 && m == 0) break;
    solve();
  }
}
