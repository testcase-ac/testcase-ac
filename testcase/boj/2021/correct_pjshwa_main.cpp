#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2e5 + 1;
bool vis[MAX];
int a[MAX], s, e;
vector<int> graph[MAX];

int bfs() {
  queue<pair<int, int>> q;
  q.push({s, 0});

  while (!q.empty()) {
    auto[v, d] = q.front();
    q.pop();

    if (v == e) return d / 2 - 1;

    if (vis[v]) continue;
    vis[v] = true;

    for (int nxt : graph[v]) if (!vis[nxt]) q.push({nxt, d + 1});
  }

  return -1;
}

int main() {
  fast_io();

  int n, m, bias = 1e5;
  cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    int x;
    while (1) {
      cin >> x;
      if (x == -1) break;

      graph[x].push_back(i + bias);
      graph[i + bias].push_back(x);
    }
  }
  cin >> s >> e;
  
  if (s == e) cout << 0;
  else cout << bfs();
}
