#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000;
vector<int> graph[MAX + 1];
int indegree[MAX + 1];
bool vis[MAX + 1];
bool found;

void dfs(int v) {
  if (found) return;
  vis[v] = true;

  for (int u : graph[v]) {
    if (vis[u]) {
      found = true;
      return;
    }
    dfs(u);
  }
}

void solve(int tc) {
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) graph[i].clear();
  memset(indegree, 0, sizeof(indegree));
  found = false;

  for (int i = 1; i <= n; i++) {
    int mi, x;
    cin >> mi;
    while (mi--) {
      cin >> x;
      graph[i].push_back(x);
      indegree[x]++;
    }
  }

  for (int i = 1; i <= n; i++) {
    if (indegree[i] == 0) {
      memset(vis, 0, sizeof(vis));
      dfs(i);
    }
    if (found) break;
  }

  cout << "Case #" << tc << ": " << (found ? "Yes" : "No") << '\n';
}

int main() {
  fast_io();

  int t;
  cin >> t;
  for (int tc = 1; tc <= t; tc++) solve(tc);
}
