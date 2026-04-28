#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5, MAXE = 2e6;
const ll INF = 1e18;
ll cdist[MAX + 1];
pll from[MAX + 1];
int banned[MAXE + 1];
vector<tuple<int, int, int>> graph[MAX + 1];

void dijk(int s) {
  for (int i = 0; i <= MAX; i++) {
    cdist[i] = INF;
    from[i] = {-1, -1};
  }
  cdist[s] = 0;

  priority_queue<pll, vector<pll>, greater<pll>> pq;
  pq.push({0, s});

  while (!pq.empty()) {
    auto [wi, ui] = pq.top();
    pq.pop();

    if (wi > cdist[ui]) continue;

    for (auto &p : graph[ui]) {
      auto [vi, di, ei] = p;
      if (!banned[ei] && cdist[vi] > di + wi) {
        cdist[vi] = di + wi;
        from[vi] = {ui, ei};
        pq.push({cdist[vi], vi});
      }
    }
  }
}

void solve() {
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < m; ++i) {
    int u, v, w;
    cin >> u >> v >> w;
    graph[u].push_back({v, w, 2 * i});
    graph[v].push_back({u, w, 2 * i + 1});
  }

  dijk(1);
  for (int i = 0; i < n; i++) {
    auto [ui, ei] = from[i];
    if (ei != -1) {
      if (ei & 1) banned[ei - 1] = 1;
      else banned[ei + 1] = 1;
    }
  }

  dijk(0);
  if (cdist[1] == INF) return cout << "impossible\n", void();

  stack<int> traj;
  int v = 1;
  while (from[v].first != -1) {
    traj.push(v);
    v = from[v].first;
  }
  traj.push(v);

  cout << traj.size() << ' ';
  while (!traj.empty()) {
    cout << traj.top() << ' ';
    traj.pop();
  }
  cout << '\n';

}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
