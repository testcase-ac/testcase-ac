#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5, INF = 0x3f3f3f3f;
vector<int> gf[MAX + 1], gb[MAX + 1];
bool o[MAX + 1], c[MAX + 1];
int fdist[MAX + 1], odist[MAX + 1], cdist[MAX + 1];

void solve() {
  int n, m, k, x;
  cin >> n >> m >> k;
  while (m--) cin >> x, o[x] = 1;
  while (k--) cin >> x, c[x] = 1;
  for (int i = 1; i <= n; i++) {
    int o, x;
    cin >> o;
    while (o--) {
      cin >> x;
      gf[i].push_back(x);
      gb[x].push_back(i);
    }
  }
  fill(fdist + 1, fdist + n + 1, INF);
  fill(odist + 1, odist + n + 1, INF);
  fill(cdist + 1, cdist + n + 1, INF);

  queue<int> q;
  q.push(1);
  fdist[1] = 0;
  while (!q.empty()) {
    int v = q.front(); q.pop();

    for (int u : gf[v]) {
      if (fdist[u] > fdist[v] + 1) {
        fdist[u] = fdist[v] + 1;
        q.push(u);
      }
    }
  }

  for (int i = 1; i <= n; i++) {
    if (!o[i]) continue;
    q.push(i);
    odist[i] = 0;
  }
  while (!q.empty()) {
    int v = q.front(); q.pop();

    for (int u : gb[v]) {
      if (odist[u] > odist[v] + 1) {
        odist[u] = odist[v] + 1;
        q.push(u);
      }
    }
  }

  for (int i = 1; i <= n; i++) {
    if (!c[i]) continue;
    q.push(i);
    cdist[i] = 0;
  }
  while (!q.empty()) {
    int v = q.front(); q.pop();

    for (int u : gb[v]) {
      if (cdist[u] > cdist[v] + 1) {
        cdist[u] = cdist[v] + 1;
        q.push(u);
      }
    }
  }

  int ans = INF;
  for (int i = 1; i <= n; i++) {
    if (fdist[i] == INF || odist[i] == INF || cdist[i] == INF) continue;
    ans = min(ans, fdist[i] + odist[i] + cdist[i]);
  }

  if (ans == INF) cout << "impossible\n";
  else cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
