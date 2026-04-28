#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5;
vector<int> adj[MAXN + 1];
int K;

bool f(int u) {
  queue<int> q; set<int> vis;
  q.push(u); vis.insert(u);

  while (!q.empty()) {
    int v = q.front(); q.pop();
    for (int w : adj[v]) {
      if (vis.count(w)) continue;
      q.push(w); vis.insert(w);
      if (vis.size() > K) return true;
    }
  }
  return false;
}

int tc;
void solve() {
  cout << "Case #" << ++tc << ": ";

  int N, M; cin >> N >> M >> K;
  for (int i = 1; i <= N; i++) adj[i].clear();

  while (M--) {
    int u, v; cin >> u >> v;

    // if v is in the set, u must also be in the set
    adj[v].push_back(u);
  }

  int ans = 0;
  for (int u = 1; u <= N; ++u) ans += f(u);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
