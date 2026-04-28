#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 2000;
vector<int> adj[MAXN + 1];
int cdist[MAXN + 1][MAXN + 1];

void solve() {
  int N, M; cin >> N >> M;
  while (M--) {
    int u, v; cin >> u >> v;
    adj[u].push_back(v);
  }

  memset(cdist, -1, sizeof cdist); queue<int> q;
  for (int i = 1; i <= N; ++i) {
    cdist[i][i] = 0; q.push(i);
    while (!q.empty()) {
      int u = q.front(); q.pop();
      for (int v : adj[u]) {
        if (cdist[i][v] != -1) continue;
        cdist[i][v] = cdist[i][u] + 1;
        q.push(v);
      }
    }
  }

  int Q; cin >> Q;
  vector<pii> pts;
  while (Q--) {
    int a, b, k; cin >> a >> b >> k;
    while (k--) {
      int x; cin >> x;
      pts.emplace_back(cdist[a][x], x);
    }
    sort(pts.begin(), pts.end());

    int sum = 0, u = a, ok = cdist[a][b] != -1;
    for (auto& p : pts) {
      ok &= (cdist[u][p.second] != -1);
      sum += cdist[u][p.second], u = p.second;
    }
    sum += cdist[u][b];
    ok &= (cdist[u][b] != -1);

    if (ok && sum == cdist[a][b]) cout << "YES\n";
    else cout << "NO\n";
    pts.clear();
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
