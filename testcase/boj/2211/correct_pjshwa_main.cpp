#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000;
const ll INF = 1e18;
ll cdist[MAX + 1];
vector<pll> graph[MAX + 1];
int from[MAX + 1];

void dijk(int s) {
  fill(cdist, cdist + MAX + 1, INF);
  cdist[s] = 0;

  priority_queue<pll, vector<pll>, greater<pll>> pq;
  pq.push({0, s});

  while (!pq.empty()) {
    auto [wi, ui] = pq.top();
    pq.pop();

    if (wi > cdist[ui]) continue;

    for (auto &p : graph[ui]) {
      auto [vi, di] = p;
      if (cdist[vi] > di + wi) {
        cdist[vi] = di + wi;
        from[vi] = ui;
        pq.push({cdist[vi], vi});
      }
    }
  }
}

void solve() {
  int n, m;
  cin >> n >> m;

  for (int i = 0; i < m; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    graph[a].push_back({b, c});
    graph[b].push_back({a, c});
  }

  dijk(1);
  cout << n - 1 << '\n';
  for (int i = 2; i <= n; i++) cout << i << ' ' << from[i] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
