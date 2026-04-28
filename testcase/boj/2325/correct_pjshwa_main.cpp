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
pll from[MAX + 1];
bool ban[1'000'001];
vector<tuple<ll, ll, ll>> graph[MAX + 1];

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
      auto [ei, vi, di] = p;
      if (ban[ei]) continue;

      if (cdist[vi] > di + wi) {
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
  for (int i = 1; i <= m; i++) {
    int a, b, t;
    cin >> a >> b >> t;
    graph[a].push_back({i, b, t});
    graph[b].push_back({i, a, t});
  }

  dijk(1);
  ll rtime = 0;

  int e = n;
  while (e != 1) {
    auto [v, i] = from[e];
    ban[i] = true;

    dijk(1);
    rtime = max(rtime, cdist[n]);

    ban[i] = false;
    e = v;
  }

  cout << rtime << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
