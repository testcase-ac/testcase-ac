#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 500;
const ll INF = 1e18;
vector<pii> graph[MAX + 1];
ll cdist[MAX + 1];
int n;

void init() {
  for (int i = 1; i <= n; i++) graph[i].clear();
  for (int i = 1; i <= n; i++) cdist[i] = 0;
}

bool bellman_ford() {
  for (int it = 1; it <= n; it++) {
    for (int i = 1; i <= n; i++) {
      for (pii& p : graph[i]) {
        auto [u, d] = p;
        if (cdist[i] + d < cdist[u]) {
          cdist[u] = cdist[i] + d;
          if (it == n) return false;
        }
      }
    }
  }
  return true;
}

void solve() {
  int m, w;
  cin >> n >> m >> w;

  init();

  while (m--) {
    int a, b, c;
    cin >> a >> b >> c;
    graph[a].push_back({b, c});
    graph[b].push_back({a, c});
  }
  while (w--) {
    int a, b, c;
    cin >> a >> b >> c;
    graph[a].push_back({b, -c});
  }
  cout << (bellman_ford() ? "NO\n" : "YES\n");
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
