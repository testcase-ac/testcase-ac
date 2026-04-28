#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

vector<int> graph[26];
int indegree[26];
bool vis[26], ban[26];

void dfs(int v) {
  vis[v] = true;
  for (int d : graph[v]) if (!ban[d]) dfs(d);
}

int main() {
  fast_io();

  int n, m;
  cin >> n >> m;
  while (m--) {
    string x, y;
    cin >> x >> y;
    int a = x[0] - 'A', b = y[0] - 'A';
    graph[a].push_back(b);
    indegree[b]++;
  }

  int k;
  cin >> k;
  for (int i = 0; i < k; i++) {
    string x;
    cin >> x;
    int a = x[0] - 'A';
    ban[a] = true;
  }

  int cc = 0;
  for (int i = 0; i < n; i++) {
    if (indegree[i] == 0 && !ban[i]) cc++, dfs(i);
  }

  int ans = 0;
  for (int i = 0; i < n; i++) {
    if (vis[i]) ans++;
  }
  cout << ans - cc << '\n';
}
