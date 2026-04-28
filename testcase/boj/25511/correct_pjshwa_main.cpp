#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
int v[MAX];
vector<int> graph[MAX];
bool vis[MAX];

void solve() {
  int n, k;
  cin >> n >> k;
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    graph[u].push_back(v);
    graph[v].push_back(u);
  }
  for (int i = 0; i < n; i++) cin >> v[i];

  queue<pii> q;
  q.push({0, 0});
  vis[0] = true;

  while (!q.empty()) {
    auto [u, c] = q.front(); q.pop();

    if (v[u] == k) return cout << c << '\n', void();

    for (int v : graph[u]) {
      if (!vis[v]) {
        vis[v] = true;
        q.push({v, c + 1});
      }
    }
  }
  
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
