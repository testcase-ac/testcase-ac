#include <bits/stdc++.h>
using namespace std;
using tii = tuple<int, int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
set<int> graph[MAX + 1];
bool vis[MAX + 1];
int vs[MAX + 1], ve[MAX + 1];

int tick = 0;
void dfs(int v) {
  vis[v] = true;
  vs[v] = ++tick;
  for (int d : graph[v]) {
    if (!vis[d]) dfs(d);
  }
  ve[v] = ++tick;
}

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    int v;
    cin >> v;

    while (1) {
      int x;
      cin >> x;
      if (x == -1) break;
      graph[v].insert(x);
    }
  }

  int r;
  cin >> r;
  dfs(r);

  for (int i = 1; i <= n; i++) cout << i << ' ' << vs[i] << ' ' << ve[i] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
