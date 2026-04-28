#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 5e4;
vector<int> graph[MAX + 1];
int vis[MAX + 1];
int c1, c2;

void dfs(int v, int c) {
  vis[v] = c;
  if (c == 1) c1++;
  else c2++;

  for (int d : graph[v]) {
    if (vis[d] == c) {
      cout << "-1\n";
      exit(0);
    }
    else if (!vis[d]) dfs(d, 3 - c);
  }
}

int main() {
  fast_io();

  int n, m;
  cin >> n >> m;
  while (m--) {
    int a, b;
    cin >> a >> b;
    graph[a].push_back(b);
    graph[b].push_back(a);
  }
  
  int ans = 0;
  for (int i = 1; i <= n; i++) if (!vis[i]) {
    c1 = c2 = 0;
    dfs(i, 1);
    ans += max(c1, c2);
  }

  cout << ans << '\n';
}
