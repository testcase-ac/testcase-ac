#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

vector<int> graph[2000];
bool vis[2000], able = false;
priority_queue<pii> pq;

void dfs(int node, int d) {
  vis[node] = true;

  if (able || d == 4) {
    able = true;
    return;
  }

  for (auto dst : graph[node]) {
    if (!vis[dst]) dfs(dst, d + 1);
  }

  vis[node] = false;
}

int main() {
  fast_io();

  int n, k, a, b;
  cin >> n >> k;

  for (int i = 0; i < k; i++) {
    cin >> a >> b;
    graph[a].push_back(b);
    graph[b].push_back(a);
  }

  for (int i = 0; i < n; i++) {
    memset(vis, false, sizeof(vis));
    dfs(i, 0);
    if (able) break;
  }

  cout << able;
}
