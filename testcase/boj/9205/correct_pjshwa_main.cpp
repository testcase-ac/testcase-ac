#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 100;
pii a[MAX + 2];
vector<int> graph[MAX + 10];
bool vis[MAX + 10];

void dfs(int v) {
  vis[v] = 1;
  for (int d : graph[v]) {
    if (!vis[d]) dfs(d);
  }
}

void solve() {
  int n;
  cin >> n;
  for (int i = 0, x, y; i < n + 2; i++) {
    cin >> x >> y;
    a[i] = {x, y};
  }

  memset(vis, 0, sizeof(vis));
  for (int i = 0; i < n + 2; i++) graph[i].clear();

  for (int i = 0; i < n + 2; i++) for (int j = i + 1; j < n + 2; j++) {
    auto [ax, ay] = a[i];
    auto [bx, by] = a[j];
    if (abs(ax - bx) + abs(ay - by) <= 1000) {
      graph[i].push_back(j);
      graph[j].push_back(i);
    }
  }
  dfs(0);
  if (vis[n + 1]) cout << "happy\n";
  else cout << "sad\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
