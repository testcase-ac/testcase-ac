#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1000;
vector<tii> adj[MAX + 1];
int n, s, t;

bool reachable(int val) {
  bool vis[n + 1]; memset(vis, false, sizeof(vis));
  queue<int> Q; Q.push(s); vis[s] = true;

  while (!Q.empty()) {
    int u = Q.front(); Q.pop();
    if (u == t) return true;

    for (auto [v, c, d] : adj[u]) {
      if (vis[v]) continue;
      if (c <= val && val <= d) {
        vis[v] = true;
        Q.push(v);
      }
    }
  }
  return false;
}

void solve() {
  int m, k; cin >> n >> m >> k >> s >> t;

  vector<int> V;
  while (m--) {
    int a, b, c, d; cin >> a >> b >> c >> d;
    adj[a].emplace_back(b, c, d);
    V.push_back(c); V.push_back(d);
  }

  // dedup
  sort(V.begin(), V.end());
  V.erase(unique(V.begin(), V.end()), V.end());

  int ans = reachable(V[0]);
  for (int i = 1; i < V.size(); ++i) {
    int l = V[i - 1], r = V[i];

    if (reachable(r)) ++ans;
    if (r > l + 1 && reachable(l + 1)) ans += r - l - 1;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
