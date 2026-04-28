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

bool bellman_ford(int s) {
  for (int i = 1; i <= n; i++) cdist[i] = INF;
  cdist[s] = 0;

  for (int it = 1; it <= n; it++) {
    for (int i = 1; i <= n; i++) {
      for (pii& p : graph[i]) {
        auto [u, d] = p;
        if (cdist[i] != INF && cdist[i] + d < cdist[u]) {
          cdist[u] = cdist[i] + d;
          if (it == n) return false;
        }
      }
    }
  }
  return true;
}

void solve() {
  int m;
  cin >> n >> m;
  while (m--) {
    int a, b, c;
    cin >> a >> b >> c;
    graph[a].push_back({b, c});
  }

  bool res = bellman_ford(1);
  if (res) for (int i = 2; i <= n; i++) cout << (cdist[i] == INF ? -1 : cdist[i]) << '\n';
  else cout << "-1\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
