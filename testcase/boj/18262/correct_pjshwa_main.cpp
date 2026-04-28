#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;
using tll = tuple<ll, ll, ll>;

const int MAX = 1000;
vector<tll> graph[MAX + 1];
const ll INF = 1e18;
ll cdist[MAX + 1];
int cflow;

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
      auto [vi, di, fi] = p;
      if (fi < cflow) continue;

      if (cdist[vi] > di + wi) {
        cdist[vi] = di + wi;
        pq.push({cdist[vi], vi});
      }
    }
  }
}

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int N, M;
  cin >> N >> M;
  while (M--) {
    int a, b, c, f;
    cin >> a >> b >> c >> f;
    graph[a].push_back({b, c, f});
    graph[b].push_back({a, c, f});
  }

  ll ans = 0, factor = 1e6;
  for (cflow = 1; cflow <= MAX; cflow++) {
    dijk(1);
    if (cdist[N] == INF) continue;

    ans = max(ans, (ll)cflow * factor / cdist[N]);
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
