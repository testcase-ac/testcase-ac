#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
vector<int> graph[MAX + 1];
int vis[MAX + 1], types[MAX + 1], ccnt[MAX + 1];

void dfs(int v, int cc, int type) {
  vis[v] = cc;

  for (int d : graph[v]) {
    if (vis[d] || type != types[d]) continue;
    dfs(d, cc, type);
  }
}

int main() {
  fast_io();

  int n;
  cin >> n;
  for (int i = 0; i < n - 1; i++) {
    int x, y;
    cin >> x >> y;
    graph[x].push_back(y);
    graph[y].push_back(x);
  }
  string types_str;
  cin >> types_str;
  for (int i = 1; i <= n; i++) types[i] = types_str[i - 1] == 'B';

  int cc = 0;
  for (int i = 1; i <= n; i++) {
    if (!vis[i]) dfs(i, ++cc, types[i]);
  }
  for (int i = 1; i <= n; i++) ccnt[vis[i]]++;

  long long ans = 0;
  for (int i = 1; i <= n; i++) {
    if (!types[i]) continue;
    for (int d : graph[i]) {
      if (!types[d]) ans += ccnt[vis[d]];
    }
  }
  cout << ans << '\n';
}
