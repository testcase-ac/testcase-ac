#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5 + 1e3 + 1;
bool vis[MAX];
int a[MAX], n;
vector<int> graph[MAX];

int bfs() {
  queue<pair<int, int>> q;
  q.push({1, 0});

  while (!q.empty()) {
    auto[v, d] = q.front();
    q.pop();

    if (v == n) return d / 2 + 1;

    if (vis[v]) continue;
    vis[v] = true;

    for (int nxt : graph[v]) if (!vis[nxt]) q.push({nxt, d + 1});
  }

  return -1;
}

int main() {
  fast_io();

  int k, m, bias = 1e5;
  cin >> n >> k >> m;
  for (int i = 1; i <= m; i++) {
    int x;
    for (int j = 0; j < k; j++) {
      cin >> x;
      graph[x].push_back(i + bias);
      graph[i + bias].push_back(x);
    }
  }

  cout << bfs();
}
