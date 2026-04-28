#include <bits/stdc++.h>
typedef long long ll;
#define pll pair<ll, ll>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const ll MAX = 1e4, INF = 1e14;
bool vis[MAX + 1];
ll cdist[MAX + 1], ans = INF;
vector<pll> graph[MAX + 1];

void dijk(int s) {
  cdist[s] = 0;

  priority_queue<pll, vector<pll>, greater<pll>> pq;
  pq.push({0, s});

  while (!pq.empty()) {
    auto [wi, ui] = pq.top();
    pq.pop();

    if (wi > cdist[ui]) continue;

    for (auto &p : graph[ui]) {
      auto[vi, di] = p;
      if (cdist[vi] > di + wi) {
        cdist[vi] = di + wi;
        pq.push({cdist[vi], vi});
      }
    }
  }
}

void dfs(int v) {
  vis[v] = true;
  for (auto [d, s] : graph[v]) if (!vis[d]) dfs(d);
}

void solve() {
  int n, d, c;
  cin >> n >> d >> c;

  for (int i = 1; i <= n; i++) graph[i].clear();
  memset(vis, 0, sizeof(vis));
  fill(cdist, cdist + MAX + 1, INF);

  while (d--) {
    int a, b, s;
    cin >> a >> b >> s;
    graph[b].push_back({a, s});
  }

  dijk(c);
  dfs(c);

  int cnt = 0;
  ll mdist = 0;
  for (int i = 1; i <= n; i++) if (vis[i]) cnt++;
  for (int i = 1; i <= n; i++) if (cdist[i] < INF) mdist = max(mdist, cdist[i]);
  cout << cnt << ' ' << mdist << '\n';
}

int main() {
  fast_io();

  int t;
  cin >> t;
  while (t--) solve();
}
