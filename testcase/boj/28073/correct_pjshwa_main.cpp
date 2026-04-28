#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e6, INF = 0x3f3f3f3f;
vector<int> adj[MAX + 1];
int cdist[MAX + 1];

void solve() {
  int N, M; string Ss, Es, W;
  cin >> N >> M >> Ss >> Es >> W;
  while (M--) {
    int u, v; cin >> u >> v; u--, v--;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  char S = Ss[0], E = Es[0];

  queue<int> q;
  memset(cdist, 0x3f, sizeof(cdist));
  for (int i = 0; i < N; i++) {
    if (W[i] == E) q.push(i), cdist[i] = 0;
  }

  while (!q.empty()) {
    int u = q.front(); q.pop();
    for (int v : adj[u]) {
      if (cdist[v] > cdist[u] + 1) {
        cdist[v] = cdist[u] + 1;
        q.push(v);
      }
    }
  }

  int mdist = INF;
  for (int i = 0; i < N; i++) {
    if (W[i] == S) mdist = min(mdist, cdist[i]);
  }
  if (mdist == INF) return cout << "Aaak!\n", void();

  bool vis[N]{};
  for (int i = 0; i < N; i++) {
    if (W[i] == S && cdist[i] == mdist) q.push(i), vis[i] = 1;
  }

  cout << S;
  for (int i = 0; i < mdist; i++) {
    queue<int> nq;
    char mchar = 'Z';
    while (!q.empty()) {
      int v = q.front(); q.pop();
      for (int u : adj[v]) {
        if (cdist[u] == cdist[v] - 1) mchar = min(mchar, W[u]);
      }
      nq.push(v);
    }
    while (!nq.empty()) {
      int v = nq.front(); nq.pop();
      for (int u : adj[v]) {
        if (cdist[u] == cdist[v] - 1 && W[u] == mchar && !vis[u]) {
          q.push(u), vis[u] = 1;
        }
      }
    }
    cout << mchar;
  }
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
