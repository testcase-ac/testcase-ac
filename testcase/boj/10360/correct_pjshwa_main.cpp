#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000;
const ll INF = 1e18;
vector<pii> graph[MAX + 1];
vector<int> rgraph[MAX + 1];
ll cdist[MAX + 1];
bool reach[MAX + 1];

void dfs(int v) {
  reach[v] = 1;
  for (int d : rgraph[v]) {
    if (!reach[d]) dfs(d);
  }
}

int tc;
void solve() {
  cout << "Case #" << ++tc << ": ";

  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; i++) graph[i].clear();
  for (int i = 0; i < n; i++) rgraph[i].clear();
  for (int i = 0; i < n; i++) reach[i] = false;

  while (m--) {
    int u, v, w;
    cin >> u >> v >> w;
    graph[u].push_back({v, w});
    rgraph[v].push_back(u);
  }
  
  dfs(0);
  cdist[0] = 0;
  for (int i = 1; i < n; i++) cdist[i] = INF;

  // Bellman-ford
  for (int it = 1; it <= n; it++) {
    for (int i = 0; i < n; i++) {
      for (auto& e : graph[i]) {
        auto [v, w] = e;
        if (cdist[v] > cdist[i] + w) {
          cdist[v] = cdist[i] + w;
          if (reach[v] && it == n) return cout << "possible\n", void();
        }
      }
    }
  }

  cout << "not possible\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
