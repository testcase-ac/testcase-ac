#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
const ll INF = 1e14;
ll cdist[MAX + 1], fdist[MAX + 1];
int h[MAX + 1];
vector<pll> graph[MAX + 1];

void dijk1(int s) {
  fill(cdist, cdist + MAX + 1, INF);
  cdist[s] = 0;

  priority_queue<pll, vector<pll>, greater<pll>> pq;
  pq.push({0, s});

  while (!pq.empty()) {
    auto[wi, ui] = pq.top();
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

void dijk2(int s) {
  fill(fdist, fdist + MAX + 1, INF);
  fdist[s] = 0;

  priority_queue<pll, vector<pll>, greater<pll>> pq;
  pq.push({0, s});

  while (!pq.empty()) {
    auto[wi, ui] = pq.top();
    pq.pop();

    if (wi > fdist[ui]) continue;

    for (auto &p : graph[ui]) {
      auto[vi, di] = p;
      if (fdist[vi] > di + wi) {
        fdist[vi] = di + wi;
        pq.push({fdist[vi], vi});
      }
    }
  }
}

void solve() {
  int n, m, d, e;
  cin >> n >> m >> d >> e;
  for (int i = 1; i <= n; i++) cin >> h[i];
  while (m--) {
    int a, b, c;
    cin >> a >> b >> c;
    
    if (h[a] > h[b]) graph[b].push_back({a, c});
    if (h[b] > h[a]) graph[a].push_back({b, c});
  }
  dijk1(1);
  dijk2(n);

  ll ans = -INF;
  for (int i = 2; i <= n - 1; i++) {
    if (cdist[i] == INF || fdist[i] == INF) continue;
    ll score = h[i] * e - (cdist[i] + fdist[i]) * d;
    ans = max(ans, score);
  }

  if (ans == -INF) cout << "Impossible\n";
  else cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
