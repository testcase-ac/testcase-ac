#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 3e5, INF = 1e9 + 7;
vector<int> graph[MAX + 1];
bool vis[MAX + 1];
int cdist[MAX + 1];

void solve() {
  int n, m, k, x;
  cin >> n >> m >> k >> x;

  while (m--) {
    int u, v;
    cin >> u >> v;
    graph[u].push_back(v);
  }

  for (int i = 1; i <= n; i++) cdist[i] = INF;

  queue<pii> q;
  q.push({x, 0});
  vis[x] = 1;

  while (!q.empty()) {
    auto [x, c] = q.front();
    q.pop();

    cdist[x] = c;
    for (int d : graph[x]) {
      if (!vis[d]) vis[d] = 1, q.push({d, c + 1});
    }
  }

  bool found = false;
  for (int i = 1; i <= n; i++) {
    if (cdist[i] == k) {
      cout << i << '\n';
      found = true;
    }
  }

  if (!found) cout << "-1\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
