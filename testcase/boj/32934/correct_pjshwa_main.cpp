#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 2e5, INF = 0x3f3f3f3f;
int deg[MAXN + 1], cdist[MAXN + 1], V[MAXN + 1];
vector<int> adj[MAXN + 1];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N - 1; ++i) {
    int u, v; cin >> u >> v;
    adj[u].push_back(v); adj[v].push_back(u);
    ++deg[u]; ++deg[v];
  }

  queue<int> Q;
  memset(cdist, 0x3f, sizeof(cdist));
  for (int i = 1; i <= N; ++i) {
    if (deg[i] != 1 && deg[i] != 3) return cout << "-1\n", void();
    if (deg[i] == 1) cdist[i] = 0, Q.push(i);
    else V[i] = 1;
  }

  int d = 1;
  while (!Q.empty()) {
    queue<int> nQ;
    while (!Q.empty()) {
      int v = Q.front(); Q.pop();
      for (int u : adj[v]) {
        if (cdist[u] == INF) {
          cdist[u] = cdist[v] + 1;
          nQ.push(u);
        } else if (cdist[u] < d) {
          V[u] = 0;
        }
      }
    }
    Q = nQ; ++d;
  }

  vector<int> ans;
  for (int i = 1; i <= N; ++i) {
    if (V[i]) ans.push_back(i);
  }
  if (ans.empty()) cout << "-1\n";
  else {
    cout << ans.size() << '\n';
    for (int v : ans) cout << v << ' ';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
