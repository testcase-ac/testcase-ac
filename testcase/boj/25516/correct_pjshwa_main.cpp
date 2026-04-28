#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5, INF = 0x3f3f3f3f;
vector<int> graph[MAX];
int V[MAX], cdist[MAX];

void solve() {
  int n, k;
  cin >> n >> k;
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    graph[u].push_back(v);
    graph[v].push_back(u);
  }
  for (int i = 0; i < n; i++) cin >> V[i];

  fill(cdist, cdist + n, INF);
  queue<int> q;
  q.push(0);
  cdist[0] = 0;

  while (!q.empty()) {
    int u = q.front(); q.pop();
    for (int v : graph[u]) {
      if (cdist[v] > cdist[u] + 1) {
        cdist[v] = cdist[u] + 1;
        q.push(v);
      }
    }
  }

  int ans = 0;
  for (int i = 0; i < n; i++) {
    if (cdist[i] <= k) ans += V[i];
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
