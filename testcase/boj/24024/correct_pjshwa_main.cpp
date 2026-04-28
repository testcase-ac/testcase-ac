#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;
using tll = tuple<ll, ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2e5;
const ll INF = 1e18;
ll cdist[MAX + 1];
vector<tll> graph[MAX + 1];
int n, x, rw;

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
      auto [vi, di, pi] = p;
      if (pi == 1) di += rw;
      if (pi == 2) di += (x - rw);
      if (cdist[vi] > di + wi) {
        cdist[vi] = di + wi;
        pq.push({cdist[vi], vi});
      }
    }
  }
}

ll f(int v) {
  rw = v;
  dijk(1);
  return cdist[n];
}

void solve() {
  int m;
  cin >> n >> m >> x;

  while (m--) {
    int u, v, w, p;
    cin >> u >> v >> w >> p;
    graph[u].push_back({v, w, p});
    graph[v].push_back({u, w, p});
  }

  int left = 0, right = x;
  while (left + 3 <= right) {
    int mid1 = left + (right - left) / 3;
    int mid2 = right - (right - left) / 3;
    if (f(mid1) > f(mid2)) right = mid2;
    else left = mid1;
  }

  ll ans = 0;
  for (int i = left; i <= right; i++) ans = max(ans, f(i));
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
