#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

vector<pii> graph[10001];
bool vis[10001];
int s, e;
const int MAX = 1e9 + 7;

bool bfs(int load) {
  queue<int> q;
  q.push(s);
  memset(vis, 0, sizeof(vis));

  while (!q.empty()) {
    int u = q.front();
    q.pop();

    if (u == e) return true;

    if (vis[u]) continue;
    vis[u] = true;

    for (auto [v, d] : graph[u]) {
      if (d < load || vis[v]) continue;
      q.push(v);
    }
  }

  return false;
}

int main() {
  fast_io();

  int n, m;
  cin >> n >> m;
  for (int i = 0; i < m; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    graph[a].push_back(pii(b, c));
    graph[b].push_back(pii(a, c));
  }
  cin >> s >> e;

  int left = 1, right = MAX;
  int mid = (left + right) / 2;

  while (left < right) {
    if (bfs(mid)) left = mid + 1;
    else right = mid;

    mid = (left + right) / 2;
  }
  cout << mid - 1;
}
