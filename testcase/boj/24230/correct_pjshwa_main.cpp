#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2e5;
int c[MAX + 1];
vector<int> graph[MAX + 1];
bool vis[MAX + 1];
int cnt = 0;

void dfs(int v, int color) {
  vis[v] = 1;
  if (color != c[v]) cnt++;

  for (int d : graph[v]) {
    if (!vis[d]) dfs(d, c[v]);
  }
}

int main() {
  fast_io();

  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> c[i];
  for (int i = 1; i <= n - 1; i++) {
    int a, b;
    cin >> a >> b;
    graph[a].push_back(b);
    graph[b].push_back(a);
  }
  dfs(1, 0);
  cout << cnt << '\n';
}
