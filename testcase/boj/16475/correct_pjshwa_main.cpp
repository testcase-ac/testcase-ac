#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e4;
const ll INF = 1e18;
ll cdist[20 * MAX + 1];
vector<pll> graph[20 * MAX + 1];

void dijk(int s) {
  fill(cdist, cdist + 20 * MAX + 1, INF);
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
        pq.push({cdist[vi], vi});
      }
    }
  }
}

void solve() {
  int n, m, k, l, p;
  cin >> n >> m >> k >> l >> p;

  bool switchv[MAX + 1];
  memset(switchv, 0, sizeof(switchv));
  for (int i = 0, x; i < k; i++) {
    cin >> x;
    switchv[x] = true;
  }

  m -= l;
  while (m--) {
    int a, b, c;
    cin >> a >> b >> c;

    if (switchv[b]) {
      for (int i = 0; i < 2 * p - 1; i++) {
        int av = i * MAX + a, bv = (i + 1) * MAX + b;
        graph[av].push_back({bv, c});
      }
      graph[(2 * p - 1) * MAX + a].push_back({b, c});
    }
    else {
      for (int i = 0; i < 2 * p; i++) {
        int av = i * MAX + a, bv = i * MAX + b;
        graph[av].push_back({bv, c});
      }
    }
  }

  while (l--) {
    int a, b, c;
    cin >> a >> b >> c;

    if (switchv[b]) {
      for (int i = 0; i < p; i++) {
        int av = i * MAX + a, bv = (i + 1) * MAX + b;
        graph[av].push_back({bv, c});
      }
    }
    else {
      for (int i = 0; i < p; i++) {
        int av = i * MAX + a, bv = i * MAX + b;
        graph[av].push_back({bv, c});
      }
    }

    if (switchv[a]) {
      for (int i = p; i < 2 * p - 1; i++) {
        int av = (i + 1) * MAX + a, bv = i * MAX + b;
        graph[bv].push_back({av, c});
      }
      graph[(2 * p - 1) * MAX + b].push_back({a, c});
    }
    else {
      for (int i = p; i < 2 * p; i++) {
        int av = i * MAX + a, bv = i * MAX + b;
        graph[bv].push_back({av, c});
      }
    }
  }

  int s, e;
  cin >> s >> e;
  dijk(s);

  ll ans = INF;
  for (int i = 0; i < 2 * p; i++) ans = min(ans, cdist[i * MAX + e]);
  if (ans == INF) cout << "-1\n";
  else cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
