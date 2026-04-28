#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 50, INF = 0x3f3f3f3f;
vector<int> adj[MAX + 1];

void solve() {
  int N; cin >> N;
  while (1) {
    int u, v; cin >> u >> v;
    if (u == -1 && v == -1) break;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  int uans[N + 1]; memset(uans, 0, sizeof(uans));

  queue<int> q;
  for (int i = 1; i <= N; ++i) {
    int cdist[N + 1]; memset(cdist, 0x3f, sizeof(cdist));
    q.push(i); cdist[i] = 0;

    while (!q.empty()) {
      int u = q.front(); q.pop();
      for (int v : adj[u]) {
        if (cdist[v] > cdist[u] + 1) {
          cdist[v] = cdist[u] + 1;
          q.push(v);
        }
      }
    }

    for (int j = 1; j <= N; ++j) uans[i] = max(uans[i], cdist[j]);
  }

  int umin = INF;
  for (int i = 1; i <= N; ++i) umin = min(umin, uans[i]);

  int ucnt = 0;
  for (int i = 1; i <= N; ++i) if (uans[i] == umin) ++ucnt;

  cout << umin << ' ' << ucnt << '\n';
  for (int i = 1; i <= N; ++i) if (uans[i] == umin) cout << i << ' ';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
