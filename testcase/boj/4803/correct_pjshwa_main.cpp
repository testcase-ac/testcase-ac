#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 500;
int n, m;
int tc;
vector<int> graph[MAX + 1];
bool vis[MAX + 1];

bool dfs(int v, int par) {
  vis[v] = 1;

  int res = true;
  for (int d : graph[v]) {
    if (vis[d]) {
      if (d != par) res = false;
      continue;
    }
    res &= dfs(d, v);
  }
  return res;
}

void solve() {
  for (int i = 1; i <= n; i++) graph[i].clear();
  memset(vis, 0, sizeof(vis));

  while (m--) {
    int a, b;
    cin >> a >> b;
    graph[a].push_back(b);
    graph[b].push_back(a);
  }

  int cnt = 0;
  for (int i = 1; i <= n; i++) {
    if (!vis[i]) {
      if (dfs(i, -1)) cnt++;
    }
  }

  cout << "Case " << ++tc << ": ";
  if (cnt == 0) cout << "No trees.\n";
  else if (cnt == 1) cout << "There is one tree.\n";
  else cout << "A forest of " << cnt << " trees.\n";
}

int main() {
  fast_io();

  while (1) {
    cin >> n >> m;
    if (n == 0 && m == 0) break;
    solve();
  }
}
